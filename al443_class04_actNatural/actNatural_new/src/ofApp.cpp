#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);
	ofBackground(0);
	ofSetLogLevel(OF_LOG_NOTICE);
	ofDisableAntiAliasing();


	box2d.init();
	box2d.setGravity(10, 0);
	box2d.setFPS(60.0);
	box2d.registerGrabbing();

	anchor.setup(box2d.getWorld(), 2*ofGetWidth() / 3, ofGetHeight() / 2, 4);

	for (int i = 0; i < 3; i++) {
		auto circle = make_shared<ofxBox2dCircle>();
		circle->setPhysics(3.0, 0.53, 0.1);
		circle->setup(box2d.getWorld(), ofGetWidth() / 2, 100 + (i * 20), 8);
		circles.push_back(circle);
	}

	for (int i = 0; i < circles.size(); i++) {

		auto joint = make_shared<ofxBox2dJoint>(box2d.getWorld(), i == 0 ? anchor.body : circles[i - 1]->body, circles[i]->body);

		joint->setLength(25);
		joints.push_back(joint);
	}

	k = 0.05;
	restLength = 200;

	an = ofVec2f(ofGetWidth() / 3, ofGetHeight()/3);
	ball = ofVec2f(ofGetWidth() / 3, restLength + 100);

	dragging = false;

	bg.load("bg.jpg");
}


void ofApp::applyForce(ofVec2f force) {

	acc.x += force.x;
	acc.y += force.y;
}

//--------------------------------------------------------------
void ofApp::update() {
	box2d.update();
	if (dragging == true)  return;

	ofVec2f force = ball - an;
	float currentLength = force.length();
	float x = currentLength - restLength;
	force.normalize();
	force *= -1 * k * x; 
	applyForce(force);
	applyForce(ofVec2f(0, 1.0));
	vel += acc;
	vel *= 0.98; 
	ball += vel;
	acc *= 0; 
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(255);
	bg.draw(0, 0, ofGetWidth(), ofGetHeight());
	ofSetHexColor(0x6da68b);
	ofDrawLine(an, ball);
	ofDrawCircle(an, 10);
	ofDrawCircle(ball, 20);


	ofSetHexColor(0x3b5247);
	anchor.draw();

	for (auto &circle : circles) {
		ofFill();
		ofSetHexColor(0x6da68b);
		circle->draw();
	}

	for (auto &joint : joints) {
		ofSetHexColor(0x444342);
		joint->draw();
	}
	string info = "";
	info += "Press [n] to add a new joint\n";
	info += "click and pull the chain around\n";
	info += "FPS: " + ofToString(ofGetFrameRate(), 1) + "\n";
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'n') {
		auto circle = make_shared<ofxBox2dCircle>();
		circle->setPhysics(3.0, 0.53, 0.1);
		circle->setup(box2d.getWorld(), circles.back()->getPosition().x + ofRandom(-30, 30), circles.back()->getPosition().y - 30, 8);
		circles.push_back(circle);

		int a = (int)circles.size() - 2;
		int b = (int)circles.size() - 1;

		auto joint = make_shared<ofxBox2dJoint>(box2d.getWorld(), circles[a]->body, circles[b]->body);
		joint.get()->setLength(25);
		joints.push_back(joint);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

	if (dragging == true) {
		ball.set(x, y);
	}

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

	if (ofVec2f(x, y).distance(ball) < 20) {
		ball.set(x, y);
		dragging = true;
		vel *= 0;

	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

	dragging = false;
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