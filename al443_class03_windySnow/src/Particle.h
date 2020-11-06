/*
modeled on the particle example given in OpenFrameworks

*/
#pragma once
#include "ofMain.h"
class Particle{
public:
	Particle();

	//void setAttractPoints(vector<ofVec2f> * attract);

	void reset();
	void update(double num);
	void draw();

	ofVec2f pos, vel, frc;

	float drag,val,scale;

	//vector <ofVec2f> * attractPoints;
};

