#pragma once
#include "ofMain.h"
class Planet
{
public:
	void setup(string im);
	void update();
	void draw();

	ofParameterGroup planetGroup;
	ofParameter<float> rotateSpeed;
	ofParameter<float> posX, posY;
	ofParameter<int> red, green, blue;
	ofImage image;

	float rotation = 0.0;
};

