#pragma once

#include "../SmartPointers/PolymorphicPtr.hpp"
#include <utility>

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