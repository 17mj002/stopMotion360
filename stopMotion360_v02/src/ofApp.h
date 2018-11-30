#pragma once

#include "ofMain.h"
#include "Theta.hpp"
#include "BackGSubtractor.hpp"
#include "OpticalFlow.hpp"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
        void mouseDragged(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void getBackground_first();
        void getFirstImg();
        void getSecondImg();
        void getNewImg();
        void updateContours();
        void saveImage(ofImage img);
        void selectSaveDirctory();
        void drawBottomTab();
        void drawToImage();
        void isAlert();
    
    bool pushSpace, isbackImg, isFirstImg, isSecondImg, isDragge, isReCap, reCapFlag, isReNewCap;
    
    Theta theta;
    BackGSubtractor bgSub;
    OpticalFlow opf;
    
    ofImage backImg;
    ofImage firstImg;
    ofImage secondImg;
    ofImage oldImg;
    
    ofFileDialogResult result;
    int saveImageCount;
    
    ofxPanel gui;
    ofxFloatSlider thresholdValue;
    ofxIntSlider kSize;
    ofxButton resetBackButton;
    ofxButton resetDirctory;
    ofxToggle canSave;
    ofxToggle showFlow;
    ofxFloatSlider alertLevel;
    
    ofxFloatSlider pyrScale;
    ofxIntSlider levels;
    ofxIntSlider winsize;
    ofxIntSlider iterations;
    ofxIntSlider polyN;
    ofxFloatSlider polySigma;
    ofxToggle OPTFLOW_FARNEBACK_GAUSSIAN;
    
    ofSoundPlayer shutterSound;
    
    ofFile file;
};
