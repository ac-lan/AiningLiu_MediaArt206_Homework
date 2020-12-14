#include "ship.h"


ofxAssimpModelLoader Ship::shipModel1;
ofxAssimpModelLoader Ship::shipModel2;
ofxAssimpModelLoader Ship::shipModel3;

ofPoint Ship::sea_min = ofPoint(0, 0, 20);
ofPoint Ship::sea_max = ofPoint(200, 0, 180);

void Ship::loadModel() {

	Ship::shipModel1.loadModel("meshes/Stone/Stone.obj");
	Ship::shipModel1.setRotation(0, 180, 1, 0, 0);
	Ship::shipModel1.setScale(0.05, 0.05, 0.05);

	shipModel2.loadModel("meshes/galleon/galleon.obj");
	Ship::shipModel2.setRotation(0, -180, 1, 0, 0);
	Ship::shipModel2.setScale(0.05, 0.05, 0.05);
	
	Ship::shipModel3.loadModel("meshes/Dragon/1.obj");
	Ship::shipModel3.setRotation(0, 180, -1, 0, 0);
	Ship::shipModel3.setScale(0.1, 0.1, 0.1);

}

void Ship::setSeaLimits(ofPoint min, ofPoint max)
{
	Ship::sea_min = min;
	Ship::sea_max = max;
}



void Ship::setup(ofPoint p, ofPoint v)
{
	position = p;
	velocity = v;
	type = 0;
}


Ship::Ship(ofPoint position, ofPoint velocity)
{
	setup(position, velocity);
}
Ship::Ship(ofPoint position)
{
	ofPoint velocity = ofPoint(ofRandom(0.1f, 0.3f), 0, 0);
	setup(position, velocity);
}
Ship::Ship()
{
	ofPoint velocity = ofPoint(ofRandom(0.1f, 0.3f), 0, 0);
	ofPoint position = ofPoint(0, -5, ofRandom(40, 200));
	setup(position, velocity);
}


void Ship::setPosition(ofPoint p) {
	position = p;
};
ofPoint Ship::getPosition() {
	return position;
};

void Ship::setVelocity(ofPoint v) {
	velocity = v;
};
ofPoint Ship::getVelocity() {
	return velocity;
};

void Ship::setModelType(int t) {
	type = t;
};
int Ship::getModelType() {
	return type;
};


void Ship::update()
{	

	float dt = ofGetLastFrameTime();
	
	position += velocity * dt;
		
	if (position.x > Ship::sea_max.x)
	{
		position.x = Ship::sea_min.x;
	}
	if (position.x < Ship::sea_min.x)
	{
		position.x = Ship::sea_max.x;
	}
	if (position.z > Ship::sea_max.z)
	{
		position.z = Ship::sea_min.z;
	}
	if (position.z < Ship::sea_min.z)
	{
		position.z = Ship::sea_max.z;
	}

}


void Ship::draw()
{
	
	ofPushMatrix();
		ofTranslate(position);
		

		if (type == 1) {
			ofRotateDeg(180, 0, 1, 0);
			Ship::shipModel1.drawFaces();
		} 
		else if(type == 2){
			Ship::shipModel2.drawFaces();
		} 
		else if (type == 3) {
			ofRotateDeg(-90, 0, 1, 0);
			Ship::shipModel3.drawFaces();
		}
				
		// ##DEBUG bounding box visible
		//ofPoint box_offset = ofPoint(-20, 0, -13);
		//ofPoint box_dimensions = ofPoint(40, 20, 10);
		//drawBox(box_offset, box_dimensions, ofColor(100, 100, 100, 100));
	

	ofPopMatrix();
	
}



bool Ship::isPointInShip(ofPoint point)
{
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
	//if (type == 3)
	//{
	//	box_offset = ofPoint(0, 0, -10);
	//	box_dimensions = ofPoint(21, 20, 10);
	//}

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

