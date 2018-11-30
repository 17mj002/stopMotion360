//
//  Theta.hpp
//  stopMotion360_v02
//
//  Created by 菊池康太 on 2018/11/16.
//

#ifndef Theta_hpp
#define Theta_hpp

#include "ofMain.h"
#include <stdio.h>

#define THETA_DEV_NAME "THETA UVC HD Blender"

class Theta {
private:
    string devicesName;
    bool isDevices;
    
public:
    //Theta();
    Theta();
    void setup();
    void draw();
    void update();
    ofImage frameCpture();
    void reConnect(bool isCheck);
    
    int camW, camH;
    int x, y, w, h;
    ofVideoGrabber cam;
    
    ofImage backImg;
    ofImage frameImg01;
    ofImage frameImg02;
};

#endif /* Theta_hpp */
