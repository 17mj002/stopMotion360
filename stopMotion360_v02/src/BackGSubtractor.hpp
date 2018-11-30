//
//  BackgroundSubtractor.hpp
//  stopMotion360_v02
//
//  Created by 菊池康太 on 2018/11/16.
//

#ifndef BackGSubtractor_hpp
#define BackGSubtractor_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

using namespace cv;
using namespace ofxCv;

class BackGSubtractor{
    int num, num02;
    float area, maxArea, area02, maxArea02;
    ofPoint center01, center02;
    
public:
    BackGSubtractor();
    void setBackground(ofImage _bk);
    void setFirstFrame(ofImage _src);
    void setSecondFrame(ofImage _src);
    void getContours(float thresholdValue, int kSize);
    void getFirstContours(ofImage _src01, float thresholdValue, int kSize);
    void getSecondContours(ofImage _src02, float thresholdValue, int kSize);
    void getFirstCenter();
    void getSecondCenter();
    void drawDiffCenter(int x, int y);
    void drawDiffImg(int x, int y);
    bool isRangeOver(float range);
    void flann(ofImage img01, ofImage img02);
    

    ofImage backImg, src01Img, src02Img;
    Mat bgMat, bgMatGray;
    Mat srcMat01, srcGrayMat01, diff01, threshold01, thresBlur01;
    Mat srcMat02, srcGrayMat02, diff02, threshold02, thresBlur02;
    std::vector<std::vector<cv::Point>> contours01, contours02;
    ofImage thresImg01, thresImg02;
    ofPolyline contoursLine01, contoursLine02;

};
#endif /* BackgroundSubtractor_hpp */
