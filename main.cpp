/*
 * Ethan Richards
 * November 2020
 * Image manipulation using Qt4.
 * Easiest to compile with a CMakeLists.txt file either in a CLion project or through terminal 
 *   with "cmake ." then "make ." to build an executable in the bin ("binary") directory.
 */

#include <stdio.h>                  // printf()
#include <QtGui/QApplication>       // QApplication class to run a GUI
#include <QtGui/QImage>             // QImage class to handle images
#include <QtGui/QLabel>             // QLabel class for displaying QImages
#include <QtGui/QColor>             // QColor class to handle color channels
#include <random>                   // To get random values for color fuzz function
#include <time.h>
//#include <jpegint.h>

//THESE ARE USED TO CHANGE THE VALUES IN THE OUTCOME OF THE STRIPES FUNCTION
#define STRIPETHICKNESS 20 //Size of stripe in pixels
#define STRIPEDIRECTION 0 //if 0: horizontal, if 1: vertical
#define COLOR1 0            //if 0: Red, if 1: Green, if 2: Blue
#define COLOR2 1

//THIS IS USED TO CHANGE THE ROTATION OF THE OUTCOME OF THE ROTATE FUNCTION
#define ROTATE 270

//-------------------------------

/* 
 * This function can complete the dot product between two vectors that are 2D
 * Inputs: Two 2D vectors
 * Outputs: 1 scalar value
 */
int dotProd(int v0[2], int v1[2]){
    int x = v0[0] * v1[0];
    int y = v0[1] * v1[1];
    int dProd = x + y;

    return dProd;
}

/* 
 * This function completes the rotation of pixels
 * Inputs: Two 2D vectors
 * Outputs: 1 scalar value
 */
void VectorMatrixMult(int pixelLocation[2], int * newLocation){ 
    int row1[2];
    int row2[2];

    if(ROTATE == 90){
        row1[0] = 1;
        row1[1] = 0;
        row2[0] = 0;
        row2[1] = -1;
    } else if(ROTATE == 180){
        row1[0] = 0;
        row1[1] = 1;
        row2[0] = -1;
        row2[1] = 0;
    } else if(ROTATE == 270){
        row1[0] = 1;
        row1[1] = 0;
        row2[0] = 0;
        row2[1] = -1;
    }

    newLocation[0] = dotProd(row1, pixelLocation);
    newLocation[1] = dotProd(row2, pixelLocation);

}

QColor getRgbaPixel(int col, int row, QImage image)
/*
 *This separate function correctly handles converting an RGBA pixel from
 *   an image with transparency to a QColor instance.
 * Inputs:  A pixel location (row and column) and the image to get a pixel from.
 * Output:  A QColor with RGBA channels.  The QImage.pixel() method by itself retrieves only RGB.
 */
{
    // pixel() coverts a *qRgb* to a QColor behind the scenes rather than including the alpha channel.
    // Here I am explicitly making a QColor from RGBA, not RGB.
    QColor pixel_RGBA;
    pixel_RGBA = QColor::fromRgba(image.pixel(col, row));
    return pixel_RGBA;
}

//-------------------------------
void makeYellowImage(QImage originalImage)
/*
 * Copy the given image and make a new one filled with yellow.
 * This function is an example of how to access and set pixels of a QImage.
 * Input:  A QImage object of some loaded image.
 * Output: None; the new image is saved to a file named "yellow."
 */
{
    QImage yellowImage = originalImage;    // Copies the original image into a new QImage object.
    QColor origPixel, newPixel;
    int width;
    int height;

    // Retrieve the dimensions of the image with the width() and height() methods.
    width = originalImage.width();
    height = originalImage.height();

    // Iterate over the pixels of the image, for each row and column per row.
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // This function call retrieves a pixel with RGBA values from the original image.
            // You can print out values by uncommenting the printf() commands.
            origPixel = getRgbaPixel(col, row, yellowImage);
            //printf("Red: %d, Green: %d, Blue: %d, Alpha: %d\n",
            //        origPixel.red(), origPixel.green(), origPixel.blue(), origPixel.alpha());

            // Get a pixel ready with yellow with no transparency.
            newPixel.setRgb(255, 255, 0);
            newPixel.setAlpha(255);

            // Use that pixel's RGBA channels to write to a pixel location in the new image.
            yellowImage.setPixel(col, row, newPixel.rgba());
        }
    }

    yellowImage.save("../Images/yellow.png");
}

