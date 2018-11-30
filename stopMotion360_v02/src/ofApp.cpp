#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetDataPathRoot("../Resources/data/");
    ofEnableAlphaBlending();
    isbackImg, isFirstImg, isSecondImg, isDragge, isReCap, isReNewCap = false;
    reCapFlag = true;
    
    theta.setup();
    shutterSound.load("Camera-Phone03-1.mp3");
    
    gui.setup();
    //gui.setWidthElements(20);
    //gui.add(thresholdValue.setup("thresholdValue", 30, 0, 255));
    //gui.add(kSize.setup("K_Size", 6, 1, 50));
    //gui.add(resetBackButton.setup("Background Reset"));
    gui.add(resetDirctory.setup("Directory Reset"));
    gui.add(canSave.setup("canSave", false));
    gui.add(pyrScale.setup("pyrScale", .5, 0, 1));
    gui.add(levels.setup("levels", 4, 1, 8));
    gui.add(winsize.setup("winsize", 8, 4, 64));
    gui.add(iterations.setup("iterations", 2, 1, 8));
    gui.add(polyN.setup("polyN", 7, 5, 10));
    gui.add(polySigma.setup("polySigma", 1.5, 1.1, 2));
    gui.add(OPTFLOW_FARNEBACK_GAUSSIAN.setup("OPTFLOW_FARNEBACK_GAUSSIAN", false));
    gui.add(showFlow.setup("Show OpticalFlow",true));
    gui.add(alertLevel.setup("alert Level", 3.0, 0, 20));
    selectSaveDirctory();
    saveImageCount = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    theta.update();
//    if(resetBackButton){
//        backImg = theta.frameCpture();
//        bgSub.setBackground(backImg);
//    } else
    if(resetDirctory){
        selectSaveDirctory();
    }
    
