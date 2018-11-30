//
//  OpticalFlow.hpp
//  stopMotion360_v02
//
//  Created by 菊池康太 on 2018/11/29.
//

#ifndef OpticalFlow_hpp
#define OpticalFlow_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxCv.h"
using namespace cv;
using namespace ofxCv;

class OpticalFlow {
private:
    ofImage src01;
    ofImage src02;
    
    Mat srcMat01;
    Mat srcMat02;
    
public:
    OpticalFlow();
    void setFirstImage(ofImage img);
    void setSecondImage(ofImage img);
    void updateFarneback(float pyrScale,int levels,int winsize,int iterations,int polyN,float polySigma,bool OPTFLOW_FARNEBACK_GAUSSIAN);
    void drawOpticalFlow(int x, int y, int w, int h);
    float getAverage();
    
    FlowFarneback farneback;
    Flow* curFlow;
    float averageFlow;
};



#endif /* OpticalFlow_hpp */
