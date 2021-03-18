#include "ofApp.h"
#pragma region helpers_setup

void ofApp::loadConfig() {
	cout << "Loading config ... " << endl;
	bool loaded = settings.loadFile("config/config.xml");
	string appname = settings.getValue("config:name", "");
	string version = settings.getValue("config:version", "1.0.0.0");
	settings.pushTag("config");
	settings.pushTag("levels");
	vector<Level> config_levels;
	int num_levels = settings.getNumTags("level");
	for (int i = 0; i < num_levels; i++) {
		settings.pushTag("level", i);
		Level level;
		level.id = settings.getValue("id", 0);
		level.shots = settings.getValue("shots", 0);
		settings.pushTag("ships");
		int num_ships = settings.getNumTags("ship");
		for (size_t j = 0; j < num_ships; j++) {
			settings.pushTag("ship", j);
			ShipConfig shipconfig;
			shipconfig.type = settings.getValue("type", 0);
			shipconfig.x = settings.getValue("x", 0);
			shipconfig.y = settings.getValue("y", 0);
			shipconfig.z = settings.getValue("z", 0);
			shipconfig.vx = settings.getValue("vx", 0);
			shipconfig.vz = settings.getValue("vz", 0);
			level.ships.push_back(shipconfig);
			settings.popTag();
		}
		settings.popTag();
		config_levels.push_back(level);
		settings.popTag();
	}
	settings.popTag();
	settings.popTag();
	config.appname = appname;
	config.version = version;
	config.levels = config_levels;
	cout << "DONE!" << endl;
}

void ofApp::loadSounds() {
	cout << "Loading sounds ... " << endl;
	sound_cannon.load("sounds/cannon.mp3");
	sound_splash.load("sounds/splash.mp3");
	sound_explode.load("sounds/bomb.mp3");
	sound_win.load("sounds/win.mp3");
	sound_lose.load("sounds/lose.mp3");
	sound_background.load("sounds/pirate_ship_at_bay.mp3");
	sound_background2.load("sounds/harry.mp3");
	cout << "DONE!" << endl;
}

void ofApp::loadModels() {
	cout << "Loading models ... " << endl;
	World::loadModel();
	Cannon::loadModel();
	Guardian::loadModel();
	cout << "DONE!" << endl;
}

void ofApp::loadFonts() {
	cout << "Loading fonts ... " << endl;
	ofTrueTypeFont::setGlobalDpi(72);
	verdana14.load("fonts/verdana.ttf", 14, true, true);
	verdana14.setLineHeight(18.0f);
	verdana14.setLetterSpacing(1.037);
	verdana30.load("fonts/verdana.ttf", 30, true, true);
	verdana30.setLineHeight(34.0f);
	verdana30.setLetterSpacing(1.035);
	cout << "DONE!" << endl;
}

void ofApp::loadImages()
{
	cout << "Loading config ... " << endl;
	skull_image.load("images/skull.png");
	wincup_image.load("images/wincup.png");
	cannon_image.load("images/cannon.png");
	galleon_image.load("images/hogwarts.jpg");
	cout << "DONE!" << endl;
}

void setLightOri(ofLight &light, ofVec3f rot){
	ofPoint x_axis = ofPoint(1, 0, 0);
	ofPoint y_axis = ofPoint(0, 1, 0);
	ofPoint z_axis = ofPoint(0, 0, 1);
	ofQuaternion q;
	q.makeRotate(rot.x, x_axis, rot.y, y_axis, rot.z, z_axis);
	light.setOrientation(q);
}
void ofApp::configureLights() {
	light_directional.setDiffuseColor(ofColor(255, 255, 255));
	light_directional.setSpecularColor(ofColor(255, 255, 255));
	light_directional.setDirectional();
	ofPoint rotation = ofPoint(0, 200, 0);
	setLightOri(light_directional, rotation);
}

void ofApp::configureCameras() {
	camera0.setAutoDistance(false);
	camera0.setPosition(220, 80, 300);
	camera0.setTarget(ofPoint(100, 0, 140));
	cameras.push_back(&camera0);

	camera1.setAutoDistance(false);
	camera1.disableMouseInput();
	camera1.setPosition(220, 80, 300);
	camera1.setTarget(ofPoint(100, 0, 140));
	cameras.push_back(&camera1);
	
	camera2.setAutoDistance(false);
	camera2.disableMouseInput();
	camera2.setPosition(100, 20, 215);
	camera2.setTarget(ofPoint(100, 20, 100));
	cameras.push_back(&camera2);
	
	camera3.setAutoDistance(false);
	camera3.disableMouseInput();
	camera3.setPosition(100, 240, 140);
	camera3.setTarget(ofPoint(100, 0, 140));
	cameras.push_back(&camera3);

	camera4.setAutoDistance(false);
	camera4.disableMouseInput();
	camera4.setPosition(50, 5, 200);
	camera4.setTarget(ofPoint(100, 5, 280));
	cameras.push_back(&camera4);
}

