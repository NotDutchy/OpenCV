#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void main()
{
	string path = "Resources/GangsterGuus.JPG";
	Mat img = imread(path);
	Mat imgResize, imgCrop;

	resize(img, imgResize, Size(), 0.3, 0.3);

	Rect roi(700, 600, 410, 520);
	imgCrop = img(roi);

	imshow("Image", img);
	imshow("Image Resize", imgResize);
	imshow("Image crop", imgCrop);

	waitKey(0);
}