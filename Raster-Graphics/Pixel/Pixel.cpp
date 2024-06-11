#include "Pixel.h"

Pixel::Pixel() = default;

Pixel::Pixel(uint8_t R, uint8_t G, uint8_t B)
{
	setR(R);
	setG(G);
	setB(B);
}

uint16_t Pixel::getR() const
{
	return this->R;
}

uint16_t Pixel::getG() const
{
	return this->G;
}

uint16_t Pixel::getB() const
{
	return this->B;
}

void Pixel::setR(uint8_t R)
{
	this->R = R;
}

void Pixel::setG(uint8_t G)
{
	this->G = G;
}

void Pixel::setB(uint8_t B)
{
	this->B = B;
}

bool Pixel::isGrayScale() const
{
	return getR() == getG() && getG() == getB();
}

void Pixel::RGBToGrayScale()
{
	uint8_t grayscale = static_cast<uint8_t>(0.3 * getR() + 0.59 * getG() + 0.11 * getB());

	setR(grayscale);
	setG(grayscale);
	setB(grayscale);
}

void Pixel::RGBToMonochrome(uint16_t colorValue)
{
	setR(colorValue);
	setG(colorValue);
	setB(colorValue);
}

void Pixel::RGBToNegative(uint16_t colorValue)
{
	setR(colorValue - getR());
	setG(colorValue - getG());
	setB(colorValue - getB());
}

std::istream& operator>>(std::istream& is, Pixel& pixel)
{
	uint16_t R;
	uint16_t G;
	uint16_t B;

	is >> R >> G >> B;

	pixel.setR(R);
	pixel.setG(G);
	pixel.setB(B);

	return is;
}

std::ostream& operator<<(std::ostream& os, const Pixel& pixel)
{
	return os << pixel.getR() << " " << pixel.getG() << " " << pixel.getB() << std::endl;
}