void ofApp::setup_level(int id) {
	guard.clear();
	Level level;
	bool found = false;
	for (size_t i = 0; i < config.levels.size(); i++){
		if (config.levels[i].id == id){
			level = config.levels[i];
			found = true;
			break;
		}
	}
	/*if (!found)
	{
		cout << "No level found with id: " + ofToString(id) << endl;
	}*/
	cannon = Cannon(level.shots);
	cannon.setPosition(ofPoint(100, -3, 215));
	for (size_t i = 0; i < level.ships.size(); i++){
		Guardian ship = Guardian();
		ship.setPosition(ofPoint(level.ships[i].x, level.ships[i].y - 2, level.ships[i].z));
		ship.setVelocity(ofPoint(level.ships[i].vx, 0, level.ships[i].vz));
		ship.setModelType(level.ships[i].type);
		guard.push_back(ship);		
	}
}
#pragma endregion;

#pragma region helpers_setup
void ofApp::updateGameStatus()
{
	if (game_status == "START") return;
	if (guard.size() == 0) {
		if (game_status != "LEVELWIN" && game_status != "GAMEWIN") {
			sound_win.setVolume(0.03);
			sound_win.play();
		}
		game_status = "LEVELWIN";

		if (current_level + 1 > config.levels.size()) {
			game_status = "GAMEWIN";
			camera_selected = 4;
		}
	}

	if (cannon.getShots() == 0 && cannon.bullets.size() == 0 && guard.size() > 0) {
		if (game_status != "LOSE") sound_lose.play();
		game_status = "LOSE";
	}
}
#pragma endregion;

#pragma region helpers_draw

void ofApp::drawIndicators() {
	ofPushMatrix();
		ofTranslate(20, 20);
		float shots_perc = roundf(cannon.getShots() * 100 / cannon.getTotalShots());
		ofSetColor(0, 0, 0, 150);
		ofRectangle box = ofRectangle(0, 0, 200, 20);
		ofDrawRectangle(box);
		ofSetColor(40, 240, 40, 150);
		box.setWidth(shots_perc * 2);
		ofDrawRectangle(box);
		ofSetColor(255, 255, 255);
		verdana14.drawString(ofToString(cannon.getShots()) + " / " + ofToString(cannon.getTotalShots()), 5, 15);
		ofSetColor(255, 255, 255);
		verdana14.drawString("shots", 210, 15);
	ofPopMatrix();

	ofPushMatrix();
		ofTranslate(20, ofGetHeight() - 40);
		ofSetColor(0, 0, 0, 150);
		box.setWidth(200);
		ofDrawRectangle(box);
		ofSetColor(240, 40, 40, 150);
		box.setWidth(bullet_speed_perc * 2);
		ofDrawRectangle(box);
		ofSetColor(255, 255, 255);
		verdana14.drawString(ofToString(roundf(bullet_speed_perc)), 5, 15);
		ofSetColor(255, 255, 255);
		verdana14.drawString("speed", 210, 15);
	ofPopMatrix();

	ofPushMatrix();
		ofTranslate(20, ofGetHeight() - 70);
		ofSetColor(0, 0, 0, 150);
		box.setWidth(200);
		ofDrawRectangle(box);
		ofSetColor(240, 200, 40, 150);
		box.setWidth(ofMap(cannon.getAngle(), cannon.ANGLE_MIN, cannon.ANGLE_MAX, 0, 200) );
		ofDrawRectangle(box);
		ofSetColor(255, 255, 255);
		verdana14.drawString(ofToString(roundf(cannon.getAngle())), 5, 15);
		ofSetColor(255, 255, 255);
		verdana14.drawString("angle", 210, 15);
	ofPopMatrix();
}

void ofApp::drawStartView() {
	ofPushMatrix();
		ofTranslate(20, 20);
		ofRectangle box = ofRectangle(0, 0, ofGetWidth() - 40, 200);
		ofSetColor(255, 255, 255, 255);
		ofDrawRectangle(box);
		galleon_image.draw(20, 20, 170, 150);
		ofSetColor(50, 50, 50);
		verdana30.drawString("Conquer Hogwarts", 200, 50);
		verdana14.drawString("press ENTER key to start", 200, 130);
		verdana14.drawString("press h key for help", 200, 100);
		verdana14.drawString("press q key to quit", 200, 160);
	ofPopMatrix();
}

