
#include "numbers.dat"
#include <iostream>
#include <vector>
int BinarySearch(int key)
{
	int left = 0;
	int right = Size - 1;
	int midd = 0;
	while (1)
	{
		midd = (left + right) / 2;
		if (key < (Data[midd]))       // если искомое меньше значения в ячейке
			right = midd - 1;      // смещаем правую границу поиска
		else if (key > (Data[midd]))  // если искомое больше значения в ячейке
			left = midd + 1;    // смещаем левую границу поиска
		else                       // иначе (значения равны)
			return midd;           // функция возвращает индекс ячейки
		if (left > right)          // если границы сомкнулись 
			return -1;
	}
}
int foo(int fnumber, int snumber, std::vector<bool>& numbers)
{
	int right = 0;
	int left = 0;
	int count = 0;
	right = BinarySearch(fnumber);
	if (right == -1)
		return count;
	left = BinarySearch(snumber);
	if (left == -1)
		return count;
	for (int k = right; k <= left; k++)
	{
		if (numbers[Data[k]])
			count += 1;
	}
	return count;
}

void get_numbers(std::vector<bool>& numbers, int N)
{
	numbers.resize(N+1);
	for (int i = 0; i < N + 1; i++)
		numbers[i] = true;
	numbers[0] = false;
	numbers[1] = false;
	for (long long p = 2; p < N + 1; p++)
	{
		if (numbers[p] != false)
		{
			for (long long j = p * p; j < N + 1; j += p)
				numbers[j] = false;
		}
	}
}


int main(int argc, char* argv[])
{
	if ((!(argc % 2)) || (argc == 1))
		return -1;
	std::vector<bool> a;
	get_numbers(a, Size);
	for (int i = 1; i < argc - 1; i += 2)
	{
		int v1 = std::atoi(argv[i]);
		int v2 = std::atoi(argv[i + 1]);
		std::cout << foo(v1, v2, a) << std::endl;
	}
	return 0;
}
