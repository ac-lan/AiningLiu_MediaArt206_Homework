#include "Scene2.h"

//--------------------------------------------------------------
/*void Scene2::setup() {

	ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL);

	bMouseForce = false;
	breakupIntoTriangles = false;
	bFill = false;

	goal = 0;

	box2d.init();
	box2d.setGravity(0, 10);
	box2d.createGround();
	box2d.setFPS(60.0);
	box2d.enableEvents();
	//box2d.registerGrabbing();

	ofAddListener(box2d.contactStartEvents, this, &Scene2::contactStart);
	ofAddListener(box2d.contactEndEvents, this, &Scene2::contactEnd);

	rect1.setPhysics(0, 0, 0);
	rect1.setup(box2d.getWorld(), ofGetWidth() / 3 - 10, 4 * ofGetHeight() / 5, ofGetWidth() / 18, ofGetHeight() / 2);

	rect2.setPhysics(0, 0, 0);
	rect2.setup(box2d.getWorld(), ofGetWidth() / 3 - 10, ofGetHeight() / 5, ofGetWidth() / 18, ofGetHeight() / 2);

	rect3.setPhysics(0, 0, 0);
	rect3.setup(box2d.getWorld(), 2 * ofGetWidth() / 3 - 10, 4 * ofGetHeight() / 5, ofGetWidth() / 18, ofGetHeight() / 2);

	rect4.setPhysics(0, 0, 0);
	rect4.setup(box2d.getWorld(), 2 * ofGetWidth() / 3 - 10, ofGetHeight() / 5, ofGetWidth() / 18, ofGetHeight() / 2);

	for (int i = 0; i < 30; i++) {
		auto particle = std::make_shared<CustomParticle>(box2d.getWorld(), ofRandom(ofGetWidth() / 3, 2 * ofGetWidth() / 3 - 10),
			ofRandom(0, ofGetHeight()), ofRandom(20, 30), 255, 0);
		customParticles.push_back(particle);
	}

	for (int i = 0; i < N_SOUNDS; i++) {
		sound[i].load("sfx/" + ofToString(i) + ".mp3");
		sound[i].setMultiPlay(true);
		sound[i].setLoop(false);
	}
}

void Scene2::contactStart(ofxBox2dContactArgs &e) {
	if (e.a != NULL && e.b != NULL) {
		Data *now1 = (Data*)e.b->GetBody()->GetUserData();
		Data *now2 = (Data*)e.a->GetBody()->GetUserData();
		if ((now1 != NULL && now2 != NULL) && (((now1->name == "micro" || now1->name == "H2") && now2->name == "N2")
			|| (now1->name == "N2" && (now2->name == "micro" || now2->name == "H2")))) {
			now1->color.setHex(0x4ccae9);
			now1->name = "NH3";
			now2->color.setHex(0x4ccae9);
			now2->name = "NH3";
			now1->bHit = true;
			sound[now1->soundID].play();
			now2->bHit = true;
			sound[now2->soundID].play();
		}
	}
}

void Scene2::contactEnd(ofxBox2dContactArgs &e) {
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
void Scene2::update() {

	box2d.update();

	//cout << customParticles.size() << endl;
	if (ofGetFrameNum() % 100 == 0) {
		auto circle = std::make_shared<CustomParticle>(box2d.getWorld(), ofGetWidth() / 6 + ofRandom(-100, 100), -200 + ofRandom(30, 100),
			ofRandom(10, 20), 20, 8);
		circle->setPhysics(0.5, 0.1, 0.1);
		circle->setVelocity(0, 0);
		circles.push_back(circle);
	}

	if (ofGetFrameNum() % 100 == 50) {
		auto circle = std::make_shared<CustomParticle>(box2d.getWorld(), 5 * ofGetWidth() / 6 + ofRandom(-100, 100), -200 + ofRandom(30, 100),
			ofRandom(10, 20), 105, 2);
		circle->setPhysics(0.5, 0.1, 0.1);
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


//--------------------------------------------------------------
void Scene2::draw() {
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
	ofSetHexColor(0x444342);
	if (drawing.size() == 0) {
		edgeLine.draw();
	}
	else drawing.draw();

	ofSetHexColor(0x444342);
	ofFill();
	shape.draw();

	ofSetHexColor(0x444342);
	bFill ? ofFill() : ofNoFill();
	for (auto & poly : polyShapes) {
		poly->isTriangulated() ? poly->drawTriangles() : poly->draw();
	}

	string info = "";
	info += "Press [s] to draw a line strip [" + ofToString(bDrawLines) + "]\n";
	info += "Press [f] to toggle Mouse Force [" + ofToString(bMouseForce) + "]\n";
	info += "Press c to clear everything\n";
	info += "Press b to toggle fill\n";
	info += "Press t to break object up into triangles/convex poly: " + string(breakupIntoTriangles ? "true" : "false") + "\n";
	/*info += "Press [c] for circles\n";
	info += "Press [b] for blocks\n";
	info += "Press [z] for custom particle\n";
	info += "Total Bodies: " + ofToString(box2d.getBodyCount()) + "\n";
	info += "Total Joints: " + ofToString(box2d.getJointCount()) + "\n\n";*/
	/*info += "goal: " + ofToString(customParticles.size()) + "\n";
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void Scene2::keyPressed(int key) {
	if (key == 't') breakupIntoTriangles = !breakupIntoTriangles;
	if (key == 'b') bFill = !bFill;
	if (key == 'c') {
		shape.clear();
		polyShapes.clear();
		circles.clear();
	}
	if (key == 'a') {
		auto iter = customParticles.begin();
		while (iter != customParticles.end()) {
			Data* now = (Data*)(*iter)->getData();
			if (now->name == "NH3") {
				goal++;
				//box2d.world->DestroyBody((*iter)->body);
				iter = customParticles.erase(iter);
			}
			else ++iter;
		}
		iter = circles.begin();
		while (iter != circles.end()) {
			Data* now = (Data*)(*iter)->getData();
			if (now->name == "NH3") {
				goal++;
				iter = circles.erase(iter);
			}
			else ++iter;
		}
		iter = hidro.begin();
		while (iter != hidro.end()) {
			Data* now = (Data*)(*iter)->getData();
			if (now->name == "NH3") {
				goal++;
				iter = hidro.erase(iter);
			}
			else ++iter;
		}
	}
}

//--------------------------------------------------------------
void Scene2::keyReleased(int key) {

}

//--------------------------------------------------------------
void Scene2::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void Scene2::mouseDragged(int x, int y, int button) {
	shape.addVertex(x, y);
}

//--------------------------------------------------------------
void Scene2::mousePressed(int x, int y, int button) {
	shape.clear();
	shape.addVertex(x, y);
}

//--------------------------------------------------------------
void Scene2::mouseReleased(int x, int y, int button) {
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
		poly->setPhysics(1.0, 0.3, 0.3);
		poly->triangulate();
		poly->create(box2d.getWorld());
		polyShapes.push_back(poly);
	}

	// done with shape clear it now
	shape.clear();
}

//--------------------------------------------------------------
void Scene2::resized(int w, int h) {

}*/
