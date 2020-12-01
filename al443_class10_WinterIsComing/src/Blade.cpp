#include "Blade.h"


void Blade::generate() {


	points.clear();

	//Loop through and create a point at given interval
	for (int i = yStart; i < yEnd; i += gapLength) {
		points.push_back(ofVec2f(xVal, i));
	}

	//Cap the vector at the end.
	points.push_back(ofVec2f(xVal, yEnd));



	// Modify points to create snowflake blades
	for (int i = 1; i < points.size() - 1; i++) {

		//Decide whether to start the blade
		if (!bladeStarted) {
			bladeStarted = rand() % 2;
		}

		if (bladeStarted) {
			points.at(i).x = xVal - 20;
			bladeStarted = !bladeStarted;
		}
	}

}

void Blade::draw() {
	ofBackground(57, 104, 189);

	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);


	ofPushMatrix();
	drawOneBlade();
	ofPopMatrix();

	ofPushMatrix();
	ofRotateZ(-45);
	drawOneBlade();
	ofPopMatrix();

	ofPushMatrix();
	ofRotateZ(45);
	drawOneBlade();
	ofPopMatrix();

	ofPushMatrix();
	ofRotateZ(-90);
	drawOneBlade();
	ofPopMatrix();

	ofPushMatrix();
	ofRotateZ(90);
	drawOneBlade();
	ofPopMatrix();

	ofPushMatrix();
	ofRotateZ(-135);
	drawOneBlade();
	ofPopMatrix();

	ofPushMatrix();
	ofRotateZ(135);
	drawOneBlade();
	ofPopMatrix();

	ofPushMatrix();
	ofRotateZ(180);
	drawOneBlade();
	ofPopMatrix();


	ofPopMatrix();






}

void Blade::drawOneBlade() {



	//Draw out points and lines
	ofVec2f lastPoint;
	for (int i = 0; i < points.size(); i++) {
		ofVec2f tempPoint = points.at(i);
		if (i == 0) {
			ofLine(tempPoint.x, tempPoint.y, xVal + bladeWidth + (xVal - tempPoint.x), tempPoint.y);
		}


		//ofCircle(tempPoint.x, tempPoint.y, 10);

		if (i > 0) {
			ofLine(lastPoint.x, lastPoint.y, tempPoint.x, tempPoint.y);
			ofLine(xVal + bladeWidth + (xVal - lastPoint.x), lastPoint.y, xVal + bladeWidth + (xVal - tempPoint.x), tempPoint.y);
		}

		if (i == points.size() - 1) {
			ofLine(tempPoint.x, tempPoint.y, xVal + bladeWidth + (xVal - tempPoint.x), tempPoint.y);
		}

		lastPoint = tempPoint;
	}

}