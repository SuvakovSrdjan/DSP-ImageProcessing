#include "ImageInterpolation.h"
#include "ColorSpaces.h"
#include <math.h>


void sampleAndHold(const uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize)
{
	uchar *yBuff_Old = new uchar[xSize*ySize]();
	uchar *yBuff_New = new uchar[newXSize*newYSize / 4]();

	char *vBuff_Old = new char[xSize * ySize / 4]();
	char *vBuff_new = new char[newXSize*newYSize / 4]();

	char *uBuff_Old = new char[xSize * ySize / 4]();
	char *uBuff_new = new char[newXSize*newYSize / 4]();

	

	/* TO DO */
	RGBtoYUV420(input, xSize, ySize, yBuff_Old, uBuff_Old, vBuff_Old);

	YUV420toRGB(input, uBuff_Old, vBuff_Old, xSize, ySize, output);

}

void bilinearInterpolate(const uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize)
{
	/* TO DO */
}

void bicubicInterpolate(uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize)
{
	/* TO DO */
}

void imageRotate(const uchar input[], int xSize, int ySize, uchar output[], int m, int n, double angle)
{
	/* TO DO */
}

void imageRotateBilinear(const uchar input[], int xSize, int ySize, uchar output[], int m, int n, double angle)
{
	/* TO DO */
}