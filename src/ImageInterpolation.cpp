#include "ImageInterpolation.h"
#include "ColorSpaces.h"
#include <math.h>

#define PI 3.141592653589793


void sampleAndHold(const uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize)
{
	uchar *yBuff_Old = new uchar[xSize*ySize]();
	uchar *yBuff_new = new uchar[newXSize*newYSize]();

	char *vBuff_Old = new char[xSize * ySize / 4]();
	char *vBuff_new = new char[newXSize*newYSize / 4]();

	char *uBuff_Old = new char[xSize * ySize / 4]();
	char *uBuff_new = new char[newXSize*newYSize / 4]();

	

	
	RGBtoYUV420(input, xSize, ySize, yBuff_Old, uBuff_Old, vBuff_Old);

	//Faktori skaliranja
	const double F_ii = (double)newXSize / xSize;
	const double F_jj = (double)newYSize / ySize;


	for (int i = 0; i < newXSize; i++) {
		for (int j = 0; j < newYSize; j++) {

			int ii, jj;

			ii = (i - 1) / F_ii;
			jj = (j - 1) / F_jj;

			if (ii < xSize - 1)
				ii = (i - 1) / F_ii + 1;

			if (jj < ySize - 1)
				jj = (j - 1) / F_jj + 1;

			yBuff_new[j * newXSize + i] = yBuff_Old[jj * xSize + ii];
		}
	}
	
	for (int i = 0; i < newXSize/2; i++) {
		for (int j = 0; j < newYSize/2; j++) {

			int ii, jj;

			ii = (i - 1) / F_ii;
			jj = (j - 1) / F_jj;

			if (ii < xSize/2 - 1)
				ii = (i - 1) / F_ii + 1;

			if (jj < ySize/2 - 1)
				jj = (j - 1) / F_jj + 1;

			vBuff_new[j * newXSize / 2 + i] = vBuff_Old[jj * xSize / 2 + ii];
			uBuff_new[j * newXSize / 2 + i] = uBuff_Old[jj * xSize / 2 + ii];
		}
	}
	
	YUV420toRGB(yBuff_new, uBuff_new, vBuff_new, newXSize, newYSize, output);

	delete[] yBuff_new;
	delete[] yBuff_Old;
	delete[] uBuff_new;
	delete[] uBuff_Old;
	delete[] vBuff_new;
	delete[] vBuff_Old;
	
}

void bilinearInterpolate(const uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize)
{
	uchar *yBuff_Old = new uchar[xSize*ySize]();
	uchar *yBuff_new = new uchar[newXSize*newYSize]();

	char *vBuff_Old = new char[xSize * ySize / 4]();
	char *vBuff_new = new char[newXSize*newYSize / 4]();

	char *uBuff_Old = new char[xSize * ySize / 4]();
	char *uBuff_new = new char[newXSize*newYSize / 4]();




	RGBtoYUV420(input, xSize, ySize, yBuff_Old, uBuff_Old, vBuff_Old);

	//Faktori skaliranja
	const double F_ii = (double)newXSize / xSize;
	const double F_jj = (double)newYSize / ySize;

	for (int i = 0; i < newXSize; i++) {
		for (int j = 0; j < newYSize; j++) {
			double a, b;
			a = i / F_ii - floor(i / F_ii);
			b = j / F_jj - floor(j / F_jj);

			int ii = i / F_ii;
			int jj = j / F_jj;

			int iii, jjj;
			if (ii < xSize-1) {
				iii = ii + 1;
			}
			if (jj < ySize-1) {
				jjj = jj + 1;
			}

			yBuff_new[j * newXSize + i] = (1 - b)*(1 - a) * yBuff_Old[jj * xSize + ii]
				+ (1 - a)*b* yBuff_Old[jjj * xSize + ii]
				+ a * (1 - b) * yBuff_Old[jj * xSize + iii]
				+ a * b * yBuff_Old[jjj * xSize + iii];

		}
	}
	for (int i = 0; i < newXSize/2; i++) {
		for (int j = 0; j < newYSize/2; j++) {
			double a, b;
			a = i / F_ii - floor(i / F_ii);
			b = j / F_jj - floor(j / F_jj);

			int ii = i / F_ii;
			int jj = j / F_jj;

			int iii = ii;
			int jjj = jj;
			if (ii < xSize/2-1) {
				iii = ii + 1;
			}
			if (jj < ySize/2-1) {
				jjj = jj + 1;
			}

			uBuff_new[j * newXSize / 2 + i] = (1 - b)*(1 - a) * uBuff_Old[jj * xSize/2 + ii]
				+ (1 - a)*b* uBuff_Old[jjj * xSize/2 + ii]
				+ a * (1 - b) * uBuff_Old[jj * xSize/2 + iii]
				+ a * b * uBuff_Old[jjj * xSize/2 + iii];

			vBuff_new[j * newXSize / 2 + i] = (1 - b)*(1 - a) * vBuff_Old[jj * xSize / 2 + ii]
				+ (1 - a)*b* vBuff_Old[jjj * xSize / 2 + ii]
				+ a * (1 - b) * vBuff_Old[jj * xSize / 2 + iii]
				+ a * b * vBuff_Old[jjj * xSize / 2 + iii];

		}
	}

	YUV420toRGB(yBuff_new, uBuff_new, vBuff_new, newXSize, newYSize, output);

	delete[] yBuff_new;
	delete[] yBuff_Old;
	delete[] uBuff_new;
	delete[] uBuff_Old;
	delete[] vBuff_new;
	delete[] vBuff_Old;
	
}

