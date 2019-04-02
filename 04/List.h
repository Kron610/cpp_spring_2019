#pragma once
#include <iostream>

typedef struct ListNode
{
	ListNode* next;
	int element;
} ListNode;

class List
{
private:
	ListNode* first;
	size_t size;

public:
	List():size(0)
	{}

	~List()
	{
		Clear();
	}

	void Clear()
	{
		if (this->size != 0)
		{
			ListNode* cash1;
			for (size_t i = 0; i < this->Getsize() - 1; i++)
			{
				cash1 = this->first;
				if (this->first->next != nullptr)
					this->first = this->first->next;
				delete cash1;
			}
			delete this->first;
			size = 0;
		}
	}

	const int& operator[](size_t index) const
	{
		ListNode* List_cash = this->first;
		for (size_t i = 0; i < index; i++)
		{
			List_cash = List_cash->next;
		}
		return List_cash->element;
	}

	int& operator[](size_t index) 
	{
		ListNode* List_cash = this->first;
		for (size_t i = 0; i < index; i++)
		{
			List_cash = List_cash->next;
		}
		return List_cash->element;
	}

	void Append(const int item)
	{
		if (this->size == 0)
		{
			this->first = new ListNode;
			this->first->element = item;
			this->first->next = nullptr;
		}
		else
		{
			ListNode* List_cash = this->first;
			for (size_t i = 0; i < this->Getsize() - 1; i++)
			{
				List_cash = List_cash->next;
			}
			List_cash->next = new ListNode;
			List_cash->next->element = item;
			List_cash->next->next = nullptr;
		}
		this->size += 1;
	}

	void Prepend(const int item)
	{
		this->size += 1;
		ListNode* cash = new ListNode;
		cash->element = item;
		if (this->size == 0)
		{
			this->first = cash;
		}
		else
		{
			cash->next = this->first;
			this->first = cash;
		}
	}

	void InsertArt(size_t index, const int item)
	{
		ListNode* cash;
		if (index == 0)
		{
			cash = new ListNode;
			cash->element = item;
			cash->next = this->first;
			this->first = cash;
		}
		else
		{
			cash = this->first;
			for (size_t i = 1; i < index; i++)
				cash = cash->next;
			ListNode* cash2;
			cash2 = new ListNode;
			cash2->element = item;
			cash2->next = cash->next;
			cash->next = cash2;
		}
		this->size += 1;
	}

	void Pop()
	{
		ListNode* cash = this->first;
		for (size_t i = 0; i < this->Getsize() - 2; i++)
			cash = cash->next;
		cash->next = nullptr;
		this->size -= 1;
	}

	void Output() const
	{

		if (this->size == 0)
			std::cout << "This sequence is empty" << std::endl;
		else
		{
			std::cout << "Your sequence:" << std::endl;
			ListNode* cash = this->first;
			std::cout << cash->element << '\t';
			for (size_t i = 0; i < this->Getsize() - 1; i++)
			{
				cash = cash->next;
				std::cout << cash->element << '\t';
			}
			std::cout << std::endl << std::endl;
		}
	}

	size_t Getsize() const
	{
		return this->size;
	}
};