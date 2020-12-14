#include "ofApp.h"



// helpers setup 
#pragma region helpers_setup

// loading

void ofApp::saveGame() {
	
	cout << "Saving game state ... " << endl;

	bool loaded = gamestate.loadFile("save.xml");
	
	if (loaded) {
		gamestate.clear();
	}
	
	gamestate.addTag("gamestate");
	gamestate.pushTag("gamestate");

	gamestate.addValue("level", current_level);

	gamestate.addTag("cannon");
	gamestate.pushTag("cannon");
		
	gamestate.addTag("position");
	gamestate.pushTag("position");

	gamestate.addValue("x", cannon.getPosition().x);
	gamestate.addValue("y", cannon.getPosition().y);
	gamestate.addValue("z", cannon.getPosition().z);

	gamestate.popTag();
	
	gamestate.addValue("totalshots", cannon.getTotalShots());
	gamestate.addValue("shots", cannon.getShots());
	gamestate.addValue("angle", cannon.getAngle());

	gamestate.popTag();

	gamestate.addTag("ships");
	gamestate.pushTag("ships");

	for (size_t i = 0; i < ships.size(); i++)
	{

		gamestate.addTag("ship");
		gamestate.pushTag("ship", i);
		
		gamestate.addValue("type", ships[i].getModelType());
		gamestate.addValue("x", ships[i].getPosition().x);
		gamestate.addValue("y", ships[i].getPosition().y);
		gamestate.addValue("z", ships[i].getPosition().z);
		gamestate.addValue("vx", ships[i].getVelocity().x);
		gamestate.addValue("vz", ships[i].getVelocity().z);
		
		gamestate.popTag();

	}
	gamestate.popTag();
	gamestate.popTag();
	gamestate.saveFile("save.xml");
	
	cout << "DONE!" << endl;

}


void ofApp::loadGame() {
	

	cout << "Loading game state ... " << endl;

	bool loaded = gamestate.loadFile("save.xml");

	if (!loaded) {
		ofLogError("Saved file not found!");
		return;
	}
	
	gamestate.pushTag("gamestate");

	current_level = gamestate.getValue("level", 1);

	gamestate.pushTag("cannon");

	cannon.setShots(gamestate.getValue("shots", 0) );
	cannon.setTotalShots(gamestate.getValue("totalshots", 0));
	cannon.setAngle(gamestate.getValue("angle", 0) );
	
	gamestate.pushTag("position");
		
	float x = gamestate.getValue("x", 0);
	float y = gamestate.getValue("y", 0);
	float z = gamestate.getValue("z", 0);
	
	cannon.setPosition(ofPoint(x, y, z));

	gamestate.popTag();
	gamestate.popTag();

	gamestate.pushTag("ships");

	ships.clear();

	int num_ships = gamestate.getNumTags("ship");

	for (size_t j = 0; j < num_ships; j++) {

		gamestate.pushTag("ship", j);
		
		int type = gamestate.getValue("type", 0);
		float x = gamestate.getValue("x", 0);
		float y = gamestate.getValue("y", 0);
		float z = gamestate.getValue("z", 0);
		float vx = gamestate.getValue("vx", 0);
		float vz = gamestate.getValue("vz", 0);
		
		Ship ship = Ship();
		ship.setModelType(type);
		ship.setPosition(ofPoint(x, y, z));
		ship.setVelocity(ofPoint(vx, 0, vz));
		ships.push_back(ship);

		gamestate.popTag();
	}

	gamestate.popTag();
	gamestate.popTag();
	

	cout << "DONE!" << endl;

}


