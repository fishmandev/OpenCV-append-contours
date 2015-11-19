#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
    Mat src[argc - 1], gray[argc - 1];
    int dstCols = 0, imgIndex = 0;
    char dstFilename[] = "result.png";

    for (int nArg = 1; nArg < argc; nArg++) {
        src[imgIndex] = imread(argv[nArg], CV_LOAD_IMAGE_COLOR);

        if (!src[imgIndex].data) {
            printf("Could not open the image file '%s'", argv[nArg]);
            return -1;
        }

        cvtColor(src[imgIndex], gray[imgIndex], CV_RGB2GRAY);
        threshold(gray[imgIndex], gray[imgIndex], 250, 255, CV_THRESH_BINARY);
        bitwise_not(gray[imgIndex], gray[imgIndex]);
        dstCols += src[imgIndex].cols;
        imgIndex++;
    }

    Mat tmp(cvSize(dstCols, src[0].rows), CV_8UC1, Scalar(255));
    for (int imgIdx = 0; imgIdx < imgIndex; imgIdx++) {
        vector<vector<Point> > contours;
        findContours(gray[imgIdx].clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
        drawContours(tmp, contours, 0, Scalar(0), 1, 8, noArray(), 0, Point(imgIdx * gray[imgIdx].cols, 0));
    }

    imwrite(dstFilename, tmp);

    return 0;
}