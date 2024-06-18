#pragma once

#include <utility>
#include <stdexcept>

template <typename T>
class PolymorphicPtr
{
private:
	T* data = nullptr;

	void copyFrom(const PolymorphicPtr<T>& other);
	void moveFrom(PolymorphicPtr<T>&& other) noexcept;
	void free();

public:
	PolymorphicPtr();
	PolymorphicPtr(T* data);

	PolymorphicPtr(const PolymorphicPtr<T>& other);
	PolymorphicPtr& operator=(const PolymorphicPtr<T>& other);

	PolymorphicPtr(PolymorphicPtr<T>&& other) noexcept;
	PolymorphicPtr& operator=(PolymorphicPtr<T>&& other) noexcept;

	const T* operator->() const;
	T* operator->();

	const T& operator*() const;
	T& operator*();

	const T* get() const;
	T* get();

	void reset(T* data);

	~PolymorphicPtr() noexcept;
};

template<typename T>
PolymorphicPtr<T>::PolymorphicPtr() = default;

template<typename T>
PolymorphicPtr<T>::PolymorphicPtr(T* data) : data(data) {}

template<typename T>
PolymorphicPtr<T>::PolymorphicPtr(const PolymorphicPtr<T>& other)
{
	copyFrom(other);
}

template<typename T>
PolymorphicPtr<T>& PolymorphicPtr<T>::operator=(const PolymorphicPtr<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
PolymorphicPtr<T>::PolymorphicPtr(PolymorphicPtr<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T>
PolymorphicPtr<T>& PolymorphicPtr<T>::operator=(PolymorphicPtr<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
const T* PolymorphicPtr<T>::operator->() const
{
	return this->data;
}

template<typename T>
T* PolymorphicPtr<T>::operator->()
{
	return this->data;
}

template<typename T>
const T& PolymorphicPtr<T>::operator*() const
{
	if (!this->data)
		throw std::runtime_error("PolymorphicPtr: NULLPTR!");

	return *this->data;
}

template<typename T>
T& PolymorphicPtr<T>::operator*()
{
	if (!this->data)
		throw std::runtime_error("PolymorphicPtr: NULLPTR!");

	return *this->data;
}

template<typename T>
const T* PolymorphicPtr<T>::get() const
{
	return this->data;
}

template<typename T>
T* PolymorphicPtr<T>::get()
{
	return this->data;
}

template<typename T>
void PolymorphicPtr<T>::reset(T* data)
{
	if (this->data != data)
	{
		free();
		this->data = data;
	}
}

template<typename T>
PolymorphicPtr<T>::~PolymorphicPtr() noexcept
{
	free();
}

template<typename T>
void PolymorphicPtr<T>::copyFrom(const PolymorphicPtr<T>& other)
{
	this->data = other.data->clone();
}

template<typename T>
void PolymorphicPtr<T>::moveFrom(PolymorphicPtr<T>&& other) noexcept
{
	this->data = other.data;
	other.data = nullptr;
}

template<typename T>
void PolymorphicPtr<T>::free()
{
	delete this->data;
	this->data = nullptr;
}
