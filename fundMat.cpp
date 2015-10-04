#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
	namedWindow( "corners" , CV_WINDOW_NORMAL);
	Mat A1 = imread("calib_30/cam--0-0.tiff",0);
	Mat A2 = imread("calib_30/cam--1-0.tiff",0);
	
	Size patternsize(9,6); //interior number of corners
	vector<Point2f> corners;
	
	bool patternfound = findChessboardCorners(A1, patternsize, corners, CALIB_CB_ADAPTIVE_THRESH+CALIB_CB_NORMALIZE_IMAGE+CALIB_CB_FAST_CHECK);

	if(patternfound)
	  cornerSubPix(A1, corners, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

	drawChessboardCorners(A1, patternsize, Mat(corners), patternfound);
	imshow("corners", A1);
	waitKey(0);
}
