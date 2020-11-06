#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetCircleResolution(50);
	ofEnableAntiAliasing();
	smile.curveTo(345, 284);
	smile.curveTo(385, 422);
	smile.curveTo(510, 490);
	smile.curveTo(629, 422);
	smile.curveTo(667, 296);

	smile1.curveTo(230, 226);
	smile1.curveTo(385, 422);
	smile1.curveTo(510, 550);
	smile1.curveTo(629, 422);
	smile1.curveTo(854, 226);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	int red = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 255);
	int blue = ofMap(ofGetMouseX(), 0, ofGetWidth(), 100, 200);
	ofBackgroundGradient(ofColor(red, 80,blue), ofColor(10, 10, 10));
	
	ofSetColor(0);
	ofDrawEllipse(512, 725, 650, 1200);
	ofSetColor(212, 192, 125);
	ofDrawEllipse(512, 384, 350, 400); // Centered at (400 100), 80 wide x 100 high
//cout << ofGetMouseX() << " " << ofGetMouseY() << endl;
	ofSetColor(57, blue, red);
	ofSetLineWidth(4.0);

	ofPoint point2(420, 300);
	eyes1.arc(point2, 85, 85, 0, 180);
	eyes1.draw();

	ofPoint point1(600, 300);
	eyes2.arc(point1, 85, 85, 0, 180);
	eyes2.draw();

	ofSetColor(255);
	ofDrawTriangle(500, 425, 510, 400, 520, 425);

	
	smile.draw();
	smile1.draw();

	ofSetColor(0);
	ofDrawEllipse(412, 345, 60, 65);
	ofDrawEllipse(600, 345, 60, 65);
	ofSetColor(255);
	ofDrawCircle(393, 328, 6);
	ofDrawCircle(415, 357, 9);
	ofDrawCircle(421, 334, 6);
	ofDrawCircle(588, 331, 6);
	ofDrawCircle(597, 361, 9);
	ofDrawCircle(609, 340, 6);

	ofSetColor(blue, 130, red);
	ofDrawTriangle(482, 602, 507, 585, 532, 602);

	ofDrawRectangle(482, 602, 50, 300);
	ofDrawTriangle(412, 802, 482, 602, 482, 802);
	ofDrawTriangle(532, 802, 532, 602, 602, 802);

	ofSetColor(230);
	ofDrawBitmapString("move mouse to change color tone", 10, 20);
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
