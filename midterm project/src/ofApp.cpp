#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup() {
	if (first && sc == scene1) {
		ofSetVerticalSync(true);
		//ofBackgroundHex(0xfdefc2);
		ofSetLogLevel(OF_LOG_NOTICE);
		ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL);

		box2d.init();
		box2d.setGravity(0, 10);
		box2d.createGround();
		box2d.setFPS(60.0);
		box2d.enableEvents();

		ofAddListener(box2d.contactStartEvents, this, &ofApp::contactStart);
		ofAddListener(box2d.contactEndEvents, this, &ofApp::contactEnd);

		for (int i = 0; i < N_SOUNDS; i++) {
			sound[i].load("sfx/" + ofToString(i) + ".mp3");
			sound[i].setMultiPlay(true);
			sound[i].setLoop(false);
		}
		first = false;
	
	}
	breakupIntoTriangles = false;
	bFill = false;
	down = true;

	goal = 0;

	if (rect1.body != NULL) box2d.world->DestroyBody(rect1.body);
	if (rect2.body != NULL) box2d.world->DestroyBody(rect2.body);
	if (rect3.body != NULL) box2d.world->DestroyBody(rect3.body);
	if (rect4.body != NULL) box2d.world->DestroyBody(rect4.body);

	rect1.setPhysics(0, 0, 0);
	rect2.setPhysics(0, 0, 0);
	rect3.setPhysics(0, 0, 0);
	rect4.setPhysics(0, 0, 0);

	shape.clear();
	polyShapes.clear();
	circles.clear();
	hidro.clear();
	customParticles.clear();
	drawing.clear();
	edgeLine.clear();

	if (sc == scene1) {
		bg1.load("images/bg11.jpg");

		rect1.setup(box2d.getWorld(), ofGetWidth() / 3 - 10, 4 * ofGetHeight() / 5, ofGetWidth() / 18, ofGetHeight() / 2);
		rect2.setup(box2d.getWorld(), ofGetWidth() / 3 - 10, ofGetHeight() / 5, ofGetWidth() / 18, ofGetHeight() / 2);
		rect3.setup(box2d.getWorld(), 2 * ofGetWidth() / 3 - 10, 4 * ofGetHeight() / 5, ofGetWidth() / 18, ofGetHeight() / 2);
		rect4.setup(box2d.getWorld(), 2 * ofGetWidth() / 3 - 10, ofGetHeight() / 5, ofGetWidth() / 18, ofGetHeight() / 2);

		for (int i = 0; i < 30; i++) {
			auto particle = std::make_shared<CustomParticle>(box2d.getWorld(), ofRandom(ofGetWidth() / 3, 2 * ofGetWidth() / 3 - 10),
				ofRandom(0, ofGetHeight()), ofRandom(20, 30), 0xe6b03c, 0);
			customParticles.push_back(particle);
		}
	}
	
	if (sc == scene2) {
		rect1.setup(box2d.getWorld(), 0, 6 * ofGetHeight() / 8, 4*ofGetWidth() / 5-100, 3*ofGetHeight() / 5);
		rect2.setup(box2d.getWorld(), 2.5*ofGetWidth() / 5-100, 8*ofGetHeight() / 9, 2*ofGetWidth() / 7, 2*ofGetHeight() / 5);
		rect3.setup(box2d.getWorld(), 8 * ofGetWidth() / 9 , 7 * ofGetHeight() / 8-50, 3*ofGetWidth() / 5, 2.5*ofGetHeight() / 5);
		rect4.setup(box2d.getWorld(), 8.9 * ofGetWidth() / 9, 2*ofGetHeight() / 5, ofGetWidth() / 18, ofGetHeight() / 2);
		for (int i = 0; i < 30; i++) {
			auto particle = std::make_shared<CustomParticle>(box2d.getWorld(), 5 * ofGetWidth() / 6 + ofRandom(-100, 100), 3 * ofGetHeight() / 8,
				ofRandom(20, 30), 0xc24517, 1);
			particle->setPhysics(0, 0, 0);
			particle->setVelocity(0, 0);
			customParticles.push_back(particle);
		}
		bg2.load("images/bg2.jpg");
		plant.load("images/plant.png");
	}

	if (sc == scene3) {
		bg3.load("images/bg3.jpg");
		rect1.setup(box2d.getWorld(), 0, 7 * ofGetHeight() / 8+100, 4 * ofGetWidth() / 5 - 100, 4 * ofGetHeight() / 5);
		rect2.setup(box2d.getWorld(), 8 * ofGetWidth() / 9, 7 * ofGetHeight() / 8+100 , 3 * ofGetWidth() / 5, 4*ofGetHeight() / 5);
		rect3.setup(box2d.getWorld(), 3 * ofGetWidth() / 5,  4*ofGetHeight() / 5-50 , ofGetWidth() / 23, 4.5*ofGetHeight() / 5);
		rect4.setup(box2d.getWorld(), 8.9 * ofGetWidth() / 9, 2 * ofGetHeight() / 5, ofGetWidth() / 18, ofGetHeight() / 2);
		for (int i = 0; i < 30; i++) {
			auto particle = std::make_shared<CustomParticle>(box2d.getWorld(), 5 * ofGetWidth() / 6 + ofRandom(-100, 100), 3 * ofGetHeight() / 8,
				ofRandom(20, 30), 0x8442f5, 4);
			particle->setPhysics(0, 0, 0);
			particle->setVelocity(0, 0);
			customParticles.push_back(particle);
		}
	}
}

