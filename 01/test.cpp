
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
int foo(int fnumber, int snumber, bool* boolarr)
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
		if (boolarr[Data[k]])
			count += 1;
	}
	return count;
}


int main(int argc, char* argv[])
{
	if ((!(argc % 2)) || (argc == 1))
		return -1;
	bool *a = new bool[Size + 1];
	for (int i = 0; i < Size + 1; i++)
		a[i] = true;
	a[1] = false;
	for (long long p = 2; p < Size + 1; p++)
	{
		if (a[p] != false)
		{
			for (long long j = p * p; j < Size + 1; j += p)
				a[j] = false;
		}
	}
	std::vector<int> ivector;
	for (int i = 1; i < argc; ++i)
	{
		int v = std::atoi(argv[i]);
		ivector.push_back(v);
	}
	for (int i = 0; i < argc - 2; i += 2)
	{
		std::cout << foo(ivector[i], ivector[i + 1], a) << std::endl;
	}
	return 0;
}