//    if(isbackImg == false){
//        getBackground_first();
//        cout << "isbacImg" <<endl;
//    } else {
        if(isFirstImg == false){
            getFirstImg();
            //cout <<"-----First-------" << endl;
        } else {
            if(isSecondImg == false){
                if(isReCap){
                    isFirstImg = false;
                    isReCap = false;
                }
                getSecondImg();
                //cout <<"-----Second-------" << endl;
            } else {
                if(isReCap){
                    isSecondImg = false;
                    isReCap = false;
                }
                //updateContours();
                opf.updateFarneback(pyrScale,levels,winsize,iterations,polyN,polySigma, OPTFLOW_FARNEBACK_GAUSSIAN);
                getNewImg();
                //cout <<"-----Third-------" << endl;
            }
        }
    //}
    cout << " opfAverage = " << opf.getAverage() << endl;
}
//--------------------------------------------------------------
void ofApp::draw(){
    theta.draw();
    //backImg.draw(ofGetWidth()-theta.w/3, 0, theta.w/3, theta.h/3);
    int w = (firstImg.getWidth()*ofGetHeight()/2-100)/firstImg.getHeight();
    if(isFirstImg == true && isSecondImg == false){
        firstImg.draw(ofGetWidth()/2-w/2, ofGetHeight()/2, (firstImg.getWidth()*ofGetHeight()/2-100)/firstImg.getHeight(), ofGetHeight()/2-100);
    } else if (isFirstImg == true && isSecondImg == true){
        drawToImage();
        //bgSub.drawDiffImg(0, ofGetHeight()/2);
        //bgSub.drawDiffCenter(0, ofGetHeight()/2);
        if(showFlow){
            opf.drawOpticalFlow(ofGetWidth()/2-w/2, ofGetHeight()/2, (firstImg.getWidth()*ofGetHeight()/2-100)/firstImg.getHeight(), ofGetHeight()/2-100);
        }
    }
    
    drawBottomTab();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::getBackground_first(){
    if(pushSpace){
        backImg = theta.frameCpture();
        bgSub.setBackground(backImg);
        isbackImg = true;
        pushSpace = false;
    }
}

//--------------------------------------------------------------
void ofApp::getFirstImg(){
    if(pushSpace){
        firstImg.setFromPixels(theta.frameCpture().getPixels());
        //firstImg = theta.frameCpture();
    
        //bgSub.setFirstFrame(firstImg);
        //bgSub.getFirstContours(firstImg, thresholdValue, kSize);
        opf.setFirstImage(firstImg);
        isFirstImg = true;
        pushSpace = false;
    }
}

//--------------------------------------------------------------
void ofApp::getSecondImg(){
    if(pushSpace){
        //secondImg = theta.frameCpture();
        secondImg.setFromPixels(theta.frameCpture().getPixels());
        
        //bgSub.setSecondFrame(secondImg);
        //bgSub.getFirstContours(secondImg, thresholdValue, kSize);
        opf.setSecondImage(secondImg);
        isSecondImg = true;
        pushSpace = false;
    }
    
}

//--------------------------------------------------------------
void ofApp::getNewImg(){
    reCapFlag = false;
     if(pushSpace){
         isAlert();
         //firstImgを保存
         saveImage(firstImg);
         oldImg = firstImg;
         firstImg = secondImg;
         secondImg = theta.frameCpture();
//         bgSub.getFirstContours(firstImg, thresholdValue, kSize);
//         bgSub.getSecondContours(secondImg, thresholdValue, kSize);
         opf.setFirstImage(firstImg);
         opf.setSecondImage(secondImg);
         pushSpace = false;
     } else if(isReNewCap){
         secondImg = firstImg;
         firstImg = oldImg;
         opf.setFirstImage(firstImg);
         opf.setSecondImage(secondImg);
         if(saveImageCount > 0){
             
             string str = result.getPath()+"/stm360_"+ ofToString(saveImageCount) +".jpg";
             //ofFile remove(str);
             file.removeFile(str);
             saveImageCount--;
         }
         isReNewCap = false;
     }
}

//--------------------------------------------------------------
void ofApp::updateContours(){
    if(isDragge){
        bgSub.getContours(thresholdValue, kSize);
    }
}

//--------------------------------------------------------------
void ofApp::saveImage(ofImage img){
    if(canSave){
        saveImageCount++;
        string str = result.getPath()+"/stm360_"+ ofToString(saveImageCount) +".jpg";
        img.save(str);
    }
}

//--------------------------------------------------------------
void ofApp::selectSaveDirctory(){
    result = ofSystemLoadDialog("Save Dirctory", true);
}

//--------------------------------------------------------------
void ofApp::drawBottomTab(){
    ofPushStyle();
    ofSetColor(0);
    ofDrawRectangle(0, ofGetHeight()-40, ofGetWidth(), 40);
    ofSetColor(255);
    ofDrawBitmapString("Save Dirctory : "+result.getPath(), 50, ofGetHeight()-25);
    ofDrawBitmapString("Save Image : "+ofToString(saveImageCount), 50, ofGetHeight()-10);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawToImage(){
    ofPushStyle();
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, 255);
    int w =(firstImg.getWidth()*ofGetHeight()/2-100)/firstImg.getHeight();
    secondImg.draw(ofGetWidth()/2-w/2, ofGetHeight()/2, (firstImg.getWidth()*ofGetHeight()/2-100)/firstImg.getHeight(), ofGetHeight()/2-100);
    ofPushStyle();
    ofSetColor(255, 255, 255, 100);
    firstImg.draw(ofGetWidth()/2-w/2, ofGetHeight()/2, (firstImg.getWidth()*ofGetHeight()/2-100)/firstImg.getHeight(), ofGetHeight()/2-100);
    ofPopStyle();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        pushSpace = true;
        shutterSound.play();
    }
    
    if(key == 'r'){
        if(reCapFlag){
            isReCap = true;
        }
        isReNewCap = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    isDragge = true;
}

void ofApp::mouseReleased(int x, int y, int button){
    isDragge = false;
}

void ofApp::isAlert(){
    if(opf.getAverage() > alertLevel){
        ofSystemAlertDialog("Too Much Movement !!!");
    }
}