void ofApp::drawGameOverView() {
	ofPushMatrix();
		ofTranslate(ofGetWidth() / 2 - 300, ofGetHeight() / 2 - 200);
		ofRectangle box = ofRectangle(0, 0, 600, 400);
		ofSetColor(255, 255, 255, 255);
		ofDrawRectangle(box);
		ofSetColor(50, 50, 50);
		verdana30.drawString("Wizarts defeated you!\nYou have no more bullets!", 20, 50);
		skull_image.draw(200, 100, 200, 200);
		verdana14.drawString("press ENTER key to restart game", 20, 350);
		verdana14.drawString("press q key to quit game", 20, 370);
	ofPopMatrix();
}

void ofApp::drawLevelWinView() {
	ofPushMatrix();
		ofTranslate(ofGetWidth()/2 -300 , ofGetHeight()/2 -200);
		ofRectangle box = ofRectangle(0, 0, 600, 400);
		ofSetColor(255, 255, 255, 255);
		ofDrawRectangle(box);
		ofSetColor(50, 50, 50);
		verdana30.drawString("Congratulations! You win level " + ofToString(current_level), 20, 50);
		wincup_image.draw(200, 100, 200, 200);
		verdana14.drawString("press ENTER key for next level", 20, 350);
	ofPopMatrix();
}

void ofApp::drawGameWinView() {
	ofPushMatrix();
		ofTranslate(ofGetWidth() / 2 - 300, ofGetHeight() / 2 - 200);
		ofRectangle box = ofRectangle(0, 0, 600, 400);
		ofSetColor(255, 255, 255, 255);
		ofDrawRectangle(box);
		ofSetColor(50, 50, 50);
		verdana30.drawString("Congratulations! You win the game!\nHogwarts is yours now!", 20, 50);
		cannon_image.draw(200, 100, 200, 200);
		verdana14.drawString("press ENTER key to restart game", 20, 350);
		verdana14.drawString("press q key to quit game", 20, 370);
	ofPopMatrix();
}

void ofApp::drawHelpView() {
	ofPushMatrix();
		ofTranslate(20, ofGetHeight() - 320);
		ofRectangle box = ofRectangle(0, 0, ofGetWidth() - 40, 300);
		ofSetColor(255, 255, 255, 255);
		ofDrawRectangle(box);
		ofSetColor(50, 50, 50);
		verdana30.drawString("Game keys", 20, 50);
		verdana14.drawString("1, 2, 3, 4 :           change game camera", 20, 100);
		verdana14.drawString("arrow left/right :     move cannon left/right", 20, 130);
		verdana14.drawString("arrow up/down :        increase/decrease cannon shooter angle", 20, 160);
		verdana14.drawString("s :                    shoot, more you press more long the shoot will be", 20, 190);
		verdana14.drawString("h :                    toggle help", 20, 220);
		verdana14.drawString("q :                    quit from game", 20, 250);
	ofPopMatrix();
}
#pragma endregion;

#pragma region of_functions
//--------------------------------------------------------------
void ofApp::setup() {
	loadConfig();
	loadSounds();
	loadModels();
	loadFonts();
	loadImages();

	/*cout << "app name: " << config.appname << endl;
	cout << "version: " << config.version << endl;*/
	
	sound_background.setLoop(true);
	sound_background.setVolume(0.07);
	sound_background.play();

	sound_background2.setLoop(true);
	sound_background2.setVolume(0.5);
	sound_background2.play();

	configureLights();
	configureCameras();
	
	Guardian::setSeaLimits(ofPoint(0, 0, 20), ofPoint(200, 0, 180));
	cannon = Cannon();
	cannon.setPosition(ofPoint(100, -3, 215));
	camera2.setPosition(cannon.getPosition() + ofPoint(5, 10, 10));
	camera4.setPosition(cannon.getPosition() + ofPoint(5, 5, -40));
	camera4.setTarget(cannon.getPosition() + ofPoint(5, 5, 20));
	camera_selected = 4;
	ofBackground(46, 167, 191);
}

