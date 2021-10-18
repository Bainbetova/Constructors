#pragma once
#include <iostream>

/* Класс с конструтором перемещения и с оператором присваивания перемещением, с запретом на копирование */
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

	// Конструктор копирования - запрещаем любое копирование
	Move_ptr(const Move_ptr& x) = delete;

	// Конструктор перемещения, который передает право собственности на x.m_ptr в m_ptr
	Move_ptr(Move_ptr&& x) noexcept
		: m_ptr(x.m_ptr)
	{
		x.m_ptr = nullptr; 
	} 

	// Оператор присваивания копированием - запрещаем любое копирование!
	Move_ptr& operator=(const Move_ptr& x) = delete;

	// Оператор присваивания перемещением, который передает право собственности на x.m_ptr в m_ptr
	Move_ptr& operator=(Move_ptr&& x) noexcept
	{
		// Проверка на самоприсваивание
		if (&x == this) return *this;

		// Удаляем всё, что к этому моменту может хранить указатель 
		delete m_ptr;

		// Передаем право собственности на x.m_ptr в m_ptr
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
	return item; // это возвращаемое значение приведет к вызову конструктора перемещения
}