#pragma once
#include "ofMain.h"

class particle
{
public:
	ofVec2f pos,vel,frc;

	particle();

	void resetForce();
	void addForce(float x, float y);
	void addDampingForce();
	void setInitialCondition(float px, float py, float vx, float vy);
	void update();
	void draw();

	float damping;

};