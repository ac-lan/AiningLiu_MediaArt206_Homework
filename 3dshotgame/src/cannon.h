#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

#include "bullet.h"


class Cannon {

private:
		
	float CANNON_VELOCITY = 40;
	float ROTATION_VELOCITY = 20;
	ofPoint SHOOT_POSITION = ofPoint(5.1, 6.5, -13.5);
	
	static ofxAssimpModelLoader cannonShooterModel;
	static ofxAssimpModelLoader cannonBaseModel;
	
	int shots;
	int total_shots;
	float shot_animation_opacity = 0;
	
	ofPoint position;
	float angle;

	void setup(int n_shots);
	
public:
	
	float ANGLE_MIN = 0;
	float ANGLE_MAX = 60;

	vector<Bullet> bullets;

	static void loadModel();


	Cannon(int n_shots);
	Cannon();
	

	void setPosition(ofPoint point);
	ofPoint getPosition();
	void setAngle(float angle);
	float getAngle();
	void setShots(int shots);
	int getShots();
	void setTotalShots(int shots);
	int getTotalShots();
	

	void moveLeft();
	void moveRight();
	void rotateUp();
	void rotateDown();
	void shoot(float velocity);


	void update();
	void draw();

};