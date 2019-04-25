#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;


Mat src,src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(255);
void thresh_callback(int,void*);

int main()
{
    src = imread("../../../dataset/5000.jpg");
    if(src.empty())
        return -1;
    cvtColor(src,src_gray,COLOR_BGR2GRAY);
    blur(src_gray,src_gray,Size(3,3));

    namedWindow("source",WINDOW_AUTOSIZE);
    imshow("source",src);

    createTrackbar("canny thresh:","source",&thresh,max_thresh,thresh_callback);
    thresh_callback(0,0);

    waitKey(0);

    return 0;
}

void thresh_callback(int,void*)
{
    Mat canny_output;
    vector<vector<Point>> contours;

    Canny(src_gray,canny_output,thresh,thresh*2,3);

    findContours(canny_output,contours,CV_RETR_EXTERNAL,
                 CHAIN_APPROX_SIMPLE,Point(0,0));

    Mat drawing = Mat::zeros(canny_output.size(),CV_8UC3);

    for(size_t i = 0;i < contours.size();i++){
        Scalar color = Scalar(rng.uniform(0,255),
                              rng.uniform(0,255),
                              rng.uniform(0,255));
        drawContours(drawing,contours,(int)i,color,2,8,noArray(),0,Point());

    }
    namedWindow("contours",WINDOW_AUTOSIZE);
    imshow("contours",drawing);
}
