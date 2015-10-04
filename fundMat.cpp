/* Written by: Yash Sanjay Bhalgat
 * Date: 4/10/2015
 */

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

void x(){
	Mat A1 = imread("calib_30/cam--0-0.tiff",0);
	Mat A2 = imread("calib_30/cam--1-0.tiff",0);
	
	Size patternsize(9,6); //interior number of corners
	vector<Point2f> corners1, corners2;
	
	bool patternfound1 = findChessboardCorners(A1, patternsize, corners1, CALIB_CB_ADAPTIVE_THRESH+CALIB_CB_NORMALIZE_IMAGE+CALIB_CB_FAST_CHECK);

	if(patternfound1){
	  cornerSubPix(A1, corners1, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
	}

	bool patternfound2 = findChessboardCorners(A2, patternsize, corners2, CALIB_CB_ADAPTIVE_THRESH+CALIB_CB_NORMALIZE_IMAGE+CALIB_CB_FAST_CHECK);

	if(patternfound2){
	  cornerSubPix(A2, corners2, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
	}
	
	Mat fundamental_matrix = findFundamentalMat(corners1, corners2, FM_LMEDS, 3, 0.95);
	
	cout<<fundamental_matrix<<endl;
	for(int i=0; i<54; i++){
		cout<<corners1[i]<<"   "<<corners2[i]<<endl;
	}
	
	drawChessboardCorners(A1, patternsize, Mat(corners1), patternfound1);
	imshow("corners1", A1);
	drawChessboardCorners(A2, patternsize, Mat(corners2), patternfound2);
	imshow("corners2", A2);
	waitKey(0);
}

int main( int argc, char** argv )
{
	namedWindow( "corners1" , CV_WINDOW_NORMAL);
	namedWindow( "corners2" , CV_WINDOW_NORMAL);
	x();
}
