#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/*void main() {
	Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));

	putText(img, "Computer vision ", Point(30, 100), FONT_HERSHEY_DUPLEX, 1.75, Scalar(255, 69, 255), 3);
	rectangle(img, Point(20, 50), Point(492, 120), Scalar(0, 0, 0), 2);

	circle(img, Point(256, 320), 100, Scalar(0, 0, 0), 6);
	circle(img, Point(220, 300), 20, Scalar(0, 0, 0), 4);
	circle(img, Point(292, 300), 20, Scalar(0, 0, 0), 4);
	circle(img, Point(256, 360), 30, Scalar(0, 0, 0), 4);

	line(img, Point(246, 290), Point(200, 270), Scalar(0, 0, 0), 3);
	line(img, Point(266, 290), Point(312, 270), Scalar(0, 0, 0), 3);

	imshow("Image", img);
	waitKey(0);
}*/