void ofApp::contactStart(ofxBox2dContactArgs &e) {
	if (sc == scene1) {
		if (e.a != NULL && e.b != NULL) {
			Data *now1 = (Data*)e.b->GetBody()->GetUserData();
			Data *now2 = (Data*)e.a->GetBody()->GetUserData();
			if ((now1 != NULL && now2 != NULL) && (((now1->name == "org" || now1->name == "H2") && now2->name == "N2")
				|| (now1->name == "N2" && (now2->name == "org" || now2->name == "H2")))) {
				now1->color.setHex(0xc24517);
				now1->name = "NH3";
				now2->color.setHex(0xc24517);
				now2->name = "NH3";
				now1->bHit = true;
				sound[now1->soundID].play();
				now2->bHit = true;
				sound[now2->soundID].play();
			}
		}
	}
	else if (sc == scene2) {
		if (e.a != NULL && e.b != NULL) {
			Data *now1 = (Data*)e.b->GetBody()->GetUserData();
			Data *now2 = (Data*)e.a->GetBody()->GetUserData();
			if ((now1 != NULL && now2 != NULL) && ((now1->name == "NH3" && now2->name == "O2")
				|| (now2->name == "NH3" && now1->name == "O2"))) {
				now1->color.setHex(0x8442f5);
				now1->name = "NO3-";
				now2->color.setHex(0x8442f5);
				now2->name = "NO3-";
				now1->bHit = true;
				sound[now1->soundID].play();
				now2->bHit = true;
				sound[now2->soundID].play();
			}
		}
	}
	else if (sc == scene3) {
		if (e.a != NULL && e.b != NULL) {
			Data *now1 = (Data*)e.b->GetBody()->GetUserData();
			Data *now2 = (Data*)e.a->GetBody()->GetUserData();
			if ((now1 != NULL && now2 != NULL) && ((now1->name == "NO3-" && now2->name == "H+")
				|| (now2->name == "NO3-" && now1->name == "H+"))) {
				now1->color.setHex(0xf5492f);
				now1->name = "N2";
				now2->color.setHex(0xf5492f);
				now2->name = "N2";
				now1->bHit = true;
				sound[now1->soundID].play();
				now2->bHit = true;
				sound[now2->soundID].play();
			}
			
		}
	}
}

