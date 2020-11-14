#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//ofBackground(120);
	background.load("images/starfield.jpg");
	p1.setup(0,0,0, "images/sun.gif");
	p2.setup(0.13, 42.8, 45.9, "images/mercury.gif");
	p3.setup(0.22,70.4,67.34,"images/venus.gif");
	p4.setup(0.229,94.89,91.83,"images/earth.gif");
	p5.setup(0.091, 119.3,122.449,"images/mars.gif");
	p6.setup(0.199,156.122,156.122,"images/jupiter.gif");
	p7.setup(0.1036,186.735,189.796,"images/saturn.gif");
	p8.setup(0.0877,217.34,220.408,"images/uranus.gif");
	p9.setup(0.024,244.898,247.959,"images/neptune.gif");
	planetGroups.add(p1.planetGroup);
	planetGroups.add(p2.planetGroup);
	planetGroups.add(p3.planetGroup);
	planetGroups.add(p4.planetGroup);
	planetGroups.add(p5.planetGroup);
	planetGroups.add(p6.planetGroup);
	planetGroups.add(p7.planetGroup);
	planetGroups.add(p8.planetGroup);
	planetGroups.add(p9.planetGroup);
	gui.setup(planetGroups);
}

//--------------------------------------------------------------
void ofApp::update(){
	p1.update();
	p2.update();
	p3.update();
	p4.update();
	p5.update();
	p6.update();
	p7.update();
	p8.update();
	p9.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	background.draw(0,0,ofGetWidth(),ofGetHeight());
	gui.draw();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	p1.draw(50,50);

	ofTranslate(p1.posX, p1.posY);
	p2.draw(25,25);
	p3.draw(25,25);
	p4.draw(25, 25);
	p5.draw(25, 25);
	p6.draw(25, 25);
	p7.draw(25, 25);
	p8.draw(25, 25);
	p9.draw(25, 25);
//	p3.draw();

	

	
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
