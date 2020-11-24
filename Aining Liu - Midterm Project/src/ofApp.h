#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "CustomParticle.h"

enum Scenes {
	scene1, scene2, scene3
};
// -------------------------------------------------
class ofApp : public ofBaseApp {

public:

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void resized(int w, int h);
	void contactStart(ofxBox2dContactArgs &e);
	void contactEnd(ofxBox2dContactArgs &e);

	ofSoundPlayer  sound[N_SOUNDS];

	Scenes sc = scene1;

	ofxBox2d                                box2d;          
	ofPolyline                              drawing;         
	ofxBox2dEdge                            edgeLine;        
	vector    <shared_ptr<CustomParticle> > circles;       
	vector    <shared_ptr<CustomParticle> > customParticles; 
	vector    <shared_ptr<CustomParticle> > hidro;

	ofxBox2dRect rect1,rect2,rect3,rect4;

	bool breakupIntoTriangles;
	bool bFill;
	bool down;
	ofPolyline                            shape;
	vector <shared_ptr<ofxBox2dPolygon>>  polyShapes;
	ofImage plant,bg1,bg2,bg3;
	bool first=true;

	int goal;
};