void bicubicInterpolate(uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize)
{
	/* TO DO */
}

void imageRotate(const uchar input[], int xSize, int ySize, uchar output[], int m, int n, double angle)
{
	uchar *yBuff_Old = new uchar[xSize * ySize]();
	uchar *yBuff_new = new uchar[xSize * ySize]();


	char *vBuff_Old = new char[xSize * ySize / 4]();
	char *vBuff_new = new char[xSize * ySize / 4]();

	char *uBuff_Old = new char[xSize * ySize / 4]();
	char *uBuff_new = new char[xSize * ySize / 4]();




	RGBtoYUV420(input, xSize, ySize, yBuff_Old, uBuff_Old, vBuff_Old);

	angle = angle * PI / 180;

	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize; j++) {
			int xPos = i*cos(angle) - j*sin(angle) - m*cos(angle) + n*sin(angle) + m + 0.5;
			int yPos = j*cos(angle) + i*sin(angle) - m*sin(angle) - n*cos(angle) + n + 0.5;

			if (xPos < xSize && yPos < ySize && xPos >= 0 && yPos >= 0)
			{
				yBuff_new[j * xSize + i] = yBuff_Old[yPos*xSize + xPos];
			}
			else
			{
				yBuff_new[j*xSize + i] = 0;
			}
		}
	}

	for (int i = 0; i < xSize / 2; i++) {
		for (int j = 0; j < ySize / 2; j++) {
			int xPos = i*cos(angle) - j*sin(angle) - m/2*cos(angle) + n/2*sin(angle) + m/2 + 0.5;
			int yPos = j*cos(angle) + i*sin(angle) - m/2*sin(angle) - n/2*cos(angle) + n/2 + 0.5;

			if (xPos < xSize / 2 && yPos < ySize / 2 && xPos >= 0 && yPos >= 0)
			{
				uBuff_new[j * xSize / 2 + i] = uBuff_Old[yPos * xSize /2 + xPos];
				vBuff_new[j * xSize / 2 + i] = vBuff_Old[yPos * xSize /2 + xPos];
			}
			else
			{
				uBuff_new[j * xSize / 2 + i] = 0;
				vBuff_new[j * xSize / 2 + i] = 0;
			}
		}
	}
	
	YUV420toRGB(yBuff_new, uBuff_new, vBuff_new, xSize, ySize, output);

	delete[] yBuff_Old;
	delete[] yBuff_new;
	delete[] uBuff_new;
	delete[] uBuff_Old;
	delete[] vBuff_new;
	delete[] vBuff_Old;
}

