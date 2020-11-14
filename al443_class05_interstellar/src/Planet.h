#pragma once
#include "ofMain.h"
class Planet
{
public:
	void setup(float s, float x, float y, string im);
	void update();
	void draw(float w, float h);

	ofParameterGroup planetGroup;
	ofParameter<float> rotateSpeed;
	ofParameter<float> posX, posY;
//	ofParameter<int> red, green, blue;
	ofImage image;

	float rotation = 0.0;
};

