#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void applyForce(ofVec2f force);
	float k;
	float restLength;

	ofVec2f acc, vel;
	ofVec2f an, ball;
	bool dragging;

	ofxBox2d                                    box2d;			 
	ofxBox2dCircle                              anchor;			  
	vector		<shared_ptr<ofxBox2dCircle>>	circles;		  
	vector		<shared_ptr<ofxBox2dJoint>>	    joints;

	ofImage bg;
};

