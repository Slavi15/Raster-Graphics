#pragma once

class Image;

class Memento
{
private:
	const Image* imagePtr;

public:
	Memento();
	Memento(const Image* imagePtr);

	Image* getState() const;
};