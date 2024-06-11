#pragma once

#include <iostream>
#include <fstream>

class Pixel
{
private:
	uint8_t R = 0;
	uint8_t G = 0;
	uint8_t B = 0;

public:
	Pixel();
	Pixel(uint8_t R, uint8_t G, uint8_t B);

	uint16_t getR() const;
	uint16_t getG() const;
	uint16_t getB() const;

	void setR(uint8_t R);
	void setG(uint8_t G);
	void setB(uint8_t B);

	bool isGrayScale() const;

	void RGBToGrayScale();
	void RGBToMonochrome(uint16_t colorValue);
	void RGBToNegative(uint16_t colorValue);

	friend std::istream& operator>>(std::istream& is, Pixel& pixel);
	friend std::ostream& operator<<(std::ostream& os, const Pixel& pixel);
};