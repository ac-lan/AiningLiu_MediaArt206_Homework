#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "utils.h"


class World {
	
private:

	static ofxAssimpModelLoader Hogwarts;
	static ofxAssimpModelLoader DeathEater;
	static ofxAssimpModelLoader Dementor;
	
	ofColor WATER_COLOR = ofColor(0, 0, 255, 170);
	ofColor WATER_COLOR2 = ofColor(0, 0, 255, 50);
	ofColor GRASS_COLOR = ofColor(25, 66, 48);
	ofColor SAND_COLOR = ofColor(59, 102, 66);

	ofPoint WORLD_DIMENSIONS = ofPoint(200, 100, 280);
	float GROUND_DEPTH = 40;
	float	GROUND_HEIGHT = 20;

	ofPoint WORLD_MIN = ofPoint(0, 0, 0);
	ofPoint WORLD_MAX = ofPoint(200, 100, 280);

public:
			
	World();

	static void loadModel();

	void update();
	
	void draw();

	bool isPointInsideWorld(ofPoint point);

};


