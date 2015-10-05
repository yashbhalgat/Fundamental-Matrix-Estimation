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
#include <string>

using namespace cv;
using namespace std;

void calcFundMat(int i){
	stringstream s; // stringstream used for the conversion
	s << i;
	
	Mat A1 = imread("calib_30/cam--0-"+s.str()+".tiff",0);
	Mat A2 = imread("calib_30/cam--1-"+s.str()+".tiff",0);
	
	Size patternsize(9,6); //interior number of corners
	
	vector<vector<Point3f> > objectPoints;
    vector<vector<Point2f> > imagePoints1, imagePoints2;
	vector<Point2f> corners1, corners2;
	
	vector<Point3f> obj;
    for (int j=0; j<54; j++)
    {
        obj.push_back(Point3f(j/6, j%9, 0.0f));
    }
	
	
	bool patternfound1 = findChessboardCorners(A1, patternsize, corners1, CALIB_CB_ADAPTIVE_THRESH+CALIB_CB_NORMALIZE_IMAGE+CALIB_CB_FAST_CHECK);

	if(patternfound1){
		cornerSubPix(A1, corners1, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
		imagePoints1.push_back(corners1);
		objectPoints.push_back(obj);
	}

	bool patternfound2 = findChessboardCorners(A2, patternsize, corners2, CALIB_CB_ADAPTIVE_THRESH+CALIB_CB_NORMALIZE_IMAGE+CALIB_CB_FAST_CHECK);

	if(patternfound2){
		cornerSubPix(A2, corners2, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
		imagePoints2.push_back(corners2);
	}
	
	Mat CM1 = Mat(3, 3, CV_64FC1);
    Mat CM2 = Mat(3, 3, CV_64FC1);
    Mat D1, D2;
    Mat R, T, E, F;
	
	stereoCalibrate(objectPoints, imagePoints1, imagePoints2, CM1, D1, CM2, D2, A1.size(), R, T, E, F, cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 100, 1e-5), CV_CALIB_SAME_FOCAL_LENGTH | CV_CALIB_ZERO_TANGENT_DIST);
	
	
	//Mat fundamental_matrix = findFundamentalMat(corners1, corners2, FM_RANSAC, 3, 0.95);
	
	cout<<i<<endl;
	cout<<F<<endl;
	cout<<endl;
	//for(int i=0; i<54; i++){
	//	cout<<corners1[i]<<"   "<<corners2[i]<<endl;
	//}
	
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
	for(int k=0;k<8;k++) calcFundMat(k);
	//calcFundMat(7);
}
