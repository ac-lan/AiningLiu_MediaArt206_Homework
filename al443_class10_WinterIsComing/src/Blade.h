#ifndef __snowflake__Blade__
#define __snowflake__Blade__

#include <iostream>
#include "ofMain.h"


class Blade {


public:

	void generate();
	void draw();
	void drawOneBlade();


	vector<ofVec2f> points;
	int bladeWidth = 10;
	float xVal = -bladeWidth / 2;
	float yStart = 0;
	float yEnd = 350;

	int gapLength = 20;

	bool bladeStarted = false;


};





#endif /* defined(__snowflake__Blade__) */