void imageRotateBilinear(const uchar input[], int xSize, int ySize, uchar output[], int m, int n, double angle)
{
	uchar *yBuff_Old = new uchar[xSize * ySize]();
	uchar *yBuff_new = new uchar[xSize * ySize]();


	char *vBuff_Old = new char[xSize * ySize / 4]();
	char *vBuff_new = new char[xSize * ySize / 4]();

	char *uBuff_Old = new char[xSize * ySize / 4]();
	char *uBuff_new = new char[xSize * ySize / 4]();




	RGBtoYUV420(input, xSize, ySize, yBuff_Old, uBuff_Old, vBuff_Old);

	angle = angle * PI / 180;

	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize; j++) {
			double a = i*cos(angle) - j*sin(angle) - m*cos(angle) + n*sin(angle) + m;
			double b = j*cos(angle) + i*sin(angle) - m*sin(angle) - n*cos(angle) + n;
			int ii = a;
			int jj = b;

			int iii = ii;
			int jjj = jj;

			if (ii < xSize - 1)
			{
				iii = ii + 1;
			}
			if(jj < ySize - 1)
			{
				jjj = jj + 1;
			}
			a -= (int)a;
			b -= (int)b;

			if (ii < xSize  && jj < ySize  && ii >= 0 && jj >= 0 && iii < xSize  && jjj < ySize  && iii >= 0 && jjj >= 0) {

				yBuff_new[j * xSize + i] = (1 - b)*(1 - a) * yBuff_Old[jj * xSize + ii]
					+ (1 - a)*b* yBuff_Old[jjj * xSize + ii]
					+ a * (1 - b) * yBuff_Old[jj * xSize + iii]
					+ a * b * yBuff_Old[jjj * xSize + iii];
			}
			else {
				yBuff_new[j * xSize + i] = 0;
			}


		}
	}

	for (int i = 0; i < xSize / 2; i++) {
		for (int j = 0; j < ySize / 2; j++) {
			double a = i*cos(angle) - j*sin(angle) - m / 2 * cos(angle) + n / 2 * sin(angle) + m / 2 + 0.5;
			double b = j*cos(angle) + i*sin(angle) - m / 2 * sin(angle) - n / 2 * cos(angle) + n / 2 + 0.5;
			int ii = a;
			int jj = b;

			int iii = ii;
			int jjj = jj;

			if (ii < xSize/2 - 1)
			{
				iii = ii + 1;
			}
			if (jj < ySize/2 -1)
			{
				jjj = jj + 1;
			}
			a -= (int)a;
			b -= (int)b;

			if (ii < xSize/2 && jj < ySize/2 && ii >= 0 && jj >= 0 && iii < xSize / 2 && jjj < ySize / 2 && iii >= 0 && jjj >= 0) {

				uBuff_new[j * xSize / 2 + i] = (1 - b)*(1 - a) * uBuff_Old[jj * xSize / 2 + ii]
					+ (1 - a)*b* uBuff_Old[jjj * xSize / 2 + ii]
					+ a * (1 - b) * uBuff_Old[jj * xSize / 2 + iii]
					+ a * b * uBuff_Old[jjj * xSize / 2 + iii];

				vBuff_new[j * xSize / 2 + i] = (1 - b)*(1 - a) * vBuff_Old[jj * xSize / 2 + ii]
					+ (1 - a)*b* vBuff_Old[jjj * xSize / 2 + ii]
					+ a * (1 - b) * vBuff_Old[jj * xSize / 2 + iii]
					+ a * b * vBuff_Old[jjj * xSize / 2 + iii];
			}
			else {
				uBuff_new[j * xSize/2 + i] = 0;
				vBuff_new[j * xSize/2 + i] = 0;
			}
		}
	}

	YUV420toRGB(yBuff_new, uBuff_new, vBuff_new, xSize, ySize, output);

	delete[] yBuff_Old;
	delete[] yBuff_new;
	delete[] uBuff_new;
	delete[] uBuff_Old;
	delete[] vBuff_new;
	delete[] vBuff_Old;
}