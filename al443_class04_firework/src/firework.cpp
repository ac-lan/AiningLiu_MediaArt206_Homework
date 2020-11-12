#include "firework.h"

void firework::init() {
	len = 20;
	exploding = 0;
	xline = ofRandom(200, ofGetWidth() - 200); yline =ofGetHeight();
	vxline = ofRandom(-1, 1); vyline = ofRandom(5,8);
	h = ofRandom(0.15, 0.45)*ofGetHeight();
	dur = ofRandom(2.0, 4.0);
	color = ofColor(ofRandom(100,225), ofRandom(100, 225), ofRandom(100, 225));
	num = ofRandom(25, 50);
	vel = num / 6.0;

}
void firework::drawLine() {
	if (line.size() > 3) {
		ofFill();
		ofSetColor(255, 255, 255, 255);
		ofCircle(xline, yline, 1 + (abs(sin(ofGetElapsedTimef() * 5))*4.0));
		int maxx = min(20, (int)line.size());
		for (int i = 0; i < maxx; i++) {
			ofSetColor(color.r - 30, color.g - 30, color.b - 30, 150 * (1.0 - (i / (float)maxx)));
			ofCircle(line[line.size() - i - 1].x, line[line.size() - i - 1].y, 1 + (abs(sin(ofGetElapsedTimef() * 5))*3.0*(1.0 - (i / (float)maxx))));
			
		}
	}
}

void firework::updateLine() {
	xline += vxline;
	yline -= vyline;
	ofPoint pt;
	pt.set(xline, yline);
	line.push_back(pt);
}

void firework::explode() {
	start = ofGetElapsedTimef();
	for (int i = 0; i < num; i++) {
		particle myParticle;
		float angle = ofRandom(0, 2.0*PI);
		float velX = cos(angle)*vel;
		float velY = sin(angle)*vel;
		myParticle.setInitialCondition(xline, yline, velX, velY);
		particles.push_back(myParticle);

		path.push_back(vector<ofPoint>());
		ofPoint st;
		st.set(xline, yline);
		path[i].push_back(st);
	}
}
void firework::drawExplode() {
	if (ofGetElapsedTimef() - start < dur) {
		ofSetColor(color.r*ofRandom(0.5, 1.5), color.g*ofRandom(0.5, 1.5), color.b*ofRandom(0.5, 1.5), 
			255 * (1.0 - (ofGetElapsedTimef() - start) / dur));
		for (int i = 0; i < particles.size(); i++) {
			particles[i].draw();
		}
		for (int i = 0; i < path.size(); i++) {
			if (path[i].size() <= 5) continue;
			int maxx=min(30,(int)path[i].size());
			//cout << path.size()<<endl;
			for (int j = 0; j < maxx - 1; j++) {
				//cout << j << endl;
				ofSetColor(color.r*ofRandom(0.5, 1.5), color.g*ofRandom(0.5, 1.5), color.b*ofRandom(0.5, 1.5), 
					255 * (1.0 - (j / (float)maxx))*((1.0 - (ofGetElapsedTimef() - start) / dur)));
				ofSetLineWidth(3.0*((1.0 - (ofGetElapsedTimef() - start) / dur)));
				//cout << ppath[i].size() - j - 1<<" "<< path[i].size() - j - 2;
				ofLine(path[i][path[i].size() - j - 1].x, path[i][path[i].size() - j - 1].y, path[i][path[i].size() - j - 2].x, path[i][path[i].size() - j - 2].y);
				//cout << "!!!!";
			}
		}
	}
}
bool firework::updateExplode() {
	if (ofGetElapsedTimef() - start < dur) {
		for (int i = 0; i < particles.size(); i++) {
			particles[i].resetForce();
			particles[i].addForce(0, 0.08); //gravity
			particles[i].addDampingForce();
			particles[i].update();
			ofPoint st;
			st.set(particles[i].pos.x, particles[i].pos.y);
			path[i].push_back(st);
			
		}
		return 1;
	}
	else  return 0;
}