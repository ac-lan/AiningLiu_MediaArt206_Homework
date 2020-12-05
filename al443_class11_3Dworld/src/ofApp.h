#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

	ofCamera camera;

	ofLight pointLight1;
	ofLight pointLight2;


	ofImage space;

	int drawingMode;

public:
	void setup();
	void update();
	void draw();

	void drawSpaceInvader();
	void drawCylinder();
	void drawTail();

	void keyReleased(int key);

};