#pragma once 
#include "ofMain.h"
#include "Particle.h"

class Spring {

public:

	Spring();
	void set(Particle * _A, Particle * _B);
	void update();
	void draw();

	float k;
	float restDist;


	Particle * A;
	Particle * B;



};