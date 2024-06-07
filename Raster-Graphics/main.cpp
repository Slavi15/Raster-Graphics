#include <iostream>

//#include "Image/Image.h"
#include "Image/PBMImage/PBM1Image.h"
#include "Image/PBMImage/PBM4Image.h"

int main()
{
	PBM4Image image("Files/sample_hd.pbm");

	Image* ptr = &image;

	ptr->load();

	//ptr->applyNegative();

	ptr->rotateLeft();

	ptr->save("Files/hdtest.pbm");

	return 0;
}