#include "ofApp.h"
#define SNOW_COLOR 0xffffff
#define BACKGROUND_COLOR 0x0d80a6
#define DEBUG_COLOR 0xff0000

ofImage* Snowflake::img = NULL;
//--------------------------------------------------------------
void ofApp::setup()
{
	//ofBackground(70, 20, 20);

	ofSetSmoothLighting(true);
	ofSetFrameRate(60);
	volcano.set(250, 400, 80, 70);
	volcano.rotateDeg(180, glm::vec3(1, 0, 0));

	mouth.set(50, 300);
	mouth.setPosition(140, 20, -220);
	mouth.rotateDeg(70,glm::vec3(1,0,0));
	mouth.rotateDeg(-30, glm::vec3(0, 1, 0));
	mouth.rotateDeg(70, glm::vec3(0, 0, 1));
	auto& coneVerts = volcano.getMesh().getVertices();
	for (int i = 0; i < coneVerts.size(); i++)
	{
		if (coneVerts[i].y <= -50) {
			coneVerts[i].y = 40;
		}
		glm::vec3 nPos = coneVerts[i] * 0.01;
		coneVerts[i].x += ofSignedNoise(nPos.x) * 30.;
		coneVerts[i].y += ofSignedNoise(nPos.y) * 30.;
		coneVerts[i].z += ofSignedNoise(nPos.z) * 30.;
	}
	ground.set(10000, 10000, 1000, 1000);       
	ground.rotateDeg(-90, glm::vec3(1, 0, 0));    
	ground.move(0, -200, 0);                

	gravity = ofVec3f(0, -.003, 0);

	firelight.setPointLight();   
	firelight.setPosition(0, 200, 0);
	firelight.setDiffuseColor(ofColor::white);

	sunlight.setDirectional();    
	sunlight.setPosition(100, 100, -400);   
	sunlight.lookAt(glm::vec3(0));      
	sunlight.setDiffuseColor(ofColor::white);

	bMouseForce = false;

	box2d.init();
	box2d.setGravity(0, .5);
	box2d.setFPS(30.0);
	box2d.registerGrabbing();

	cursor.setup(box2d.getWorld(), mouseX, mouseY, 20);
	cursor.fixture.filter.maskBits = 0x0000;
	ofSetFrameRate(60);
	cur = Particle({ ofGetWidth() / 2.f, 0.f,1 });
}

void ofApp::addEdge(ofPolyline* drawing) {
	ofxBox2dEdge* e = new ofxBox2dEdge;
	e->addVertexes(*drawing);
	e->setPhysics(0.0, 0.01, 1.0);
	e->create(box2d.getWorld());
	edges.push_back(ofPtr<ofxBox2dEdge>(e));
}
//--------------------------------------------------------------
void ofApp::update()
{

	// animate sun rotation
	sunlight.rotateDeg(.2, 0, 1, 0);

	createSnowflake();
	createSnowflake();

	cursor.setPosition(mouseX, mouseY);

	for (int i = 0; i < snowflakes.size(); ++i)
	{
		Snowflake* flake = snowflakes[i].get();
		flake->update();
	}


	while (snowflakes.size() > 1500) {
		Snowflake* c = snowflakes[snowflakes.size() - 1].get();
		c->destroy();
		snowflakes.erase(snowflakes.begin());
	}
	box2d.update();

	ofRemove(snowflakes, ofxBox2dBaseShape::shouldRemoveOffScreen);

	while (!cur.finished() and !cur.intersects(particles))
	{
		cur.update();
	}
	particles.push_back(cur);
	cur = Particle({ ofGetWidth() / 2.f, ofRandom(-10.f,10.f),1 });
	rcnt += 0.1f;
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackgroundGradient(ofColor(13, 128, 166), ofColor(30., 10., 0));

	for (int i = 0; i < snowflakes.size(); i++) {
		snowflakes[i].get()->draw();
	}

	ofNoFill();
	ofSetHexColor(BACKGROUND_COLOR);

	for (int i = 0; i < edges.size(); ++i) {
		edges[i].get()->updateShape();
		edges[i].get()->draw();
	}

	if (drawing.size() == 0) {
		edgeLine.updateShape();
		edgeLine.draw();
	}
	else {
		drawing.draw();
	}

	//blade.draw();
	ofTranslate(ofGetWidth() / 2.f, ofGetHeight() / 2.f);
	ofRotateDeg(rcnt);
	ofRotateDeg(30.f);
	for (auto i = 0ul; i < 6ul; ++i)
	{
		ofRotate(60.f);
		cur.draw();
		for (auto &p : particles)
		{
			p.draw();
		}

		ofPushMatrix();
		ofScale(1, -1);
		cur.draw();
		for (auto &p : particles)
		{
			p.draw();
		}
		ofPopMatrix();
	}

	
	ofEnableLighting();

	cam.begin();
	ofEnableDepthTest();

	firelight.enable();


	sunlight.enable();

	ofSetColor(255);
	volcano.draw();
	ofFill();
	ofDrawIcoSphere(20, 150,7, 150);
	ofSetColor(10);
	ofDrawIcoSphere(50, 150, 140,21);
	ofDrawIcoSphere(130, 150, 90, 20);
	mouth.draw();
	volcano.drawAxes(100);

	ofSetColor(255);
	ground.draw();
	ofSetColor(255);

	firelight.disable();
	sunlight.disable();
	ofDisableLighting();

	ofDisableDepthTest();

	// you can draw the lights on top of your scene
	firelight.draw();
	sunlight.draw();


	cam.end();
}

void ofApp::createSnowflake() {
	float r = ofRandom(2, 4);		
	Snowflake* flake = new Snowflake;
	snowflakes.push_back(ofPtr<Snowflake>(flake));
	flake->setPhysics(0.0001, 0.03, 1.0);
	float x = ofRandom(ofGetWindowWidth());

	if (!(rand() % 2)) {
		flake->fixture.filter.maskBits = 0x0000;
	}
	else {
		flake->fixture.filter.maskBits = 0xffff;
	}

	flake->setup(box2d.getWorld(), x, 0.0f, r);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	//blade.generate();

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}