#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
    vector<vector<Point> > contours;
    int largest_area=0;
    int largest_contour_index=0;
    Rect bounding_rect;
    vector<Vec4i> hierarchy;

    Mat Image;
    Mat mask;
//        VideoCapture video("C:/Users/ksrnd/Desktop/Light/KakaoTalk_Video_20190319_1346_26_975.mp4");
        VideoCapture video(1);
    while (1) {
//        Mat Image = imread("C:/Users/ksrnd/Desktop/Light/Original_screenshot_19.03.2019.png");

        video >> Image;
        Mat thr(Image.rows,Image.cols,CV_8UC1);
        Mat dst(Image.rows,Image.cols,CV_8UC1,Scalar::all(0));
        Mat hsv,gray;

        Mat imageROI(Image, Rect(10,120,500,250));
        imshow("rec",imageROI);
        cvtColor(imageROI, gray, COLOR_BGR2GRAY); //Convert the captured frame from BGR to HSV

        blur(gray, mask, Size(3, 3));
        Canny(gray, mask, 70, 150, 3);

        findContours( mask, contours,hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);

        for( int i = 0; i< contours.size(); i++ ) {

            double a =contourArea( contours[i],false);  //  Find the area of contour
            double arc = arcLength( contours[i], false);
            if( arc > largest_area ){

                largest_area=arc;
                largest_contour_index=i;                //Store the index of largest contour
                bounding_rect=boundingRect(contours[i]); // Find the bounding rectangle for biggest contour

            }
        }

        //       drawContours( Image, contours,largest_contour_index, Scalar(0,255,255), 1, 8, hierarchy,INT_MAX );
        rectangle(imageROI, bounding_rect,  Scalar(0,255,255),1, 4,0);

        imshow("Detect", mask);
        imshow("Original",Image);

        if ( waitKey(1) == 27)break;
    }

}
