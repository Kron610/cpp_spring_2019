#pragma once
#include <vector>
class Matrix
{
private:
	
	class Row
	{
	public:
		Row(size_t Columns = 0) :
		Columns(Columns)
		{
			this->row = std::vector<int>(Columns);
		}
		const int& operator[](size_t i) const
		{
			if (i >= Columns)
				throw std::out_of_range("");
			return row[i];
		}
		int& operator[](size_t i)
		{
			if (i >= Columns)
				throw std::out_of_range("");
			return row[i];
		}

		size_t Get_Columns() const
		{
			return Columns;
		}

		Row& operator*=(const int number)
		{
			for (size_t i = 0; i < Columns; i++)
				row[i] *= number;
			return *this;
		}

		const bool operator==(const Row& srow) const
		{
			for (size_t i = 0; i < Columns; i++)
				if (row[i] != srow[i])
					return false;
			return true;
		}

		const bool operator!=(const Row& srow) const
		{
			return !(*this == srow);
		}

	private:

		std::vector<int> row;
		size_t Columns;
	};

	size_t Rows;
	size_t Columns;
	std::vector<Row> Data;

public:

	Matrix(size_t Rows, size_t Columns) :
		Rows(Rows)
	{
		Data = std::vector<Row>(Rows);
		for (size_t i = 0; i < Rows; i++)
			Data[i] = Row(Columns);
	}

	size_t getRows() const
	{
		return this->Rows;
	}

	size_t getColumns() const
	{
		return this->Data[0].Get_Columns();
	}

	const Row& operator[](size_t i) const
	{
		if (i >= Rows)
			throw std::out_of_range("");
		return Data[i];
	}

	Row& operator[](size_t i)
	{
		if (i >= Rows)
			throw std::out_of_range("");
		return Data[i];
	}

	Matrix& operator*=(const int number)
	{
		for (size_t i = 0; i < Rows; i++)
			Data[i] *= number;
		return *this;
	}

	const bool operator==(const Matrix& smatr) const
	{
		if (this->Rows != smatr.Rows)
			return false;
		if (this->Columns != smatr.Columns)
			return false;
		for (size_t i = 0; i < Rows; i++)
			if (Data[i] != smatr[i])
				return false;
		return true;
	}

	const bool operator!=(const Matrix& smatr) const
	{
		return !(*this == smatr);
	}

};