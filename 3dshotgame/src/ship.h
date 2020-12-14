#pragma once

#include "ofMain.h";
#include "ofxAssimpModelLoader.h"

#include "utils.h"


class Ship
{

private:
	
	static ofxAssimpModelLoader shipModel1;
	static ofxAssimpModelLoader shipModel2;
	static ofxAssimpModelLoader shipModel3;

	static ofPoint sea_min;
	static ofPoint sea_max;
	
	ofPoint position; 
	ofPoint velocity;
	int type;

	void setup(ofPoint position, ofPoint velocity);

public:
	
	static void loadModel();
	static void setSeaLimits(ofPoint min, ofPoint max);
	
	
	Ship(ofPoint position, ofPoint velocity);
	Ship(ofPoint position);
	Ship();

	
	ofPoint getPosition();
	void setPosition(ofPoint position);

	ofPoint getVelocity();
	void setVelocity(ofPoint velocity);

	int getModelType();
	void setModelType(int type);


	void update();
	void draw();
	

	bool isPointInShip(ofPoint point);
};