void ofApp::contactEnd(ofxBox2dContactArgs &e) {
		if (e.a != NULL && e.b != NULL) {
			Data *now1 = (Data*)e.b->GetBody()->GetUserData();
			Data *now2 = (Data*)e.a->GetBody()->GetUserData();
			if (now1) {
				now1->bHit = false;
			}
			if (now2) {
				now2->bHit = false;
			}
		}
}
//--------------------------------------------------------------
void ofApp::update() {

	box2d.update();

	if (sc == scene1) {
		if (customParticles.empty()) {
			sc = scene2;
			setup();
		}
		if (down && ofGetFrameNum() % 20 == 0) {
			auto circle = std::make_shared<CustomParticle>(box2d.getWorld(), ofGetWidth() / 6 + ofRandom(-100, 100), -200 + ofRandom(30, 100),
				ofRandom(15, 25), 0x0a694f, 8);
			circle->setPhysics(0.1,0.3,0);
			circle->setVelocity(0, 0);
			circles.push_back(circle);
		}

		if (down && ofGetFrameNum() % 20 == 10) {
			auto circle = std::make_shared<CustomParticle>(box2d.getWorld(), 5 * ofGetWidth() / 6 + ofRandom(-100, 100), -200 + ofRandom(30, 100),
				ofRandom(15, 25), 0x0a4569, 2);
			circle->setPhysics(0.1,0.3,0);
			circle->setVelocity(0, 0);
			hidro.push_back(circle);
		}

		for (auto &particle : customParticles) {
			particle->update();
		}

		ofRemove(polyShapes, [](shared_ptr<ofxBox2dPolygon> shape) -> bool {
			return !ofRectangle(0, -400, ofGetWidth(), ofGetHeight() + 400).inside(shape->getPosition());
		});
		ofRemove(customParticles, [](shared_ptr<CustomParticle> shape) -> bool {
			return !ofRectangle(0, -400, ofGetWidth(), ofGetHeight() + 400).inside(shape->getPosition());
		});
	}
	else if (sc == scene2) {
		if (customParticles.empty()) {
			sc = scene3;
			setup();
		}
		if (down && ofGetFrameNum() % 20 == 0) {
			auto circle = std::make_shared<CustomParticle>(box2d.getWorld(), ofGetWidth() / 6 + ofRandom(-100, 100), -200 + ofRandom(30, 100),
				ofRandom(15, 25), 0x157d33, 3);
			circle->setPhysics(0.5, 0.1, 0.1);
			circle->setVelocity(0, 0);
			circles.push_back(circle);
		}
		for (auto &particle : customParticles) {
			particle->update2();
		}
	}
	else if (sc == scene3) {
		if (customParticles.empty()) {
			sc = scene1;
			setup();
		}
		if (down && ofGetFrameNum() % 20 == 0) {
			auto circle = std::make_shared<CustomParticle>(box2d.getWorld(), ofGetWidth() / 6 + ofRandom(-100, 100), -200 + ofRandom(30, 100),
				ofRandom(15, 25), 0x199eb3, 5);
			circle->setPhysics(0.5, 0.1, 0.1);
			circle->setVelocity(0, 0);
			circles.push_back(circle);
		}
	}
}


