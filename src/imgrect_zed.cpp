//
// Created by rpng on 7/26/16.
// Delete debug information 11/07/16
//

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <boost/filesystem.hpp>

#include <iostream>
#include <sstream>
#include <string>



using namespace cv;
using namespace std;



int main( int argc, char** argv ){

    // read the images
    string filename1 = "/home/linde/project/imgrect/data/zed/001.png";
    string filename2 = "/home/linde/project/imgrect/data/zed/002.png";

    Mat img1,img2;
    img1 = imread(filename1,IMREAD_GRAYSCALE);
    img2 = imread(filename2,IMREAD_GRAYSCALE);

    imshow("before Left", img1);
    imshow("before Right", img2);

    waitKey(0);

    Mat K_1 = (Mat_<double>(3,3) << 7.353913810364e+02, 0.000000000000e+00, 6.692286987385e+02,
                                    0.000000000000e+00, 7.161078587206e+02, 3.774531727097e+02,
                                    0.000000000000e+00, 0.000000000000e+00, 1.000000000000e+00);

    Mat K_2 = (Mat_<double>(3,3) << 7.167200148141e+02, 9.740939725568e-03, 7.027806452102e+02,
                                    0.000000000000e+00, 6.965268947538e+02, 3.926605129413e+02,
                                    0.000000000000e+00, 0.000000000000e+00, 1.000000000000e+00);

    Mat R_rect1 = (Mat_<double>(3,3) << 9.826816289450e-01, 2.444704761493e-02, 1.836822201437e-01,
                                        -2.339291679524e-02, 9.996951034959e-01, -7.903890819248e-03,
                                        -1.838194428722e-01, 3.470145412675e-03, 9.829539005025e-01);

    Mat R_rect2 = (Mat_<double>(3,3) << 9.836675825477e-01, 2.608950769921e-02, 1.780938646691e-01,
                                        -2.711049454173e-02, 9.996269917353e-01, 3.301284586158e-03,
                                        -1.779413052961e-01, -8.075579374197e-03, 9.840079658658e-01);

    Mat P_rect1 = (Mat_<double>(3,4) << 4.328220393532e+02, 0.000000000000e+00, 3.413039855957e+02, 0.000000000000e+00,
                                        0.000000000000e+00, 4.328220393532e+02, 2.350234909058e+02, 0.000000000000e+00,
                                        0.000000000000e+00, 0.000000000000e+00, 1.000000000000e+00, 0.000000000000e+00);

    Mat P_rect2 = (Mat_<double>(3,4) << 4.328220393532e+02, 0.000000000000e+00, 3.413039855957e+02, -4.963830275321e+01,
                                        0.000000000000e+00, 4.328220393532e+02, 2.350234909058e+02, 0.000000000000e+00,
                                        0.000000000000e+00, 0.000000000000e+00, 1.000000000000e+00, 0.000000000000e+00);
    Mat D_1 = (Mat_<double>(1,5) << -1.966589467446e-01, 3.488312753209e-02, -1.109990416874e-03, 2.434258171672e-03, 0.000000000000e+00);

    Mat D_2 = (Mat_<double>(1,5) << -1.928912817715e-01, 3.385670991895e-02, -1.063267710287e-03, 3.951352434793e-03, 1.842606618655e-04);


    double cols = 9.140000000000e+02;
    double rows = 4.480000000000e+02;

    Size S_rect1(cols,rows);
    Size S_rect2(cols,rows);

    Mat matL1, matL2;
    Mat matR1, matR2;

    cv::initUndistortRectifyMap(K_1, D_1, R_rect1, P_rect1, S_rect1, CV_32F, matL1, matL2);
    cv::initUndistortRectifyMap(K_2, D_2, R_rect2, P_rect2, S_rect2, CV_32F, matR1, matR2);

    Mat matLrect, matRrect;

    cv::remap(img1, matLrect, matL1, matL2, INTER_LINEAR);
    cv::remap(img2, matRrect, matR1, matR2, INTER_LINEAR);

    imshow("after Left", matLrect);
    imshow("after Right", matRrect);

    waitKey(0);



return 0;
}
