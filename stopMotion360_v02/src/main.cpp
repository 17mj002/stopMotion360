#include "ofMain.h"
#include "ofApp.h"
//リコーTHETAを使って360度写真を撮影する．撮影画像を背景差分を求め，物体を検出し，その物体の移動量を計算する．

//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
