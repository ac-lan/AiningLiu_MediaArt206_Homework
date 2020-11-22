#include "ofMain.h"
#include "ofxBox2d.h"

#define N_SOUNDS 5

class Data {
public:
	ofColor color;
	string  name;
	int		id;

	int	 soundID;
	bool bHit;
};

class CustomParticle : public ofxBox2dCircle {
public:
	ofColor color;

	CustomParticle(b2World * world, float x, float y,int radius, int color,int sb);

	void draw();
	void update();
};