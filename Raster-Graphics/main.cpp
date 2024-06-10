#include <iostream>

#include "ImageEditor/ImageEditor.h"

int main()
{
	ImageEditor editor;
	editor.runImageEditor();

	//PPM6Image image("Files/sample_640x426.ppm");

	//Image* ptr = &image;

	//ptr->load();

	////ptr->rotateLeft();

	////dynamic_cast<IMonochrome*>(ptr)->applyMonochrome();

	//ptr->applyNegative();
	//ptr->applyNegative();

	////ptr->rotateLeft();

	////ptr->rotateRight();

	//ptr->saveAs("Files/sample_640x426Neg.ppm");

	return 0;
}