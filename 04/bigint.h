#pragma once
#include <string>
#include "List.h"
#include <iomanip>

class BigInt 
{

	friend std::ostream& operator <<(std::ostream& os, const BigInt& number);

private:

	static const int64_t base = 1000000000;
	bool mark;
	List Data;

	void RemoveZeroes()
	{
		while (Data.Getsize() > 1 && Data[Data.Getsize() - 1] == 0)
		{
			Data.Pop();
		}
		if (Data.Getsize() == 1 && Data[0] == 0)
			mark = true;
	}

public:

	BigInt(std::string str = "")
	{
		if (str.length() == 0)
			this->mark = true;
		else
		{
			if (str[0] == '-')
			{
				str = str.substr(1);
				this->mark = false;
			}
			else
				this->mark = true;
			this->Data = List();
			for (long long i = str.length(); i > 0; i -= 9)
			{
				if (i < 9)
				{
					Data.Append(atoi(str.substr(0, i).c_str()));
				}
				else
					Data.Append(atoi(str.substr(i - 9, 9).c_str()));
			}	
		}
		RemoveZeroes();
	}

		BigInt& operator=(int64_t Int)
	{
		Data.Clear();
		if (Int < 0)
		{
			this->mark = false;
			Int = -Int;
		}
		else
			this->mark = true;
		do 
		{
			this->Data.Append(Int % base);
			Int /= base;
		} while (Int != 0);
		return *this;
	}

	BigInt(int64_t Int)
	{
		if (Int < 0) 
		{
			this->mark = false;
			Int = -Int;
		}
		else
			this->mark = true;
		do
		{
			this->Data.Append(Int % base);
			Int /= base;
		} while (Int != 0);
	}

	BigInt(const BigInt& number)
	{
		mark = number.mark;
		for (size_t i = 0; i < number.Data.Getsize(); i++)
			Data.Append(number.Data[i]);
	}

	BigInt& operator=(const BigInt& number)
	{
		if (this == &number)
			return *this;
		this->Data.Clear();
		for (size_t i = 0; i < number.Data.Getsize(); i++)
			Data.Append(number.Data[i]);
		mark = number.mark;
		return *this;
	}

	BigInt operator-() const
	{
		BigInt tmp = BigInt(*this);
		if (!(Data.Getsize() && Data[0] == 0))
			tmp.mark = !(this->mark);
		return tmp;
	}

	BigInt operator+(const BigInt& number) const
	{
		if (mark == number.mark)
		{
			BigInt tmp;
			if (this->Data.Getsize() < number.Data.Getsize())
				tmp = BigInt(number);
			else
				tmp = BigInt(*this);

			for (size_t i = 0; i < number.Data.Getsize() - 1; i++)
			{
				tmp.Data[i] += number.Data[i];
				if (tmp.Data[i] >= base)
				{
					tmp.Data[i] = tmp.Data[i] % base;
					tmp.Data[i + 1] += 1;
				}
			}
			size_t i = number.Data.Getsize() - 1;
			tmp.Data[i] += number.Data[i];
			while (tmp.Data[i] >= base)
			{
				tmp.Data[i] = tmp.Data[i] % base;
				i += 1;
				if (i == tmp.Data.Getsize())
					tmp.Data.Append(1);
			}
			return tmp;
		}
		else
		{
			if (mark)
				return (*this - (-number));
			else
				return (number - (-(*this)));
		}
	}

	BigInt operator-(const BigInt& number) const
	{
		if (!(number.mark))
			return *this + (-number);
		else
			if (!(this->mark))
				return -(-(*this) + number);
			else
				if (*this < number)
					return -(number - (*this));
		BigInt tmp = BigInt(*this);
		for (size_t i = 0; i < tmp.Data.Getsize(); i++)
		{
			tmp.Data[i] -= (i < number.Data.Getsize() ? number.Data[i] : 0);
			if (tmp.Data[i] < 0)
			{
				tmp.Data[i] += base;
				tmp.Data[i + 1] -= 1;
			}
		}
		tmp.RemoveZeroes();
		return tmp;
	}

	bool operator==(const BigInt& number) const
	{
		if (this->Data.Getsize() != number.Data.Getsize())
			return false;
		if (this->mark != number.mark)
			return false;
		if (this->Data.Getsize() == 0)
			return true;
		for (size_t i = 0; i < this->Data.Getsize(); i++)
			if (number.Data[i] != this->Data[i])
				return false;
		return true;
	}

	bool operator!=(const BigInt& number) const
	{
		return !(*this == number);
	}

	bool operator<(const BigInt& number) const
	{
		if (number.mark != this->mark)
			return !mark;
		if (number.Data.Getsize() < this->Data.Getsize())
			return !mark;
		if (number.Data.Getsize() > this->Data.Getsize())
			return mark;
		for (long long i = number.Data.Getsize() - 1; i >= 0; i--)
			if (number.Data[i] != this->Data[i])
				if (this->Data[i] > number.Data[i])
					return !mark;
				else
					return mark;
		return false;
	}

	bool operator>(const BigInt& number) const
	{
		if (*this == number)
			return false;
		return !(*this < number);
	}

	bool operator<=(const BigInt& number) const
	{
		return !(*this > number);
	}

	bool operator>=(const BigInt& number) const
	{
		return !(*this < number);
	}

};

std::ostream& operator <<(std::ostream& os, const BigInt& number)
{
	if (number.Data.Getsize() == 0)
		os << 0 ;
	else
	{
		if (!(number.mark))
			os << '-';
		os << number.Data[number.Data.Getsize() - 1];
		char old_fill = os.fill('0');
		for (long long i = static_cast<long long>(number.Data.Getsize()) - 2; i >=0; i--)
		{
			os << std::setw(9) << number.Data[i];
		}
	}
	return os;
}