/* Description: makesStripeImage makes a .png that has two color in a stripe pattern that vary depending on the defines
 * at the top of this file where the size is based on the image provided.
 * Input: A QImage object of some loaded image and an integer of the size of the stripes desired.
 * Output: None; the new image is saved to a file named "stripes."
 */
void makeStripeImage(QImage originalImage, int sizeOfStripe){

    QImage stripesImage = originalImage;
    QColor oldPixel, newPixel;

    int width;
    int height;
    int Count = 0;    			//Used to represent color and 

    // Retrieve the dimensions of the image with the width() and height() methods.
    width = originalImage.width();
    height = originalImage.height();

    for (int row = 0; row < height; row++) {
        if(STRIPEDIRECTION == 0){               //Used for horizontal stripe selections to change colors at each
            if(row % sizeOfStripe == 0){        //selection length
                Count++;
            }
        }
        for (int col = 0; col < width; col++) {

            oldPixel = getRgbaPixel(col, row, stripesImage);    //Gets the old pixel for storing the original image

            if(Count % 2 == 0){                 //Used for alternating colors
                switch(COLOR1){                 //Finds the correct color based on the first selection
                    case 0:
                        newPixel.setRgb(255, 0, 0);
                        newPixel.setAlpha(255);
                        break;
                    case 1:
                        newPixel.setRgb(0, 255, 0);
                        newPixel.setAlpha(255);
                        break;
                    case 2:
                        newPixel.setRgb(0, 0, 255);
                        newPixel.setAlpha(255);
                        break;
                    default:
                        newPixel.setRgb(255, 255, 0);
                        newPixel.setAlpha(255);
                }
            }
            else{
                switch(COLOR2){                 //Finds the correct color based on the second selection
                    case 0:
                        newPixel.setRgb(255, 0, 0);
                        newPixel.setAlpha(255);
                        break;
                    case 1:
                        newPixel.setRgb(0, 255, 0);
                        newPixel.setAlpha(255);
                        break;
                    case 2:
                        newPixel.setRgb(0, 0, 255);
                        newPixel.setAlpha(255);
                        break;
                    default:
                        newPixel.setRgb(0, 255, 255);
                        newPixel.setAlpha(255);
                }
            }

            // Use that pixel's RGBA channels to write to a pixel location in the new image.
            stripesImage.setPixel(col, row, newPixel.rgba());
            if(STRIPEDIRECTION == 1) {  //Changes the column striped color vertical selected
                if (col % sizeOfStripe == 0) {
                    Count++;
                }
            }
        }
    }
    stripesImage.save("../Images/stripes.png"); //Saves the striped image
}

/* Description: makesInvertedImage makes a .png that that is inverted from the input image.
 * Input: A QImage object of some loaded image.
 * Output: None; the new image is saved to a file named "invert."
 */
void makeInvertedImage(QImage originalImage){

    QImage invertImage = originalImage;
    QColor oldPixel, newPixel;

    int width;
    int height;

    width = originalImage.width();
    height = originalImage.height();

    for (int row = 0; row < height; row++) {

        for (int col = 0; col < width; col++) {
            //Gathers the original image info
            oldPixel = getRgbaPixel(col, row, invertImage);

            //This uses the image original pixel values to inverse them
            newPixel.setRgb(255 - oldPixel.red() , 255 - oldPixel.green(), 255 - oldPixel.blue());
            newPixel.setAlpha(255);


            // Use that pixel's RGBA channels to write to a pixel location in the new image.
            invertImage.setPixel(col, row, newPixel.rgba());

        }
    }
    invertImage.save("../Images/invert.png"); //Saves new image as invert
}

