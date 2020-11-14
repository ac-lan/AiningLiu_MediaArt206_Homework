#pragma once

#include "ofMain.h"
#include "particle.h"

class firework {
public:
	void init(float a,float b);
	void explode();
	void drawExplode();
	bool updateExplode();

	bool exploding;
	int num;
	float vel;
	vector <particle> particles;
	vector < vector < ofPoint > > path;
	float xline, yline; //linePos, lineVel, 
	float dur, start; //lasting time, start time
	ofColor color;
	
};


