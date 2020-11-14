#include "Planet.h"

void Planet::setup(float s, float x, float y, string im) {
	planetGroup.add(rotateSpeed.set("speed", s, 0.0, 9.0));
	planetGroup.add(posX.set("X", x, 0, 600));
	planetGroup.add(posY.set("Y", y, 0, 600));

/*	planetGroup.add(red.set("red", 255, 0, 255));
	planetGroup.add(green.set("green", 255, 0, 255));
	planetGroup.add(blue.set("blue", 255, 0, 255));*/

	image.load(im);
}

void Planet::update() {
	rotation++;
}

void Planet::draw(float w, float h) {
//	ofSetColor(red, green, blue);
	ofRotate(rotation*rotateSpeed);
	//ofCircle(posX, posY, 30);
	image.draw(posX, posY, w, h);
}