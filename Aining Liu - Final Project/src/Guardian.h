#pragma once

#include "ofMain.h";
#include "ofxAssimpModelLoader.h"
#include "utils.h"
class Guardian{
private:
	static ofxAssimpModelLoader stone;
	static ofxAssimpModelLoader ship;
	static ofxAssimpModelLoader dragon;
	static ofPoint sea_min;
	static ofPoint sea_max;
	ofPoint position; 
	ofPoint velocity;
	int type;
	void setup(ofPoint position, ofPoint velocity);

public:
	static void loadModel();
	static void setSeaLimits(ofPoint min, ofPoint max);
	Guardian(ofPoint position, ofPoint velocity);
	Guardian(ofPoint position);
	Guardian();
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


