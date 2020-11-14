#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofEnableAlphaBlending();
	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < fireworks.size(); i++) {
		if (fireworks[i].exploding) {
			//cout << "*****";
			bool alive = fireworks[i].updateExplode();
			//cout << "!!!!";
			if (!alive) {
				//cout << "*****";
				fireworks.erase(fireworks.begin() + i, fireworks.begin() + i + 1);
				//cout << "!!!!";
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(230);
	ofDrawBitmapString("left click mouse to generate firework!", 10, 20);
	for (int i = 0; i < fireworks.size(); i++) {
		if (fireworks[i].exploding) {
			//cout << "*****";
			fireworks[i].drawExplode();
			//cout << "!!!!";
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	firework aFirework;
	aFirework.init(x,y);
	aFirework.explode();
	fireworks.push_back(aFirework);
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
