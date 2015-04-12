#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxAssimpModelLoader.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
	ofVideoGrabber cam;
	ofxCv::ObjectFinder finder;
    ofxCv::ObjectFinder handFinder;
	ofImage ironMan;
    ofImage ironManHand;
   };
