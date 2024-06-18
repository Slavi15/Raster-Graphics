#include "Memento.h"

Memento::Memento() = default;

Memento::Memento(Image* imagePtr) : imagePtr(imagePtr) {}

Image* Memento::getState() const
{
	return (Image*)imagePtr.get();
}
