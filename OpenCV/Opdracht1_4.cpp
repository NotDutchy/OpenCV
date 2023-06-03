#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

///////////////  Warp Images  //////////////////////

/*void main() {

	string path = "Resources/NameTag.jpg";
	Mat img = imread(path);
	Mat matrix, imgWarp, imgResize1, imgResize2;
	float w = 1600, h = 1100;

	Point2f src[4] = { {1151,1116},{2737, 935},{1540,2216},{3281,1730} }; 
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));

	for (int i = 0; i < 4; i++)
	{
		circle(img, src[i], 10, Scalar(0, 0, 255), FILLED);
	}

	resize(imgWarp, imgResize1, Size(), 0.5, 0.5);
	resize(img, imgResize2, Size(), 0.3, 0.3);


	imshow("Image Resize", imgResize1);
	imshow("Image", imgResize2);
	waitKey(0);

}*/