/* Description: makesInvertedImage makes a .png that that is inverted from the input image.
 * Input: A QImage object of some loaded image, A QImage object of a imaged to be overlaid above the first image.
 * Output: None; the new image is saved to a file named "overlay."
 */
void imageOverlay(QImage originalImage, QImage overlayImage, int type){

    QImage newImage = originalImage;
    QColor bottomPixel, topPixel, newPixel;

    int width;
    int height;
    float topImpact;

    width = originalImage.width();
    height = originalImage.height();

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            //Gets the info for the top and bottom images
            bottomPixel = getRgbaPixel(col, row, originalImage);
            topPixel = getRgbaPixel(col, row, overlayImage);

            //gets the impact of transparency for the linear interpolation
            topImpact = topPixel.alpha() / 255;

            //gets the new values for each based on linear interpolation with the top and bottom images
            float nRed = (topImpact * topPixel.red() + (1 - topImpact) * bottomPixel.red());
            float nGreen = (topImpact * topPixel.green() + (1 - topImpact) * bottomPixel.green());
            float nBlue = (topImpact * topPixel.blue() + (1 - topImpact) * bottomPixel.blue());

            //set new pixel
            newPixel.setRgb(int(nRed), int(nGreen), int(nBlue));

            //new image pixel put in
            newImage.setPixel(col, row, newPixel.rgba());
        }
    }
    if(type == 1) {
        newImage.save("../Images/colorStatic.png"); //save new image as overlay
    }else
        newImage.save("../Images/overlay.png"); //save new image as overlay

}

/* Description: rotate makes a .png that that is rotated ROTATE degrees counter-clockwise from the input image. This
 * rotation is designed for 90 degree increments.
 * Input: A QImage object of some loaded image to be rotated.
 * Output: None; the new image is saved to a file named "rotate."
 */
void rotate(QImage originalImage){

    QImage rotatedImage;
    QColor oldPixel, newPixel;
    int pixelLocationRelativeToCenter[2];
    int newPixelLocation[2];

    int width;
    int height;

    width = originalImage.width();
    height = originalImage.height();

    //Set up the new image height and width
    if(ROTATE == 90 || ROTATE == 270) {
        rotatedImage = QImage(height, width, QImage::Format_ARGB32);
    }
    else{
        rotatedImage = originalImage;
    }

    for (int row = 0; row < height; row++) {

        for (int col = 0; col < width; col++) {
            //Gathers the original image info
            oldPixel = getRgbaPixel(col, row, originalImage);

            //This uses the image original pixel values to inverse them
            newPixel.setRgb(oldPixel.red(), oldPixel.green(), oldPixel.blue());
            newPixel.setAlpha(255);

            pixelLocationRelativeToCenter[0] = row - (height / 2);
            pixelLocationRelativeToCenter[1] = col - (width / 2);

            VectorMatrixMult(pixelLocationRelativeToCenter, newPixelLocation);


            // Use that pixel's RGBA channels to write to a pixel location in the new image.
            if(ROTATE == 90) {
                rotatedImage.setPixel(newPixelLocation[0] + height/2, newPixelLocation[1] + width/2, newPixel.rgba());
            }
            else if(ROTATE == 180){
                rotatedImage.setPixel(width - (newPixelLocation[0] + width/2) - 1, (newPixelLocation[1] + height/2) - 1, newPixel.rgba());
            }
            else if(ROTATE == 270){
                rotatedImage.setPixel(height - (newPixelLocation[0] + height/2) - 1, width - (newPixelLocation[1] + width/2)- 1, newPixel.rgba());
            }
        }
    }
    rotatedImage.save("../Images/rotate.png"); //Saves new image as rotate90
}

