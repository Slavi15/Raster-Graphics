#pragma once

#include <iostream>
#include <fstream>

template<typename T>
class Vector
{
private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void resize(size_t newCapacity);

	unsigned int getNextPowerOfTwo(unsigned int n) const;
	unsigned int allocateCapacity(unsigned int n) const;

	void copyFrom(const Vector& other);
	void moveFrom(Vector&& other) noexcept;
	void free();

public:
	Vector();
	Vector(size_t newSize);

	Vector(const Vector<T>& other);
	Vector<T>& operator=(const Vector<T>& other);

	Vector(Vector<T>&& other) noexcept;
	Vector<T>& operator=(Vector<T>&& other) noexcept;

	const size_t getSize() const;
	const size_t getCapacity() const;

	void push_back(const T& element);
	void push_back(T&& element);

	void pop_back();

	void insert(const T& element, size_t index);
	void insert(T&& element, size_t index);

	void remove(size_t index);

	const bool isEmpty() const;

	void clear();

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	template<typename T>
	friend std::istream& operator>>(std::istream& is, Vector<T>& vector);

	template<typename T>
	friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vector);

	~Vector() noexcept;
};

template<typename T>
Vector<T>::Vector()
{
	this->size = 0;
	this->capacity = 8;
	this->data = new T[this->capacity];
}

template<typename T>
Vector<T>::Vector(size_t newSize) : size(newSize)
{
	this->capacity = allocateCapacity(newSize);
	this->data = new T[this->capacity];
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	copyFrom(other);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
inline const size_t Vector<T>::getSize() const
{
	return this->size;
}

template<typename T>
inline const size_t Vector<T>::getCapacity() const
{
	return this->capacity;
}

template<typename T>
void Vector<T>::push_back(const T& element)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->data[this->size++] = element;
}

template<typename T>
void Vector<T>::push_back(T&& element)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->data[this->size++] = std::move(element);
}

template<typename T>
void Vector<T>::pop_back()
{
	if (getSize())
		this->size--;
	else
		return;

	if ((getSize() * 4) <= getCapacity() && getCapacity() > 1)
		resize(getCapacity() / 2);
}

template<typename T>
void Vector<T>::insert(const T& element, size_t index)
{
	if (index >= getSize()) return;

	this->data[index] = element;
}

template<typename T>
void Vector<T>::insert(T&& element, size_t index)
{
	if (index >= getSize()) return;

	this->data[index] = std::move(element);
}

template<typename T>
void Vector<T>::remove(size_t index)
{
	if (index >= getSize()) return;

	if (getSize())
		this->size--;
	else
		return;

	for (size_t i = index; i < getSize(); i++)
	{
		this->data[i] = this->data[i + 1];
	}
}

template<typename T>
const bool Vector<T>::isEmpty() const
{
	return getSize() == 0;
}

template<typename T>
void Vector<T>::clear()
{
	delete[] this->data;

	this->data = nullptr;
	this->size = 0;
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const
{
	return this->data[index];
}

template<typename T>
T& Vector<T>::operator[](size_t index)
{
	return this->data[index];
}

template<typename T>
std::istream& operator>>(std::istream& is, Vector<T>& vector)
{
	is >> vector.size;
	vector.resize(vector.allocateCapacity(vector.getSize()));

	for (size_t i = 0; i < vector.getSize(); i++)
	{
		is >> vector.data[i];
	}

	return is;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vector)
{
	for (size_t i = 0; i < vector.getSize(); i++)
	{
		os << vector.data[i] << " ";
	}

	os << std::endl;
	return os;
}

template<typename T>
Vector<T>::~Vector() noexcept
{
	free();
}

template<typename T>
void Vector<T>::resize(size_t newCapacity)
{
	T* newData = new T[newCapacity];
	for (size_t i = 0; i < getSize(); i++)
	{
		newData[i] = this->data[i];
	}

	delete[] this->data;
	this->data = newData;
	this->capacity = newCapacity;
}

template<typename T>
void Vector<T>::copyFrom(const Vector<T>& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->data = new T[this->capacity];
	for (size_t i = 0; i < this->capacity; i++)
	{
		this->data[i] = other.data[i];
	}
}

template<typename T>
void Vector<T>::moveFrom(Vector<T>&& other) noexcept
{
	this->data = other.data;
	this->size = other.size;
	this->capacity = other.capacity;

	other.data = nullptr;
	other.size = other.capacity = 0;
}

template<typename T>
void Vector<T>::free()
{
	delete[] this->data;

	this->data = nullptr;
	this->size = this->capacity = 0;
}

template<typename T>
unsigned int Vector<T>::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
	{
		n &= (n - 1);
	}

	return n << 1;
}

template<typename T>
unsigned int Vector<T>::allocateCapacity(unsigned int n) const
{
	return std::max(getNextPowerOfTwo(n + 1), 8u);
}
