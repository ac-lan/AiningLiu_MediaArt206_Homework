#include "world.h"
ofxAssimpModelLoader World::Hogwarts;
ofxAssimpModelLoader World::DeathEater;
ofxAssimpModelLoader World::Dementor;
World::World() {};

void World::loadModel() {
	Hogwarts.loadModel("meshes/Hogwarts/Hogwarts1.obj");
	Hogwarts.setRotation(0, 180, 1, 0, 0);
	Hogwarts.setScale(0.45, 0.5, 0.15);
	DeathEater.loadModel("meshes/deathEater/1.obj");
	DeathEater.setRotation(90, 180, 1, 0, 0);
	DeathEater.setScale(0.05, 0.04, 0.05);
	Dementor.loadModel("meshes/Dementor/Dementor.obj");
	Dementor.setRotation(90, 180, 1, 0, 0);
	Dementor.setScale(0.05, 0.06, 0.06);
};


void World::update() {

};


void World::draw() {

	ofPushMatrix();
	ofTranslate(0, -GROUND_HEIGHT, 0);
	ofPushMatrix();
	drawBox(ofPoint(WORLD_DIMENSIONS.x, GROUND_HEIGHT, GROUND_DEPTH), GRASS_COLOR);
	ofPopMatrix();

	ofPushMatrix();
	ofTranslate(0, 0, WORLD_DIMENSIONS.z - GROUND_DEPTH);
	drawBox(ofPoint(WORLD_DIMENSIONS.x, GROUND_HEIGHT, GROUND_DEPTH), GRASS_COLOR);
	ofPopMatrix();

	ofPushMatrix();
	ofTranslate(0, -3, WORLD_DIMENSIONS.z - 2 * GROUND_DEPTH);
	drawBox(ofPoint(WORLD_DIMENSIONS.x, GROUND_HEIGHT, GROUND_DEPTH), SAND_COLOR);
	ofPopMatrix();

	ofPushMatrix();
	ofTranslate(0, -3, GROUND_DEPTH + 0.1);

	ofPoint dimensions = ofPoint(WORLD_DIMENSIONS.x, GROUND_HEIGHT, WORLD_DIMENSIONS.z - 3 * GROUND_DEPTH - 0.2);
	ofPoint resolution = ofPoint(10, 1, 10);

	ofPushMatrix();
	ofTranslate(dimensions.x / 2, dimensions.y / 2, dimensions.z / 2);

	ofPlanePrimitive plane;
	plane.set(WORLD_DIMENSIONS.x, WORLD_DIMENSIONS.z - 3 * GROUND_DEPTH - 0.2);
	plane.setResolution(40, 40);
	plane.rotateDeg(90, 1, 0, 0);
	plane.setPosition(0, dimensions.y / 2, 0);

	vector<glm::vec3>& verts = plane.getMesh().getVertices();
	for (unsigned int i = 0; i < verts.size(); i++) {
		verts[i].x += ofSignedNoise(verts[i].x / 5, verts[i].y / 5, verts[i].z / 5, ofGetElapsedTimef() / 5)*3;
		verts[i].y += ofSignedNoise(verts[i].z / 5, verts[i].x / 5, verts[i].y / 5, ofGetElapsedTimef() / 5)*3;
		verts[i].z += ofSignedNoise(verts[i].y / 5, verts[i].z / 5, verts[i].x / 5, ofGetElapsedTimef() / 5)*3;
	}

	ofSetColor(WATER_COLOR);
	plane.draw();

	ofBoxPrimitive box = ofBoxPrimitive(dimensions.x, dimensions.y, dimensions.z, resolution.x, resolution.y, resolution.z);
	box.setPosition(0, -1, 0);
	ofSetColor(WATER_COLOR2);
	box.draw();

	ofPopMatrix();

	ofPopMatrix();
	ofPopMatrix();

	ofPushMatrix();
	ofTranslate(100, -10, 20);
	ofRotateDeg(180, 0, 1, 0);
	Hogwarts.drawFaces();
	ofPopMatrix();

	ofPushMatrix();
	ofTranslate(0, 0, 240);
	for (size_t i = 0; i < 40; i++)
	{
		ofPushMatrix();
		ofTranslate(ofRandom(10, 190), 0, ofRandom(10, 30));
		//ofRotateDeg(ofRandom(0, 360), 0, 1, 0);
		if (ofRandom(1)<0.45) {
			DeathEater.drawFaces();
		}
		else {
			Dementor.drawFaces();
		}
		ofPopMatrix();
	}
	ofPopMatrix();
};

bool World::isPointInsideWorld(ofPoint point) {

	ofPoint world_min = ofPoint(0, 0, 0);
	ofPoint world_max = ofPoint(200, 100, 280);

	return point.x >= world_min.x &&
		point.x <= world_max.x &&
		point.y >= world_min.y &&
		point.y <= world_max.y &&
		point.z >= world_min.z &&
		point.z <= world_max.z;
};



