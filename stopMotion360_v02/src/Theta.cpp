//
//  Theta.cpp
//  stopMotion360_v02
//
//  Created by 菊池康太 on 2018/11/16.
//

#include "Theta.hpp"

Theta::Theta(){
    isDevices = false;
}

//--------------------------------------------------------------
void Theta::setup(){
    cam.setVerbose(true);
    cam.listDevices();

    if(cam.isInitialized() == false){
        cout << "Initalizing cam" << endl;
        int index = 0;
        vector<ofVideoDevice> devices = cam.listDevices();
        if(devices.size() > 0) isDevices = true;
        else isDevices = false;
        
        for(int i=0; i<devices.size(); i++){
            ofVideoDevice& device = devices.at(i);
            cout << i  << ":" << device.deviceName << ":" << endl;
            devicesName = device.deviceName;
            if(device.deviceName.find(THETA_DEV_NAME) != std::string::npos){
                index = i;
            }
        }
        if(devicesName == THETA_DEV_NAME){
            camW = 1920;
            camH = 960;
        } else {
            camW = cam.getWidth();
            camH = cam.getHeight();
        }
        cam.setDeviceID(index);
        cam.initGrabber(camW, camH);
        return;
    }
}

//--------------------------------------------------------------
void Theta::update(){
    cam.update();
}

//--------------------------------------------------------------
void Theta::draw(){
    if(isDevices == false){
        ofPushStyle();
        ofSetColor(0);
        ofSetLineWidth(3);
        ofNoFill();
        ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight()/2);
        ofPopStyle();
        ofDrawBitmapString("DEVICE NOT FOUND", ofGetWidth()/4, ofGetHeight()/4);
    } else {
        //        if(devicesName != THETA_DEV_NAME){
        //            w = (cam.getWidth()*(ofGetHeight()/2)) / cam.getHeight();
        //            cam.draw(x, y, w, ofGetHeight()/2);
        //        } else {
        //            w = (cam.getWidth()*(ofGetHeight()/2)) / cam.getHeight();
        //            cam.draw(x, y, w, ofGetHeight()/2);
        //        }
        
        w = (cam.getWidth()*(ofGetHeight()/2)) / cam.getHeight();
        x = (ofGetWidth()-w)/2;
        y = 0;
        h = ofGetHeight()/2;
        cam.draw(x, y, w, ofGetHeight()/2);
    }
}

//--------------------------------------------------------------
ofImage Theta::frameCpture(){
    ofImage img;
    img.setFromPixels(cam.getPixels().getData(), cam.getWidth(), cam.getHeight(), OF_IMAGE_COLOR);
    return img;
}

//--------------------------------------------------------------
void Theta::reConnect(bool isCheck){
    if(isCheck){
        setup();
    }
}




