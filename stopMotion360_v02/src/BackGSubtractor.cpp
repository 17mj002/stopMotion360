//
//  BackgroundSubtractor.cpp
//  stopMotion360_v02
//
//  Created by 菊池康太 on 2018/11/16.
//

#include "BackGSubtractor.hpp"

BackGSubtractor::BackGSubtractor(){
}

void BackGSubtractor::setBackground(ofImage _bk){
    backImg = _bk;
    bgMat = toCv(_bk);
    cvtColor(bgMat, bgMatGray, CV_RGB2GRAY);
}

void BackGSubtractor::setFirstFrame(ofImage _src){
    srcMat01 = toCv(_src);
    
    cvtColor(srcMat01, srcGrayMat01, CV_RGB2GRAY);
    absdiff(bgMatGray, srcGrayMat01, diff01);
    
}

void BackGSubtractor::setSecondFrame(ofImage _src){
    srcMat02 = toCv(_src);
    cvtColor(srcMat02, srcGrayMat02, CV_RGB2GRAY);
    absdiff(bgMatGray, srcGrayMat02, diff02);
}

void BackGSubtractor::getContours(float thresholdValue, int kSize){
    threshold(diff01, threshold01, thresholdValue, 255, THRESH_BINARY);
    threshold(diff02, threshold02, thresholdValue, 255, THRESH_BINARY);
    blur(threshold01, thresBlur01, cv::Size(kSize,kSize));
    blur(threshold02, thresBlur02, cv::Size(kSize,kSize));
    findContours(thresBlur01, contours01, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    findContours(thresBlur02, contours02, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    getFirstCenter();
    getSecondCenter();
}

void BackGSubtractor::getFirstContours(ofImage _src01,float thresholdValue, int kSize){
    src01Img = _src01;
    src01Img.resize((src01Img.getWidth()*ofGetHeight()/2)/src01Img.getHeight(), ofGetHeight()/2);
    
    srcMat01 = toCv(src01Img);
    cvtColor(srcMat01, srcGrayMat01, CV_RGB2GRAY);
    absdiff(bgMatGray, srcGrayMat01, diff01);
    threshold(diff01, threshold01, thresholdValue, 255, THRESH_BINARY);
    threshold01 = ~threshold01;
    blur(threshold01, thresBlur01, cv::Size(kSize,kSize));
    findContours(thresBlur01, contours01, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    getFirstCenter();
}

void BackGSubtractor::getSecondContours(ofImage _src02,float thresholdValue, int kSize){
    src02Img = _src02;
    src02Img.resize((src02Img.getWidth()*ofGetHeight()/2)/src02Img.getHeight(), ofGetHeight()/2);
    srcMat02 = toCv(src02Img);
    cvtColor(srcMat02, srcGrayMat02, CV_RGB2GRAY);
    absdiff(bgMatGray, srcGrayMat02, diff02);
    threshold(diff02, threshold02, thresholdValue, 255, THRESH_BINARY);
    threshold02 = ~threshold02;
    blur(threshold02, thresBlur02, cv::Size(kSize,kSize));
    findContours(thresBlur02, contours02, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    getSecondCenter();

}

void BackGSubtractor::getFirstCenter(){
    for(int i = 0; i < contours01.size(); i++){
        area = contourArea(contours01[i]);
        if(area > maxArea){
            maxArea = area;
            num = i;
        }
    }
    if(contours01.size()>0){
        contoursLine01 = toOf(contours01[num]);
        center01 = contoursLine01.getCentroid2D();
    }
}

void BackGSubtractor::getSecondCenter(){
    for(int i = 0; i < contours02.size(); i++){
        area02 = contourArea(contours02[i]);
        if(area02 > maxArea02){
            maxArea02 = area02;
            num02 = i;
        }
    }
    if(contours02.size()>0){
        contoursLine02 = toOf(contours02[num02]);
        center02 = contoursLine02.getCentroid2D();
    }
}

void BackGSubtractor::drawDiffImg(int x, int y){
    ofPushMatrix();
    ofPushStyle();
        ofTranslate(x, y);
        ofEnableAlphaBlending();
        ofSetColor(255, 255, 255, 255);
        src02Img.draw(0,0);
        ofSetColor(255, 255, 255, 100);
        src01Img.draw(0,0);
    ofPopStyle();
    ofPopMatrix();
}


void BackGSubtractor::drawDiffCenter(int x, int y){
    ofPushMatrix();
    ofPushStyle();
        ofTranslate(x, y);
        ofSetColor(255, 0, 0);
        ofSetLineWidth(3);
        contoursLine01.draw();
        contoursLine02.draw();
        ofSetColor(0, 255, 0);
        ofSetLineWidth(1);
        ofDrawLine(center01.x, center01.y, center02.x, center02.y);
    ofPopStyle();
    ofPopMatrix();
}


bool BackGSubtractor::isRangeOver(float range){
    
    if(abs(ofDist(center01.x, center01.y, center02.x, center02.y)) > range){
        return true;
    }
    return false;
}

void BackGSubtractor::flann(ofImage img01, ofImage img02){
    Mat img_1 = toCv(img01);
    Mat img_2 = toCv(img02);
    Mat imgGray_1, imgGray_2;
    cvtColor(img_1, imgGray_1, CV_RGB2GRAY);
    cvtColor(img_2, imgGray_2, CV_RGB2GRAY);
    
    int minHessian = 400;
    
    
}