void ofApp::loadConfig() {

	cout << "Loading config ... " << endl;

	bool loaded = settings.loadFile("config/config.xml");
	
	if (!loaded) {
		ofLogError("Position file did not load!");
		return;
	}
	
	string appname = settings.getValue("config:name", "");
	string version = settings.getValue("config:version", "1.0.0.0");


	
	settings.pushTag("config");
	
	settings.pushTag("levels");
	
	
	vector<Level> config_levels;


	int num_levels = settings.getNumTags("level");
	//cout << "num_levels: " << num_levels << endl;
	for (int i = 0; i < num_levels; i++) {

		settings.pushTag("level", i);

		Level level;
		level.id = settings.getValue("id", 0);
		level.shots = settings.getValue("shots", 0);

		settings.pushTag("ships");

		int num_ships = settings.getNumTags("ship");
		//cout << "num_ships: " << num_ships << endl;
		
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
	Ship::loadModel();

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

	//grass_texture.load("images/grass.jpg");
	skull_image.load("images/skull.png");
	wincup_image.load("images/wincup.png");
	cannon_image.load("images/cannon.png");
	galleon_image.load("images/hogwarts.jpg");
	
	
	cout << "DONE!" << endl;
}


// settings

void setLightOri(ofLight &light, ofVec3f rot)
{
		
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
	//ofPoint rotation = ofPoint(0, -95, 0);
	ofPoint rotation = ofPoint(0, 200, 0);
	setLightOri(light_directional, rotation);
	
	//light_ambient.setAmbientColor(ofColor(20, 20, 20));

}


void ofApp::configureCameras() {
	
	// free camera
	camera0.setAutoDistance(false);
	camera0.setPosition(220, 80, 300);
	camera0.setTarget(ofPoint(100, 0, 140));
	cameras.push_back(&camera0);

	// standard camera
	camera1.setAutoDistance(false);
	camera1.disableMouseInput();
	camera1.setPosition(220, 80, 300);
	camera1.setTarget(ofPoint(100, 0, 140));
	cameras.push_back(&camera1);
	
	// cannon camera
	camera2.setAutoDistance(false);
	camera2.disableMouseInput();
	camera2.setPosition(100, 20, 215);
	camera2.setTarget(ofPoint(100, 20, 100));
	cameras.push_back(&camera2);
	
	// top camera
	camera3.setAutoDistance(false);
	camera3.disableMouseInput();
	camera3.setPosition(100, 240, 140);
	camera3.setTarget(ofPoint(100, 0, 140));
	cameras.push_back(&camera3);

	// front camera
	camera4.setAutoDistance(false);
	camera4.disableMouseInput();
	camera4.setPosition(50, 5, 200);
	camera4.setTarget(ofPoint(100, 5, 280));
	cameras.push_back(&camera4);
	
}


void ofApp::setup_level(int id) {
	
	ships.clear();

	Level level;
	bool found = false;
	
	for (size_t i = 0; i < config.levels.size(); i++)
	{
		if (config.levels[i].id == id)
		{
			level = config.levels[i];
			found = true;
			break;
		}
	}

	if (found == false)
	{
		cout << "No level found with id: " + ofToString(id) << endl;
	}


	cannon = Cannon(level.shots);
	cannon.setPosition(ofPoint(100, -3, 215));

	for (size_t i = 0; i < level.ships.size(); i++)
	{
		Ship ship = Ship();
		ship.setPosition(ofPoint(level.ships[i].x, level.ships[i].y - 2, level.ships[i].z));
		ship.setVelocity(ofPoint(level.ships[i].vx, 0, level.ships[i].vz));
		ship.setModelType(level.ships[i].type);
		ships.push_back(ship);		
	}
	
}


#pragma endregion;



// helpers update
#pragma region helpers_setup


void ofApp::updateGameStatus()
{
	if (game_status == "START")
	{
		return;
	}
	

	// winning check
	if (ships.size() == 0)
	{
		if (game_status != "LEVELWIN" && game_status != "GAMEWIN")
		{
			sound_win.setVolume(0.03);
			sound_win.play();
		}
		game_status = "LEVELWIN";


		if (current_level + 1 > config.levels.size())
		{
			game_status = "GAMEWIN";
			camera_selected = 4;
		}
	}

	// losing check
	if (cannon.getShots() == 0 && cannon.bullets.size() == 0 && ships.size() > 0)
	{
		if (game_status != "LOSE")
		{
			sound_lose.play();
		}
		game_status = "LOSE";
	}

	
}


#pragma endregion;



// helpers draw
#pragma region helpers_draw


void ofApp::drawIndicators() {

	// shoots indicator
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


	// speed indicator
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


	// angle indicator
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
		verdana30.drawString("Pirates defeat you!\nYou have no more shoots!", 20, 50);

		skull_image.draw(200, 100, 200, 200);

		verdana14.drawString("press ENTER key to restart game", 20, 350);
		verdana14.drawString("press q key to quit game", 20, 370);

	ofPopMatrix();

	// ##TEST
	//cout << verdana30.stringWidth("ciao") << endl;
	
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
		verdana30.drawString("Congratulations! You win the game!\nNo more pirates in the sea!", 20, 50);

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
		verdana14.drawString("k/l :                  save/load game", 20, 280);

	ofPopMatrix();
	
}


#pragma endregion;



// openframeworks functions
#pragma region of_functions


//--------------------------------------------------------------
void ofApp::setup() {

	
	// loadings
	loadConfig();
	loadSounds();
	loadModels();
	loadFonts();
	loadImages();

	cout << "app name: " << config.appname << endl;
	cout << "version: " << config.version << endl;
	

	// play background sounds in loop
	sound_background.setLoop(true);
	sound_background.setVolume(0.07);
	sound_background.play();

	sound_background2.setLoop(true);
	sound_background2.setVolume(0.5);
	sound_background2.play();


	// lights
	configureLights();
	// cameras
	configureCameras();
	
	// game elements

    // set sea limits on Ship class static field
	Ship::setSeaLimits(ofPoint(0, 0, 20), ofPoint(200, 0, 180));
    
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


	// sounds update 
	ofSoundUpdate();


	// update game status
	updateGameStatus();
	

	// shoot indicator update
	if (shoot_key_pressed == true) {
		float time = ofGetElapsedTimef();
		float dt = time - shoot_press_start_time;
		bullet_speed_perc = ofMap(dt, 0, 1, 0, 100, true);
	}

	// cannon update
	if (left_key_pressed == true)
	{
		cannon.moveLeft();
	}
	if (right_key_pressed == true)
	{
		cannon.moveRight();
	}
	if (up_key_pressed == true)
	{
		cannon.rotateUp();
	}
	if (down_key_pressed == true)
	{
		cannon.rotateDown();
	}
	
	cannon.update();
	camera2.setPosition(cannon.getPosition() + ofPoint(5, 10, 10));
	camera4.setPosition(cannon.getPosition() + ofPoint(5, 5, -40));
	camera4.setTarget(cannon.getPosition() + ofPoint(5, 5, 20));

	
	// ship update
	for (size_t i = 0; i < ships.size(); i++)
	{
		ships[i].update();
	}
	

	// bullets update
	for (size_t j = 0; j < cannon.bullets.size(); j++)
	{
		cannon.bullets[j].update();

		ofPoint bullet_position = cannon.bullets[j].getPosition();

		if (bullet_position.y <= 0)
		{

			if (bullet_position.z >= 40)
			{
				ofPoint animation_point = bullet_position + ofPoint(0, -3, 0);
				WaterHoleAnimation animation = WaterHoleAnimation(animation_point);
				animationEmitter.addWaterHoleAnimation(animation);
				sound_splash.play();
			}
			else {
				ofPoint animation_point = bullet_position;
				ExplosionAnimation animation = ExplosionAnimation(animation_point);
				animationEmitter.addExplosionAnimation(animation);
				sound_explode.setVolume(0.05);
				sound_explode.play();
			}

			cannon.bullets.erase(cannon.bullets.begin() + j);

			break;
		}
		

		if ( world.isPointInsideWorld(cannon.bullets[j].getPosition()) == false )
		{
			cannon.bullets.erase(cannon.bullets.begin() + j);
			break;
		}

	}

	
	// check collisions between ships and bullets
	for (size_t i = 0; i < ships.size(); i++)
	{
		for (size_t j = 0; j < cannon.bullets.size(); j++)
		{
			if (ships[i].isPointInShip(cannon.bullets[j].getPosition()))
			{	
				ofPoint animation_point = ships[i].getPosition() + ofPoint(0, -3, 0) + ofPoint(10.5, 0, -5);
				ExplosionAnimation animation = ExplosionAnimation(animation_point);
				animationEmitter.addExplosionAnimation(animation);
				
				sound_explode.setVolume(0.05);
				sound_explode.play();

				ships.erase(ships.begin() + i);
				cannon.bullets.erase(cannon.bullets.begin() + j);

				break;

			}
		}
	}


	// update animations
	animationEmitter.update();
	
}


//--------------------------------------------------------------
void ofApp::draw() {
	
	
	ofEnableDepthTest();
	ofEnableAlphaBlending();
	ofSeedRandom(0);

	
	// light
	light_directional.enable();
	light_directional.draw();
	light_ambient.enable();
	light_ambient.draw();



	// world
	cameras[camera_selected]->begin();

		// ##DEBUG
		// draw cartesian axis and grid
		//ofDrawAxis(100);
		//ofDrawGrid(10, 28, false, false, true, false);
		
		// draw world
		world.draw();

		// draw animations
		animationEmitter.draw();

		// draw ships
		for (size_t i = 0; i < ships.size(); i++)
		{
			ships[i].draw();
		}

		// draw cannon
		cannon.draw();

	cameras[camera_selected]->end();
	
	

	// ui game interface

	ofDisableDepthTest();
	
	// start check
	if (game_status == "START")
	{
		drawStartView();
	}
	// level win check
	if (game_status == "LEVELWIN")
	{
		drawLevelWinView();
	}
	// game win check
	if (game_status == "GAMEWIN")
	{
		drawGameWinView();
	}
	// lose check
	if (game_status == "LOSE")
	{
		drawGameOverView();
	}
	// play check
	if (game_status == "PLAY")
	{
		drawIndicators();
	}
	
	if (help_visible)
	{
		drawHelpView();
	}
	
}


#pragma endregion



// openframeworks events
#pragma region of_events


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	// cannon movements
	
	// 'left arrow' key press
	if (key == OF_KEY_LEFT)
	{
		left_key_pressed = true;
	}
	// 'right arrow' key press
	if (key == OF_KEY_RIGHT)
	{
		right_key_pressed = true;
	}
	// 'up arrow' key press
	if (key == OF_KEY_UP)
	{
		up_key_pressed = true;
	}
	// 'down arrow' key press
	if (key == OF_KEY_DOWN)
	{
		down_key_pressed = true;
	}
	
	// cannon shoot start press

	// 's' key press
	if (key == 's')
	{
		if (shoot_key_pressed == false)
		{
			shoot_press_start_time = ofGetElapsedTimef();
			shoot_key_pressed = true;
		}
	}


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

	/*cout << key << endl;*/

	// 'k' key release
	if (key == 'k')
	{
		saveGame();
	}
	// 'l' key release
	if (key == 'l')
	{
		loadGame();
	}
	
	// 'enter' key release
	if (key == OF_KEY_RETURN)
	{
		if (game_status == "PLAY")
		{
			return;
		}
		if (game_status == "LOSE")
		{
			current_level = 0;
		}
		current_level++;
		if (current_level <= config.levels.size())
		{
			game_status = "PLAY";
			setup_level(current_level);
			if (current_level == 1)
			{
				camera_selected = 1;
			}
		}
		if (current_level > config.levels.size())
		{
			current_level = 0;
			game_status = "START";
		}
	}

	// 'q' key release
	if (key == 'q')
	{
		ofExit();
	}

	// cannon controls

	// 'left arrow' key press
	if (key == OF_KEY_LEFT)
	{
		left_key_pressed = false;
	}
	// 'right arrow' key press
	if (key == OF_KEY_RIGHT)
	{
		right_key_pressed = false;
	}
	// 'up arrow' key press
	if (key == OF_KEY_UP)
	{
		up_key_pressed = false;
	}
	// 'down arrow' key press
	if (key == OF_KEY_DOWN)
	{
		down_key_pressed = false;
	}
	

	// 's' key release
	if (key == 's')
	{
		
		shoot_key_pressed = false;

		if (cannon.getShots() <= 0)
		{
			return;
		}
		
		float bullet_speed = ofMap(bullet_speed_perc, 0, 100, MIN_SHOOT_SPEED, MAX_SHOOT_SPEED, true);
		cannon.shoot(bullet_speed);
		sound_cannon.setVolume(0.05);
		sound_cannon.play();
		
	}




	// help toggle

	// 'h' key press
	if (key == 'h') {
		help_visible = !help_visible;
	}

	// camera selection

	// '1' key release
	if (key == '1') {
		camera_selected = 1;
	}
	// '2' key release
	if (key == '2') {
		camera_selected = 2;
	}
	// '3' key release
	if (key == '3') {
		camera_selected = 3;
	}
	// '4' key release
	if (key == '4') {
		camera_selected = 4;
	}
	// '9' key release
	if (key == '9') {
		camera_selected = 0;
	}


	
	// ##DEBUG
	// 'e' key release
	//if (key == 101)
	//{	
	//	ExplosionAnimation animation = ExplosionAnimation(ofPoint(100, 0, 100));
	//	animationEmitter.addExplosionAnimation(animation);
	//}
	//// 'w' key release
	//if (key == 119)
	//{
	//	animation_water_radius = 3;
	//	animation_water_point = ofPoint(100, 0, 100);
	//}
	// '1' key release
	//if (key == 49) {
	//	sound_cannon.setMultiPlay(true);
	//	sound_cannon.play();
	//}
	//// '2' key release
	//if (key == 50) {
	//	sound_splash.play();
	//}
	//// '3' key release
	//if (key == 51) {
	//	sound_explode.play();
	//}

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



