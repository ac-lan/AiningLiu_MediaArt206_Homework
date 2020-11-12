#pragma once

#include "ofMain.h"
#include "particle.h"

class firework {
public:
	void init();
	void drawLine();
	void updateLine();
	void explode();
	void drawExplode();
	bool updateExplode();

	bool exploding;
	int num;
	float vel;
	vector <particle> particles;
	vector <ofPoint> line;
	vector < vector < ofPoint > > path;
	float xline, yline, vxline,vyline; //linePos, lineVel, 
	int len, h;
	float dur, start; //length, height, lasting time, start time
	ofColor color;
	
};


