#pragma once

#include <iostream>
#include <fstream>

template <typename T>
class Pixel
{
private:
	T R;
	T G;
	T B;

public:
	Pixel();
	Pixel(const T& R, const T& G, const T& B);

	const T& getR() const;
	const T& getG() const;
	const T& getB() const;

	void setR(const T& R);
	void setG(const T& G);
	void setB(const T& B);

	bool isGrayScale() const;

	template <typename T>
	friend std::istream& operator>>(std::istream& is, Pixel<T>& pixel);

	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const Pixel<T>& pixel);
};

template <typename T>
Pixel<T>::Pixel() = default;

template <typename T>
Pixel<T>::Pixel(const T& R, const T& G, const T& B)
{
	setR(R);
	setG(G);
	setB(B);
}

template <typename T>
const T& Pixel<T>::getR() const
{
	return this->R;
}

template <typename T>
const T& Pixel<T>::getG() const
{
	return this->G;
}

template <typename T>
const T& Pixel<T>::getB() const
{
	return this->B;
}

template <typename T>
void Pixel<T>::setR(const T& R)
{
	this->R = R;
}

template <typename T>
void Pixel<T>::setG(const T& G)
{
	this->G = G;
}

template <typename T>
void Pixel<T>::setB(const T& B)
{
	this->B = B;
}

template<typename T>
bool Pixel<T>::isGrayScale() const
{
	return getR() == getG() && getG() == getB();
}

template <typename T>
std::istream& operator>>(std::istream& is, Pixel<T>& pixel)
{
	return is >> pixel.R >> pixel.G >> pixel.B;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Pixel<T>& pixel)
{
	return os << pixel.getR() << " " << pixel.getG() << " " << pixel.getB() << std::endl;
}