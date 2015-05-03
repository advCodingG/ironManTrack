#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {

    //set this true if you want to synchronized vertically, false if you want to draw as fast as possible
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
    
    //frontal face tracking setup
	finder.setup("haarcascade_frontalface_alt2.xml");
	finder.setPreset(ObjectFinder::Fast);
	finder.getTracker().setSmoothingRate(0.3);
    
    //hand tracking setup
    handFinder.setup("haarcascade_hand.xml");
    handFinder.setPreset(ObjectFinder::Fast);
    handFinder.getTracker().setSmoothingRate(0.3);
    
    //initialize the webcam image
	cam.initGrabber(640, 480);
	ironMan.loadImage("ironman.png");
    
    ironManHand.loadImage("ironmanHand.png");
	ofEnableAlphaBlending();
}

void ofApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		finder.update(cam);
        handFinder.update(cam);
	}
}

void ofApp::draw() {
	cam.draw(0, 0);
	
    //face tracking
	for(int i = 0; i < finder.size(); i++) {
        //create a rectangle based on the finder object
		ofRectangle object = finder.getObjectSmoothed(i);
        
        //scale the ironman image to match the face that's being tracked
		float scaleAmount = object.width / (ironMan.getWidth()*.55);
        ofPushMatrix();
        //draw the ironman image based on the location of the face object
        ofTranslate(object.getTopLeft() - 80);
		ofScale(scaleAmount, scaleAmount);
        ironMan.draw(0, 0);
		ofPopMatrix();
        
        //draw the labels
		ofPushMatrix();
		ofTranslate(object.getPosition());
		ofDrawBitmapStringHighlight(ofToString(finder.getLabel(i)), 0, 0);
		ofLine(ofVec2f(), toOf(finder.getVelocity(i)) * 10);
		ofPopMatrix();
        
	}
    
    //hand tracking
    //inaccurate and unstable
    for(int j = 0; j < handFinder.size(); j++) {
        ofRectangle hand = handFinder.getObjectSmoothed(j);
        
        float handScaleAmount = hand.width / (ironManHand.getWidth()/2);
        
        ofPushMatrix();
        ofTranslate(hand.getTopLeft()-100);
        ofScale(handScaleAmount, handScaleAmount);
        ironManHand.draw(0, 0);
        ofPopMatrix();

        ofPushMatrix();
        ofTranslate(hand.getPosition());
        ofDrawBitmapStringHighlight(ofToString(handFinder.getLabel(j)), 0, 0);
        ofLine(ofVec2f(), toOf(handFinder.getVelocity(j)) * 20);
        ofPopMatrix();
        
    }
}
