#include "Guardian.h"

ofxAssimpModelLoader Guardian::stone;
ofxAssimpModelLoader Guardian::ship;
ofxAssimpModelLoader Guardian::dragon;

ofPoint Guardian::sea_min = ofPoint(0, 0, 20);
ofPoint Guardian::sea_max = ofPoint(200, 0, 180);

void Guardian::loadModel() {

	Guardian::stone.loadModel("meshes/Stone/Stone.obj");
	Guardian::stone.setRotation(0, 180, 1, 0, 0);
	Guardian::stone.setScale(0.05, 0.05, 0.05);

	ship.loadModel("meshes/galleon/galleon.obj");
	Guardian::ship.setRotation(0, -180, 1, 0, 0);
	Guardian::ship.setScale(0.05, 0.05, 0.05);
	
	Guardian::dragon.loadModel("meshes/Dragon/1.obj");
	Guardian::dragon.setRotation(0, 180, -1, 0, 0);
	Guardian::dragon.setScale(0.1, 0.1, 0.1);

}

void Guardian::setSeaLimits(ofPoint min, ofPoint max)
{
	Guardian::sea_min = min;
	Guardian::sea_max = max;
}



void Guardian::setup(ofPoint p, ofPoint v)
{
	position = p;
	velocity = v;
	type = 0;
}


Guardian::Guardian(ofPoint position, ofPoint velocity){
	setup(position, velocity);
}
Guardian::Guardian(ofPoint position){
	ofPoint velocity = ofPoint(ofRandom(0.1f, 0.3f), 0, 0);
	setup(position, velocity);
}
Guardian::Guardian(){
	ofPoint velocity = ofPoint(ofRandom(0.1f, 0.3f), 0, 0);
	ofPoint position = ofPoint(0, -5, ofRandom(40, 200));
	setup(position, velocity);
}

void Guardian::setPosition(ofPoint p) {
	position = p;
};
ofPoint Guardian::getPosition() {
	return position;
};

void Guardian::setVelocity(ofPoint v) {
	velocity = v;
};
ofPoint Guardian::getVelocity() {
	return velocity;
};

void Guardian::setModelType(int t) {
	type = t;
};
int Guardian::getModelType() {
	return type;
};


void Guardian::update(){	
	float dt = ofGetLastFrameTime();
	position += velocity * dt;
	if (position.x > Guardian::sea_max.x) position.x = Guardian::sea_min.x;
	if (position.x < Guardian::sea_min.x) position.x = Guardian::sea_max.x;
	if (position.z > Guardian::sea_max.z) position.z = Guardian::sea_min.z;
	if (position.z < Guardian::sea_min.z) position.z = Guardian::sea_max.z;
}


void Guardian::draw(){
	ofPushMatrix();
		ofTranslate(position);
		if (type == 1) {
			ofRotateDeg(180, 0, 1, 0);
			Guardian::stone.drawFaces();
		} 
		else if(type == 2){
			Guardian::ship.drawFaces();
		} 
		else if (type == 3) {
			ofRotateDeg(-90, 0, 1, 0);
			Guardian::dragon.drawFaces();
		}
				
		//ofPoint box_offset = ofPoint(-10, 0, -5);
		//ofPoint box_dimensions = ofPoint(20, 20, 10);
		//drawBox(box_offset, box_dimensions, ofColor(100, 100, 100, 100));

	ofPopMatrix();
}


bool Guardian::isPointInShip(ofPoint point){
	ofPoint box_offset, box_dimensions;
	if (type == 1) {
		box_offset = ofPoint(-10, 0, -5);
		box_dimensions = ofPoint(21, 20, 10);
	}
	else if (type == 2) {
		box_offset = ofPoint(0, 0, -10);
		box_dimensions = ofPoint(21, 20, 10);
	}
	else {
		box_offset = ofPoint(-20, 0, -13);
		box_dimensions = ofPoint(40, 20, 10);
	}
	ofPoint min = position + box_offset;
	ofPoint max = min + box_dimensions;

	bool result = point.x > min.x &&
		point.x < max.x &&
		point.y > min.y &&
		point.y < max.y &&
		point.z > min.z &&
		point.z < max.z;
	return result;
}

