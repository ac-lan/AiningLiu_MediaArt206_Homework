#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	camera.setFov(100);

	camera.setPosition(ofVec3f(60, 60, 60));
	camera.lookAt(ofVec3f(0, 0, 0));

	pointLight1.setPosition(0, 82, 100);
	pointLight1.setDiffuseColor(ofColor(255, 250, 154));

	pointLight2.setPosition(0, 82, -100);
	pointLight2.setDiffuseColor(ofColor(255, 130, 5));


	ofEnableDepthTest();
	space.load("space.jpg");



	drawingMode = 0;
}

//--------------------------------------------------------------
void ofApp::update() {


	float distance = sin(ofGetElapsedTimef() * 0.4) * 100;


	float radius = 120 + (sin(ofGetElapsedTimef() * 0.3) * 100);
	float height = 30 + (sin(ofGetElapsedTimef() * 0.6) * 60);

	ofVec3f newCamera = ofVec3f(cos(ofGetElapsedTimef()) * radius, height, sin(ofGetElapsedTimef()) * radius);

	camera.setPosition(newCamera);
	camera.lookAt(ofVec3f(0, 0, 0));


}

//--------------------------------------------------------------
void ofApp::draw() {

	camera.begin();


	ofDrawAxis(100); 

	ofEnableLighting();
	pointLight1.enable();
	pointLight2.enable();



	if (drawingMode == 0) {
		drawSpaceInvader();
	}
	else if (drawingMode == 1) {
		drawTail();
	}
	else if (drawingMode == 2) {
		drawCylinder();
	}



	pointLight1.draw();
	pointLight2.draw();

	camera.end();

	ofDrawBitmapString("press space to switch drawing ", 10, 20);


}



void ofApp::drawSpaceInvader() {

	ofPushMatrix();

	ofTranslate(-space.getWidth() * 0.5, space.getHeight() * 0.5, 0);

	int gridSize = 15;
	for (int x = 0; x < space.getWidth(); x += gridSize) {
		for (int y = 0; y < space.getHeight(); y += gridSize) {

			if (space.getColor(x, y).getBrightness() > 240) {
				ofDrawBox(ofVec3f(x, -y, 0), 12);
			}
		}
	}

	ofPopMatrix();


}


void ofApp::drawCylinder() {

	for (float angle = 0; angle < 360; ++angle) {


		float radius = 50 + (angle * 0.1) + sin(ofGetElapsedTimef() * 0.4) * 24;
		ofVec3f position(sin(angle) * radius, -100 + angle, cos(angle) * radius);


		ofPushMatrix();

		ofTranslate(position);
		ofRotate(angle, 0, 1, 0);
		ofDrawBox(ofVec3f(0, 0, 0), fabs(sin(angle)) * 8);


		ofPopMatrix();


	}
}


void ofApp::drawTail() {
	ofPushMatrix();

	for (int i = 0; i < 40; ++i) {
		ofTranslate(i * 0.2, 0, 0);
		ofRotate(ofGetElapsedTimef() * 20, 1, 1, 1);
		ofScale(1.1, 1.1, 1.1);
		ofDrawBox(ofVec3f(0, 0, 0), 4);
	}

	ofPopMatrix();
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (key == 'f') {
		ofToggleFullscreen();
	}
	else if (key == ' ') {
		drawingMode++;
		drawingMode %= 3;
	}

}