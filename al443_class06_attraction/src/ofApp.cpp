#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofBackground(0);
	left = right = 0;
	background.load("images/bg.jpg");
	boy.load("images/boyy.jpg");
	girl.load("images/girll.jpg");
	score = 0;
}

//--------------------------------------------------------------
void ofApp::update() {
	if (frame > (1 << 27)) frame = 0;
	frame++;
	if (frame % 40 == 1) {
		float posY = ofRandom(250, 500);
		//ofMap(y, 0, 9, 0, ofGetHeight());
		float posX = -5;
		//ofMap(x, 0, 9, 0, ofGetWidth());
		float vx = ofRandom(0, 8);
		float vy = ofRandom(-5, 5);
		Mover mover(glm::vec2(posX, posY), glm::vec2(vx, vy));
		movers.push_back(mover);
	}
	glm::vec2 mousePos = glm::vec2(ofGetMouseX(), ofGetMouseY());

	for (int i = 0; i < movers.size(); i++) {

		glm::vec2 diff = mousePos - movers[i].pos;

		float distance = glm::length(diff);


		if (left && distance != 0 && distance < 100) {
			// calc repulsion

			glm::vec2 norm = diff / distance;
			movers[i].applyForce(-norm);
		}
		if (right && distance != 0 && distance < 200) {
			// calc attraction

			glm::vec2 norm = diff / distance;
			movers[i].applyForce(norm*5);
		}

		movers[i].update();
		if (movers[i].pos.x >= ofGetWidth()-5) {
			score++;
			movers.erase(movers.begin() + i, movers.begin() + i + 1);
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw() {
	background.draw(0, 0, ofGetWidth(), ofGetHeight());
	//ofSetColor(0);
	ofDrawBitmapString("Score: " + ofToString(score), 10, 20);
	boy.draw(0, 250, 150, 250);
	girl.draw(ofGetWidth() - 150, 250, 150, 250);
	for (int i = 0; i < movers.size(); i++)
	{
		movers[i].draw();
		//ofDrawBitmapStringHighlight(ofToString(movers[i].elasticForce, 2), movers[i].pos);
	}

	ofNoFill();
	ofDrawCircle(mouseX, mouseY, 100);
	ofDrawCircle(mouseX, mouseY, 200);
	ofFill();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (button == 0) left = 1;
	if (button == 2) right = 1;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	if (button == 0) left = 0;
	if (button == 2) right = 0;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}