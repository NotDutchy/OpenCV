#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//void main() {
//	Mat img = imread("resources/ballstripes.png");
//	Mat diout, erout, canOut, imgGray;
//
//	cvtColor(img, imgGray, COLOR_BGR2GRAY);
//
//	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
//	dilate(imgGray, diout, kernel);
//	erode(diout, erout, kernel);
//
//	imshow("nromal", imgGray);
//	imshow("dilate", diout);
//	imshow("erode", erout);
//
//	waitKey(0);
//}