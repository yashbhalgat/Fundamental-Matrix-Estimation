A1 = imread('calib_30/cam--0-0.tiff');
A2 = imread('calib_30/cam--1-0.tiff');
A1 = rgb2gray(A1);
A2 = rgb2gray(A2);
[imagePoints,boardSize,pairsUsed] = detectCheckerboardPoints(A1,A2);
F = estimateFundamentalMatrix(imagePoints(:,:,1),imagePoints(:,:,2));
