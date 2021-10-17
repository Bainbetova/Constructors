#pragma once
#include <iostream>
template<class T>
class Move_ptr
{
	T* m_ptr;
public:
	Move_ptr(T* ptr = nullptr)
		:m_ptr(ptr)
	{
	}

	~Move_ptr()
	{
		delete m_ptr;
	}

	// ����������� �����������, ������� �������� ����� ������������� �� x.m_ptr � m_ptr
	Move_ptr(Move_ptr&& x) noexcept
		: m_ptr(x.m_ptr)
	{
		x.m_ptr = nullptr; 
	} 

	// �������� ������������ ������������, ������� �������� ����� ������������� �� x.m_ptr � m_ptr
	Move_ptr& operator=(Move_ptr&& x) noexcept
	{
		// �������� �� ����������������
		if (&x == this) return *this;

		// ������� ��, ��� � ����� ������� ����� ������� ��������� 
		delete m_ptr;

		// �������� ����� ������������� �� x.m_ptr � m_ptr
		m_ptr = x.m_ptr;
		x.m_ptr = nullptr; 

		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};

class ItemMove
{
public:
	ItemMove() { std::cout << "Item acquired\n"; }
	~ItemMove() { std::cout << "Item destroyed\n"; }
};

Move_ptr<ItemMove> generateItemMove()
{
	Move_ptr<ItemMove> item(new ItemMove);
	return item; // ��� ������������ �������� �������� � ������ ������������ �����������
}