//--------------------------------------------------------------
void ofApp::update() {
	ofSoundUpdate();
	updateGameStatus();
	if (shoot_key_pressed) {
		float time = ofGetElapsedTimef();
		float dt = time - shoot_press_start_time;
		bullet_speed_perc = ofMap(dt, 0, 1, 0, 100, true);
	}
	if (left_key_pressed) cannon.moveLeft();
	if (right_key_pressed) cannon.moveRight();
	if (up_key_pressed) cannon.rotateUp();
	if (down_key_pressed) cannon.rotateDown();
	cannon.update();
	camera2.setPosition(cannon.getPosition() + ofPoint(5, 10, 10));
	camera4.setPosition(cannon.getPosition() + ofPoint(5, 5, -40));
	camera4.setTarget(cannon.getPosition() + ofPoint(5, 5, 20));

	for (size_t i = 0; i < guard.size(); i++) guard[i].update();

	for (size_t j = 0; j < cannon.bullets.size(); j++){
		cannon.bullets[j].update();
		ofPoint bullet_position = cannon.bullets[j].getPosition();
		if (bullet_position.y <= 0){
			if (bullet_position.z >= 40){
				ofPoint animation_point = bullet_position + ofPoint(0, -3, 0);
				WaterHoleAnimation animation = WaterHoleAnimation(animation_point);
				animationEmitter.addWaterHoleAnimation(animation);
				sound_splash.play();
			}
			else {
				ofPoint animation_point = bullet_position;
				ExplosionAnimation animation = ExplosionAnimation(animation_point);
				animationEmitter.addExplosionAnimation(animation);
				sound_explode.setVolume(0.01);
				sound_explode.play();
			}
			cannon.bullets.erase(cannon.bullets.begin() + j);
			break;
		}
		if ( world.isPointInsideWorld(cannon.bullets[j].getPosition()) == false ){
			cannon.bullets.erase(cannon.bullets.begin() + j);
			break;
		}
	}

	for (size_t i = 0; i < guard.size(); i++){
		for (size_t j = 0; j < cannon.bullets.size(); j++){
			if (guard[i].isPointInShip(cannon.bullets[j].getPosition())){	
				ofPoint animation_point = guard[i].getPosition() + ofPoint(0, -3, 0) + ofPoint(10.5, 0, -5);
				ExplosionAnimation animation = ExplosionAnimation(animation_point);
				animationEmitter.addExplosionAnimation(animation);
				sound_explode.setVolume(0.01);
				sound_explode.play();
				guard.erase(guard.begin() + i);
				cannon.bullets.erase(cannon.bullets.begin() + j);
				break;
			}
		}
	}
	animationEmitter.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofEnableDepthTest();
	ofEnableAlphaBlending();
	ofSeedRandom(0);

	light_directional.enable();
	light_directional.draw();
	light_ambient.enable();
	light_ambient.draw();

	cameras[camera_selected]->begin();
	world.draw();
	animationEmitter.draw();
	for (size_t i = 0; i < guard.size(); i++) guard[i].draw();
	cannon.draw();
	cameras[camera_selected]->end();
	ofDisableDepthTest();

	if (game_status == "START") drawStartView();
	if (game_status == "LEVELWIN") drawLevelWinView();
	if (game_status == "GAMEWIN") drawGameWinView();
	if (game_status == "LOSE") drawGameOverView();
	if (game_status == "PLAY") drawIndicators();
	if (help_visible) drawHelpView();
}
#pragma endregion

#pragma region of_events

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == OF_KEY_LEFT) left_key_pressed = true;
	if (key == OF_KEY_RIGHT) right_key_pressed = true;
	if (key == OF_KEY_UP) up_key_pressed = true;
	if (key == OF_KEY_DOWN) down_key_pressed = true;

	if (key == 's'){
		if (shoot_key_pressed == false){
			shoot_press_start_time = ofGetElapsedTimef();
			shoot_key_pressed = true;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (key == OF_KEY_RETURN){
		if (game_status == "PLAY") return;
		if (game_status == "LOSE") current_level = 0;
		current_level++;
		if (current_level <= config.levels.size()){
			game_status = "PLAY";
			setup_level(current_level);
			if (current_level == 1) camera_selected = 1;
		}
		if (current_level > config.levels.size()){
			current_level = 0;
			game_status = "START";
		}
	}
	if (key == 'q') ofExit();
	if (key == OF_KEY_LEFT) left_key_pressed = false;
	if (key == OF_KEY_RIGHT) right_key_pressed = false;
	if (key == OF_KEY_UP) up_key_pressed = false;
	if (key == OF_KEY_DOWN) down_key_pressed = false;

	if (key == 's'){
		shoot_key_pressed = false;
		if (cannon.getShots() <= 0) return;
		float bullet_speed = ofMap(bullet_speed_perc, 0, 100, MIN_SHOOT_SPEED, MAX_SHOOT_SPEED, true);
		cannon.shoot(bullet_speed);
		sound_cannon.setVolume(0.03);
		sound_cannon.play();
	}
	if (key == 'h') help_visible = !help_visible;
	if (key == '1') camera_selected = 1;
	if (key == '2') camera_selected = 2;
	if (key == '3') camera_selected = 3;
	if (key == '4') camera_selected = 4;
	if (key == '9') camera_selected = 0;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

#pragma endregion



