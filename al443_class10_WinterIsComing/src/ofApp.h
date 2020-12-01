#pragma once

#include "ofMain.h"
#include "Blade.h"
#include "ofxBox2d.h"
class Orniment : public ofxBox2dCircle {
public:
	Orniment() {
		scale = 1.0;
		step = 0.01;
	}

	float scale;
	float step;
	ofColor color;
	void update() {
		if (scale >= 1 || scale <= 0) {
			step *= -1;
		}

		scale += step;
	}
	void draw() {
		float radius = getRadius();

		glPushMatrix();
		glTranslatef(getPosition().x, getPosition().y, 0);

		ofSetColor(color.r*scale, color.g*scale, color.b*scale);
		ofFill();
		ofCircle(0, 0, radius);

		glPopMatrix();

	}
};


class Snowflake : public ofxBox2dCircle {
public:
	Snowflake() {
		scale = 1.0;
		step = 0.230;
		color = 0xffffff;
	}

	float scale;
	float step;
	ofColor color;
	static ofImage* img;

	void update() {
		if (scale >= 1 || scale <= 0.8) {
			step *= -1;
		}

		scale += step;

		if (!isSleeping()) {

			if (!(rand() % 2)) {
				int dx = 1;
				if (rand() % 2) {
					dx *= -1;
				}

				int dy = 1;
				if (rand() % 2) {
					dy *= -1;
				}

				ofVec2f vec(ofRandom(.001)*dx, ofRandom(.001)*dy);
				addForce(vec, .003);
			}
		}

	}

	void draw() {
		float radius = getRadius();

		glPushMatrix();
		glTranslatef(getPosition().x, getPosition().y, 0);
		//		img->draw(getPosition().x, getPosition().y);

		ofSetColor(color.r*scale, color.g*scale, color.b*scale);
		ofFill();
		ofCircle(0, 0, getRadius());

		glPopMatrix();

	}
};

struct Particle
{
	ofVec3f pos;
	float rad = 3;
	ofVec3f color{ ofRandom(0,200), 0, ofRandom(0,200) };
	Particle() = default;
	Particle(ofVec3f _pos)
	{
		this->pos = _pos;
	}
	void update()
	{
		this->pos.x -= 3;
		this->pos.y += ofRandom(-3.f, 3.f);
	}
	void draw()
	{
		ofSetColor(color.x, color.y, color.z);
		ofDrawCircle(this->pos, rad);
	}
	bool finished()
	{
		return this->pos.x < 0.f;
	}
	bool intersects(std::vector<Particle>& others)
	{
		for (auto & p : others)
		{
			auto d = ofDist(p.pos.x, p.pos.y, this->pos.x, this->pos.y);
			if (d < this->rad * 2)
			{
				return true;
			}
		}
		return false;
	}
};
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
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void addEdge(ofPolyline* drawing);

	void createSnowflake();
	void createOrniment();
	ofxBox2dCircle cursor;


	float                                   px, py;
	bool                                    bDrawLines;
	bool                                    bMouseForce;
	ofxBox2d                                box2d;			
	ofPolyline                              drawing;		 
	ofxBox2dEdge                            edgeLine;		  
	vector		<ofPtr<ofxBox2dEdge> >		edges;		  
	vector		<ofPtr<Snowflake> >	snowflakes;	

	Blade blade;
	Particle cur;
	std::vector<Particle> particles;
	float rcnt = 0.f;

	ofConePrimitive volcano,mouth,hand;
	ofPlanePrimitive ground;

	ofLight firelight;	
	ofLight sunlight;	

	ofEasyCam cam;

	glm::vec3 gravity;
};
