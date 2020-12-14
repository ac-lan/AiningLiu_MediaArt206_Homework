#pragma once

#include "ofMain.h"


class ExplosionAnimation {

public:

	float radius = 3;
	float MAX_RADIUS = 15;
	float ANIMATION_SPEED = 12;

	ofPoint position;
	bool running = true;

	ExplosionAnimation() {};
	ExplosionAnimation(ofPoint p) { position = p; };
	

	void update()  {

		if (radius >= MAX_RADIUS)
		{
			running = false;
		}
		if (running == true)
		{
			float dt = ofGetLastFrameTime();
			radius += ANIMATION_SPEED * dt;
		}

	}

	void draw() {

		if (running == false)
		{
			return;
		}
		
		ofSpherePrimitive sphere;

		ofPushMatrix();

			ofTranslate(position);

			ofSetColor(ofColor(255, 255, 10, 100));
			sphere.setRadius(radius / 3);
			sphere.draw();

			ofSetColor(ofColor(255, 140, 0, 100));
			sphere.setRadius(radius / 2);
			sphere.draw();

			ofSetColor(ofColor(255, 10, 10, 100));
			sphere.setRadius(radius);
			sphere.draw();

		ofPopMatrix();

	}

};


class WaterHoleAnimation {

public:

	float radius = 3;
	float MAX_RADIUS = 8;
	float ANIMATION_SPEED = 8;

	ofPoint position;
	bool running = true;

	WaterHoleAnimation() {};
	WaterHoleAnimation(ofPoint p) { position = p; };


	void update() {

		if (radius >= MAX_RADIUS)
		{
			running = false;
		}
		if (running == true)
		{
			float dt = ofGetLastFrameTime();
			radius += ANIMATION_SPEED * dt;
		}

	}

	void draw() {

		if (running == false)
		{
			return;
		}
		
		ofSpherePrimitive sphere;

		ofPushMatrix();
			
			ofTranslate(position);

			ofSetColor(ofColor(30, 144, 255, 100));
			sphere.setRadius(radius / 3);
			sphere.draw();

			ofSetColor(ofColor(0, 191, 255, 100));
			sphere.setRadius(radius / 1.6);
			sphere.draw();

			ofSetColor(ofColor(173, 216, 230, 100));
			sphere.setRadius(radius);
			sphere.draw();

		ofPopMatrix();

	}

};


class AnimationEmitter {

public:

	vector<ExplosionAnimation> explosion_animations;
	vector<WaterHoleAnimation> waterhole_animations;

	AnimationEmitter() {};


	void addExplosionAnimation(ExplosionAnimation a) {
		explosion_animations.push_back(a);
	}

	void addWaterHoleAnimation(WaterHoleAnimation a) {
		waterhole_animations.push_back(a);
	}

	
	void update() {
		
		for (size_t i = 0; i < explosion_animations.size(); i++)
		{
			explosion_animations[i].update();
			if (explosion_animations[i].running == false)
			{
				explosion_animations.erase(explosion_animations.begin() + i);
			}
		}
		for (size_t i = 0; i < waterhole_animations.size(); i++)
		{
			waterhole_animations[i].update();
			if (waterhole_animations[i].running == false)
			{
				waterhole_animations.erase(waterhole_animations.begin() + i);
			}
		}
		
	}

	void draw() {
		
		for (size_t i = 0; i < explosion_animations.size(); i++)
		{
			explosion_animations[i].draw();
		}
		for (size_t i = 0; i < waterhole_animations.size(); i++)
		{
			waterhole_animations[i].draw();
		}
		
	}

};