//--------------------------------------------------------------
void ofApp::draw() {
	
	if (sc == scene1) {
		ofSetHexColor(0xfafafa);
		bg1.draw(0,0,ofGetWidth(), ofGetHeight());
		ofSetHexColor(0xdbdbd7);
	}
	if (sc == scene2) {
		ofSetHexColor(0xfafafa);
		plant.draw(ofGetWidth() - 215, ofGetHeight()/3+80, 150, 250);
		bg2.draw(0, 0, ofGetWidth(), ofGetHeight());
		ofSetHexColor(0x8c4826);
	}
	if (sc == scene3) {
		ofSetHexColor(0xfafafa);
		bg3.draw(0, 0, ofGetWidth(), ofGetHeight());
		ofSetHexColor(0x26378c);
	}
		rect1.draw();
		rect2.draw();
		rect3.draw();
		rect4.draw();
		for (auto &circle : circles) {
			ofFill();
			ofSetHexColor(0x90d4e3);
			circle->draw();
		}

		for (auto &circle : hidro) {
			ofFill();
			ofSetHexColor(0x90d4e3);
			circle->draw();
		}

		for (auto &particle : customParticles) {
			particle->draw();
		}

		ofNoFill();
		ofSetHexColor(0xf5f5f5);
		if (drawing.size() == 0) {
			edgeLine.draw();
		}
		else drawing.draw();

		//ofSetHexColor(0x444342);
		ofFill();
		shape.draw();

		//ofSetHexColor(0x444342);
		bFill ? ofFill() : ofNoFill();
		for (auto & poly : polyShapes) {
			poly->isTriangulated() ? poly->drawTriangles() : poly->draw();
		}

		string info = "";
		info += "Press c to clear everything\n";
		info += "Press a to collect the goal particle\n";
		info += "Press b to fill the polygon\n";
		info += "Press t to break object up into triangles/convex poly: " + string(breakupIntoTriangles ? "true" : "false") + "\n";
		info += "Press d to start/stop particles from falling down: " + string(down ? "true" : "false") + "\n";
		info += "remain: " + ofToString(customParticles.size()) + "\n";
		if(sc==scene2) ofSetHexColor(0x292828);
		else ofSetHexColor(0xf5f5f5);
		ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 't') breakupIntoTriangles = !breakupIntoTriangles;
	if (key == 'b') bFill = !bFill;
	if (key == 'd') down = !down;
	if (key == 'c') {
		shape.clear();
		polyShapes.clear();
		circles.clear();
		hidro.clear();
	}
	if (key == 'a') {
		auto iter = customParticles.begin();
		while (iter != customParticles.end()) {
			Data* now = (Data*)(*iter)->getData();
			if ((sc==scene1 && now->name == "NH3")
				|| (sc == scene2 && now->name == "NO3-")
				|| (sc==scene3 && now->name=="N2")) {
				goal++;
				//box2d.world->DestroyBody((*iter)->body);
				iter = customParticles.erase(iter);
			}
			else ++iter;
		}
		iter = circles.begin();
		while (iter != circles.end()) {
			Data* now = (Data*)(*iter)->getData();
			if ((sc == scene1 && now->name == "NH3")
				|| (sc == scene2 && now->name == "NO3-")
				|| (sc == scene3 && now->name == "N2")) {
				goal++;
				iter = circles.erase(iter);
			}
			else ++iter;
		}
		iter =hidro.begin();
		while (iter != hidro.end()) {
			Data* now = (Data*)(*iter)->getData();
			if ((sc == scene1 && now->name == "NH3")
				|| (sc == scene2 && now->name == "NO3-")
				|| (sc == scene3 && now->name == "N2")) {
				goal++;
				iter = hidro.erase(iter);
			}
			else ++iter;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	shape.addVertex(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	shape.clear();
	shape.addVertex(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	if (breakupIntoTriangles) {

		// This is the manual way to triangulate the shape
		// you can then add many little triangles

		// first simplify the shape
		shape.simplify();

		// resample shape
		auto resampled = shape.getResampledBySpacing(25);

		// triangulate the shape, return am vector of traingles
		auto tris = ofxBox2dPolygonUtils::triangulate(resampled);

		// now loop through all the triangles and make a box2d triangle
		for (int i = 0; i < tris.size(); i++) {

			auto triangle = std::make_shared<ofxBox2dPolygon>();

			triangle->addTriangle(ofDefaultVertexType(tris[i].a.x, tris[i].a.y, 0),
				ofDefaultVertexType(tris[i].b.x, tris[i].b.y, 0),
				ofDefaultVertexType(tris[i].c.x, tris[i].c.y, 0));

			triangle->setPhysics(1.0, 0.3, 0.3);

			triangle->create(box2d.getWorld());

			polyShapes.push_back(triangle);
		}

	}
	else {
		auto poly = std::make_shared<ofxBox2dPolygon>();
		poly->addVertices(shape.getVertices());
		poly->setPhysics(3, 0, 0);
		poly->triangulate();
		poly->create(box2d.getWorld());
		polyShapes.push_back(poly);
	}

	// done with shape clear it now
	shape.clear();
}

//--------------------------------------------------------------
void ofApp::resized(int w, int h) {

}
