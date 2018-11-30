//
//  OpticalFlow.cpp
//  stopMotion360_v02
//
//  Created by 菊池康太 on 2018/11/29.
//

#include "OpticalFlow.hpp"

OpticalFlow::OpticalFlow(){
    curFlow = &farneback;
}


void OpticalFlow::setFirstImage(ofImage img){
    ofImage cimg;
    //unsigned char *pixels = img.getPixels().getData();
    src01.setFromPixels(img.getPixels().getData(), img.getWidth(), img.getHeight(), OF_IMAGE_COLOR);
    srcMat01 = toCv(src01);
}

void OpticalFlow::setSecondImage(ofImage img){
    ofImage c2img;
    src02.setFromPixels(img.getPixels().getData(), img.getWidth(), img.getHeight(), OF_IMAGE_COLOR);//c2img.clone(img);
    srcMat02 = toCv(src02);
}


void OpticalFlow::updateFarneback(float pyrScale,int levels,int winsize,int iterations,int polyN,float polySigma,bool OPTFLOW_FARNEBACK_GAUSSIAN){
    
    curFlow = &farneback;
    farneback.setPyramidScale(pyrScale);
    farneback.setNumLevels(levels);
    farneback.setWindowSize(winsize);
    farneback.setNumIterations(iterations);
    farneback.setPolyN(polyN);
    farneback.setPolySigma(polySigma);
    farneback.setUseGaussian(OPTFLOW_FARNEBACK_GAUSSIAN);
    
     
    averageFlow = farneback.getAverageFlow().length();
    curFlow->calcOpticalFlow(srcMat01, srcMat02);
}

void OpticalFlow::drawOpticalFlow(int x, int y, int w, int h){
    ofPushStyle();
    ofSetColor(255,0,0);
    curFlow->draw(x,y,w,h);
    ofPopStyle();
}

float OpticalFlow::getAverage(){
    return averageFlow;
}


