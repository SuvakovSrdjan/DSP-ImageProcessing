
#include "ImageProcessing.h"
#include "ImageInterpolation.h"

#include <QDebug>

int upto(int x, int y) {
	return (x + y - 1) & ~(y - 1);
}

void imageProcessingFun(const QString& progName, QImage* const outImgs, const QImage* const inImgs, const QVector<double>& params) 
{
	int X_SIZE = inImgs->width();
	int Y_SIZE = inImgs->height();

	/* NOTE: Calculate output image resolution and construct output image object */

	if(progName == "Sample and hold") 
	{	
		/* Input image data in RGB format can be obtained with inImgs->bits() */
		/* Vertical scale factor is params[0] */
		/* Horizontal scale factor is params[1] */

		/* TO DO: Calculate output image resolution and construct output image object */

		/* TO DO: Perform Sample and hold interpolation  */
		
		int newX_size = upto(X_SIZE * params[1], 4);
		int newY_size = upto(Y_SIZE * params[0], 4);

		*outImgs = *(new QImage(newX_size, newY_size, inImgs->format()));

		sampleAndHold(inImgs->bits(), X_SIZE, Y_SIZE, outImgs->bits(), newX_size, newY_size);
		


	}
	else if (progName == "Bilinear") 
	{
		/* Input image data in RGB format can be obtained with inImgs->bits() */
		/* Vertical scale factor is params[0] */
		/* Horizontal scale factor is params[1] */

		/* TO DO: Calculate output image resolution and construct output image object */

		/* TO DO: Perform Bilinear interpolation  */

		double vertical_factor = params[0], horizontal_factor = params[1];
		int newX_size = upto(horizontal_factor * X_SIZE, 4);
		int newY_size = upto(vertical_factor * Y_SIZE, 4);

		*outImgs = *(new QImage(newX_size, newY_size, inImgs->format()));

		bilinearInterpolate(inImgs->bits(), X_SIZE, Y_SIZE, outImgs->bits(), newX_size, newY_size);

	}
	else if (progName == "Bicubic")
	{
		/* Input image data in RGB format can be obtained with inImgs->bits() */
		/* Vertical scale factor is params[0] */
		/* Horizontal scale factor is params[1] */

		/* TO DO: Calculate output image resolution and construct output image object */

		/* TO DO: Perform Bicubic interpolation  */

	}
	else if(progName == "Rotation") 
	{	
		/* Input image data in RGB format can be obtained with inImgs->bits() */
		/* Rotation angle in degrees is params[0]*/
		/* Center of rotation coordinates are (XSIZE/2, YSIZE/2) */

		/* TO DO: Construct output image object */

		/* TO DO: Perform image rotation */
		uchar* output = (uchar*)malloc(3 * sizeof(uchar)*X_SIZE*Y_SIZE);


		imageRotate((uchar*)inImgs->bits(), X_SIZE, Y_SIZE, output, X_SIZE / 2, Y_SIZE / 2, params[0]);

		QImage img(output, X_SIZE, Y_SIZE, inImgs->format());
		*outImgs = img;
	
	}
	else if (progName == "Rotation Bilinear") 
	{
		/* Input image data in RGB format can be obtained with inImgs->bits() */
		/* Rotation angle in degrees is params[0]*/
		/* Center of rotation coordinates are (XSIZE/2, YSIZE/2) */

		/* TO DO: Construct output image object */

		/* TO DO: Perform image rotation with bilinear interpolation */
		uchar* output = (uchar*)malloc(3 * sizeof(uchar)*X_SIZE*Y_SIZE);


		imageRotateBilinear((uchar*)inImgs->bits(), X_SIZE, Y_SIZE, output, X_SIZE / 2, Y_SIZE / 2, params[0]);

		QImage img(output, X_SIZE, Y_SIZE, inImgs->format());
		*outImgs = img;
	}

}

