#pragma once

#include <utility>

#include "../SmartPointers/PolymorphicPtr.hpp"

class Image;

class Memento
{
private:
	PolymorphicPtr<Image> imagePtr;

public:
	Memento();
	Memento(Image* imagePtr);

	Image* getState() const;
};