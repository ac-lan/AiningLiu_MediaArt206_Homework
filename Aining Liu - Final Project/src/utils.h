#pragma once

#include "ofMain.h"


void drawBox(ofPoint position, ofPoint dimensions, ofColor color);
void drawBox(ofPoint dimensions, ofColor color);


struct BoundingBox {
	ofPoint min;
	ofPoint max;
	ofPoint size;
};

BoundingBox getMeshBoundingBox(ofMesh mesh);
