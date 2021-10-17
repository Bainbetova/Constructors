// CopyConstructor.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "MoveConstructor.h"

/* Класс с конструктором копирования */
template<class T>
class Auto_ptr
{
	T* m_ptr;
public:
	Auto_ptr(T* ptr = nullptr)
		:m_ptr(ptr)
	{
	}

	~Auto_ptr()
	{
		delete m_ptr;
	}

	// Конструктор копирования, который выполняет глубокое копирование x.m_ptr в m_ptr
	Auto_ptr(const Auto_ptr& x)
	{
		m_ptr = new T;
		*m_ptr = *x.m_ptr;
	}

	// Оператор присваивания копированием, который выполняет глубокое копирование x.m_ptr в m_ptr
	Auto_ptr& operator=(const Auto_ptr& x)
	{
		// Проверка на самоприсваивание
		if (&x == this) return *this;

		// Удаляем всё, что к этому моменту может хранить указатель 
		delete m_ptr;

		// Копируем передаваемый объект
		m_ptr = new T;
		*m_ptr = *x.m_ptr;

		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};

// Инкапсулированный умный указатель
class Item
{
public:
	Item() { std::cout << "ItemMoveMove acquired\n"; }
	~Item() { std::cout << "ItemMove destroyed\n"; }
};

Auto_ptr<Item> generateItem()
{
	Auto_ptr<Item> Item(new Item); // будет уничтожена, при завершении выполнения данной функции
	return Item; // это возвращаемое значение приведет к вызову конструктора копирования
}



int main()
{
	/* Использование конструктора копирования */
	//Auto_ptr<Item> mainItem;
	//mainItem = generateItem(); // эта операция присваивания приведет к вызову оператора присваивания копированием

	/* Использование конструктора перемещения */
	Move_ptr<ItemMove> mainItemMove;
	mainItemMove = generateItemMove(); // эта операция присваивания приведет к вызову оператора присваивания перемещением
	return 0;
}