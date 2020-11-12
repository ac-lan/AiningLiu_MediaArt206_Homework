#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//ofBackground(120);
	background.load("images/starfield.jpg");
	p1.setup("images/sun.gif");
	p2.setup("images/earth.gif");
	p3.setup("images/jupiter.gif");
	p4.setup("images/venus.gif");
	planetGroups.add(p1.planetGroup);
	planetGroups.add(p2.planetGroup);
	planetGroups.add(p3.planetGroup);
	planetGroups.add(p4.planetGroup);

	gui.setup(planetGroups);
}

//--------------------------------------------------------------
void ofApp::update(){
	p1.update();
	p2.update();
	p3.update();
	p4.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	background.draw(0,0,ofGetWidth(),ofGetHeight());
	gui.draw();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	p1.draw();

	ofTranslate(p1.posX, p1.posY);
	p2.draw();
//	p3.draw();
	ofTranslate(p2.posX, p2.posY);
	p4.draw();

	

	
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
