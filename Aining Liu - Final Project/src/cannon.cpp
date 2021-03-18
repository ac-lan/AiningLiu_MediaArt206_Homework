#include "cannon.h"

ofxAssimpModelLoader Cannon::cannonShooterModel;
ofxAssimpModelLoader Cannon::cannonBaseModel;

void Cannon::loadModel(){
	Cannon::cannonShooterModel.loadModel("meshes/cannon/cannon_shooter.obj");
	Cannon::cannonShooterModel.setRotation(0, 180, 1, 0, 0);
	Cannon::cannonShooterModel.setScale(0.02, 0.02, 0.02);
	Cannon::cannonBaseModel.loadModel("meshes/cannon/cannon_base.obj");
	Cannon::cannonBaseModel.setRotation(0, 180, 1, 0, 0);
	Cannon::cannonBaseModel.setScale(0.02, 0.02, 0.02);
}

void Cannon::setup(int n_shots){
	shots = n_shots;
	total_shots = n_shots;
	angle = 0;
	position = ofPoint(0,0,0);
}

Cannon::Cannon(int n_shots) {
	setup(n_shots);
}
Cannon::Cannon() {
	setup(10);
}

void Cannon::setPosition(ofPoint p) {
	position = p;
}
ofPoint Cannon::getPosition() {
	return position;
};

void Cannon::setAngle(float a){
	angle = a;
}
float Cannon::getAngle() {
	return angle;
};

void Cannon::setShots(int s) {
	shots = s;
}
int Cannon::getShots(){
	return shots;
}
void Cannon::setTotalShots(int s) {
	total_shots = s;
}
int Cannon::getTotalShots(){
	return total_shots;
}


void Cannon::moveLeft(){
	if (position.x > 0){
		float dt = ofGetLastFrameTime();
		position.x -= CANNON_VELOCITY * dt;
	}
}
void Cannon::moveRight()
{
	if (position.x < 200){
		float dt = ofGetLastFrameTime();
		position.x += CANNON_VELOCITY * dt;
	}
}
void Cannon::rotateUp(){
	if (angle < ANGLE_MAX){
		float dt = ofGetLastFrameTime();
		angle += ROTATION_VELOCITY * dt;
	}
}
void Cannon::rotateDown(){
	if (angle > ANGLE_MIN){
		float dt = ofGetLastFrameTime();
		angle -= ROTATION_VELOCITY * dt;
	}
}

void Cannon::shoot(float v){
	shot_animation_opacity = 150;
	Bullet bullet = Bullet();
	bullet.setPosition(position + SHOOT_POSITION);
	bullet.setVelocity(ofPoint(0, v * sin(angle * (PI / 180)), - v * cos(angle * (PI / 180)) ));
	bullets.push_back(bullet);
	shots--;
}

void Cannon::update(){
	if (shot_animation_opacity <= 20) shot_animation_opacity = 0;
	if (shot_animation_opacity > 0){
		float dt = ofGetLastFrameTime();
		shot_animation_opacity -= 80 * dt;
	}
}

void Cannon::draw(){
	for (size_t i = 0; i < bullets.size(); i++){
		bullets[i].draw();
	}

	ofPushMatrix();
		ofTranslate(position);
		Cannon::cannonBaseModel.drawFaces();
		ofPushMatrix();
			ofTranslate(5, 5.5, -7.5);
			ofRotate(angle, 1, 0, 0);
			ofTranslate(-5, -5.5, 7.5);
			Cannon::cannonShooterModel.drawFaces();
			if (shot_animation_opacity != 0)
			{
				ofSetColor(ofColor(100, 100, 100, shot_animation_opacity));
				ofIcoSpherePrimitive sphere;
				sphere.setResolution(1);

				ofPushMatrix();

				ofTranslate(SHOOT_POSITION);
				sphere.setRadius(3);
				sphere.draw();

				ofPushMatrix();
				ofTranslate(0, 0, -3);
				sphere.setRadius(2);
				sphere.draw();
				ofPopMatrix();

				ofPushMatrix();
				ofTranslate(0, 0, -5);
				sphere.setRadius(1);
				sphere.draw();
				ofPopMatrix();

				ofPopMatrix();
			}
		ofPopMatrix();
	ofPopMatrix();
}