/* Description: This file takes the left half of an image and mirrors it over the right half of the photo
 *
 * Input: The input to this function is the image in which is intended to be manipulated
 * Output: There is no output but a .png is saved by the name of "leftMirror"
 */
void mirrorLeft(QImage originalImage){
    QImage leftImage = originalImage;    // Copies the original image into a new QImage object.
    QColor origPixel, newPixel;
    int width;
    int height;

    // Retrieve the dimensions of the image with the width() and height() methods.
    width = originalImage.width();
    height = originalImage.height();

    // Iterate over the pixels of the image, for each row and column per row.
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width / 2; col++)
        {
            // This function call retrieves a pixel with RGBA values from the original image.
            // You can print out values by uncommenting the printf() commands.
            origPixel = getRgbaPixel(col, row, leftImage);
            //printf("Red: %d, Green: %d, Blue: %d, Alpha: %d\n",
            //        origPixel.red(), origPixel.green(), origPixel.blue(), origPixel.alpha());

            // Get a pixel ready with yellow with no transparency.
            newPixel.setRgb(origPixel.red(), origPixel.green(), origPixel.blue());
            newPixel.setAlpha(255);

            // Use that pixel's RGBA channels to write to a pixel location in the new image.
            leftImage.setPixel(col, row, newPixel.rgba());
            leftImage.setPixel(width - col - 1, row, newPixel.rgba());
        }
    }

    leftImage.save("../Images/leftMirror.png");

}

/* colorStatic()
 * Des: This function takes an image and adds pixel confetti that is randomly patterned over the image.
 * Input: This is takes in an image that will have the pixel confetti applied to it.
 * Output: No Output. This function creates a file called colorStatic.png
 */
void colorStatic(QImage originalImage){

    srand(time(0));

    QImage leftImage = originalImage;    // Copies the original image into a new QImage object.
    QColor newPixel;
    int width;
    int height;

    // Retrieve the dimensions of the image with the width() and height() methods.
    width = originalImage.width();
    height = originalImage.height();

    int randColor;
    int randTran;

    // Iterate over the pixels of the image, for each row and column per row.
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++) {

            randColor = rand() % 3;
            randTran = rand() % 256;
            // Get a pixel ready with original image with no transparency.
            if (randColor == 0) {
                newPixel.setRgb(225, 0, 0);
                newPixel.setAlpha(randTran);
            } else if (randColor == 1) {
                newPixel.setRgb(0, 255, 0);
                newPixel.setAlpha(randTran);
            } else {
                newPixel.setRgb(0, 0, 255);
                newPixel.setAlpha(randTran);
            }

            // Use that pixel's RGBA channels to write the mirror to a pixel location in the new image.
            leftImage.setPixel(col, row, newPixel.rgba());
        }
    }

    imageOverlay(originalImage, leftImage, 1);
}

//-------------------------------
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);   // Main application that runs all of the Qt code.
    QLabel label;                   // Label widget to put the image in for displaying.

    // Load an image by its path (relative to the bin folder where code is being built) and the filename.
    // Need to go back a directory with .. then access the Images folder because code execution occurs in the bin folder.
    QImage image = QImage("../Images/fluff.png");
    QImage image2 = QImage("../Images/Shia.png");

    // Call functions which creates and saves a yellow image, striped image, inverted image, and
    // an image with another overlaid above it of the same size as the input image.
    makeYellowImage(image);
    makeStripeImage(image, STRIPETHICKNESS);
    makeInvertedImage(image);
    imageOverlay(image, image2, 0);
    rotate(image);
    mirrorLeft(image);
    colorStatic(image2);

    // Display an image as a part of a Qt GUI.
    // A QPixmap is another image-like class.  Add one from the QImage to the QLabel.
    label.setPixmap(QPixmap::fromImage(image));
    // Actually display the label widget containing the image.
    label.show();

    // This launches the GUI this program set up.
    return app.exec();
}
