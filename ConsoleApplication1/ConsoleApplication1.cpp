#include "opencv2/imgcodecs.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>
#include <opencv2/tracking.hpp>
#include <stdio.h>
#include <iostream>
// we're NOT "using namespace std;" here, to avoid collisions between the beta variable and std::beta in c++17
using std::cin;
using std::cout;
using std::endl;

using namespace cv;
using namespace std;

#define w 100

void MyFilledCircle(Mat img, Point center);

int main(int argc, char** argv)
{
    Mat image = imread("C:\\Users\\JR\\Pictures\\33iummvno5t31.png");
    if (image.empty())
    {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }
    
    imshow("Original Image", image);
    waitKey();
    
    MyFilledCircle(image, Point(image.cols / 2, image.rows/ 2));
    imshow("Original Image", image);

    putText(image,
        "Pumpkin man!!!",
        Point(image.cols / 2, image.rows / 2),
        FONT_HERSHEY_COMPLEX,
        1,
        COLORMAP_PINK,
        5,
        8);

    imshow("Original Image", image);
    waitKey();
    
}

void MyFilledCircle(Mat img, Point center)
{
    circle(img,
        center,
        img.rows/8,
        Scalar(0, 0, 255),
        FILLED,
        LINE_8);
}
