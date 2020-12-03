#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

	int num = 1500;
	for (int i = 0; i < num; i++) {
		Particle now = Particle();
		p.push_back(now);
	}
	wind = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < p.size(); i++) {
		p[i].update(wind);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor(51, 153, 255), ofColor(10, 10, 10));

	for (int i = 0; i < p.size(); i++) {
		p[i].draw();
	}

	ofSetColor(230);
	ofDrawBitmapString("\n\nSpacebar to reset. \nKeys 1-4 to change wind direction and speed.", 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == '1')  wind = 0.25;
	if (key == '2') wind = 0.55;
	if (key == '3') wind = -0.25;
	if (key == '4') wind = -0.55;
	if (key == ' ') wind=0;
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
