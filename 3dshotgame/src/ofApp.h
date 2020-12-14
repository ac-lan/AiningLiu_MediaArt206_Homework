
/*

#######################################################################################


Laboratorio di Programmazione per Sistemi Multimediali Interattivi
Final exam project

Student: Michele Castenetto
Title: 3d Cannon Shot Game

#######################################################################################

# Description:

This project is build around the idea of a simple game: the player must destroy all the ships with a cannon.
If the cannon has no more shots the player lose.

# Game keys:

left/right arrows: move cannon left-right
up/down arrows: rotate the shot angle up/down
s: shoot
h: help
q: quit
enter: start game
1,2,3,4,9: change camera view
k/l: save/load game


# Open task and potentials developments:

- compute ship mesh bounding boxes 
- enemy ships shoot on the player
- textures and materials for better sand and grass
- use of fbo for better performance

*/


#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxAssimpModelLoader.h"


#include "utils.h"


#include "world.h"
#include "animationEmitter.h"
#include "cannon.h"
#include "ship.h"
#include "bullet.h"




// oggetti per la configurazione
struct ShipConfig {
	int type;
	int x;
	int y;
	int z;
	int vx;
	int vz;
};

struct Level {
	int id;
	int shots;
	vector<ShipConfig> ships;
};

struct Config {
	string appname;
	string version;
	vector<Level> levels;
};





class ofApp : public ofBaseApp {

private:

	// constants 

	float MIN_SHOOT_SPEED = 10;
	float MAX_SHOOT_SPEED = 90;


	// fbo
	ofFbo fbo;

	
	// save load
	ofxXmlSettings gamestate;

	// config

	ofxXmlSettings settings;
	Config config;

	// sounds

	ofSoundPlayer sound_splash;
	ofSoundPlayer sound_explode;
	ofSoundPlayer sound_cannon;
	ofSoundPlayer sound_win;
	ofSoundPlayer sound_lose;
	ofSoundPlayer sound_background;
	ofSoundPlayer sound_background2;


	

	// 3dmodels
	
	ofxAssimpModelLoader palmtree1Model;
	ofxAssimpModelLoader palmtree2Model;
	
	// fonts

	ofTrueTypeFont	verdana14;
	ofTrueTypeFont	verdana30;

	// images

	//ofImage grass_texture;
	ofImage skull_image;
	ofImage wincup_image;
	ofImage cannon_image;
	ofImage galleon_image;
	
	
	// lights
	
	ofLight light_directional;
	ofLight light_ambient;

	// cameras
	
	ofEasyCam camera0;
	ofEasyCam camera1;
	ofEasyCam camera2;
	ofEasyCam camera3;
	ofEasyCam camera4;

	vector<ofEasyCam*> cameras;
	int camera_selected = 1;
	
	// game elements

	World world;
	Cannon cannon;
	vector<Ship> ships;
	Bullet bullet;
	AnimationEmitter animationEmitter;
	
	// ui interface
	
	bool help_visible = false;
	
	bool shoot_key_pressed = false;
	bool left_key_pressed = false;
	bool right_key_pressed = false;
	bool up_key_pressed = false;
	bool down_key_pressed = false;


	float shoot_press_start_time = 0;
	float bullet_speed_perc = 0;
	
	// game

	bool game_started = false;
	// START, LEVELWIN, GAMEWIN, LOSE, PLAY
	string game_status = "START";
	int current_level = 0;



public:

	// setup helpers

	void saveGame();
	void loadGame();

	void loadConfig();
	void loadSounds();
	void loadModels();
	void loadFonts();
	void loadImages();
	
	void configureLights();
	void configureCameras();
	
	void setup_level(int level);

	// update helpers

	void updateGameStatus();

	// draw helpers
	
	void drawIndicators();
	void drawStartView();
	void drawGameOverView();
	void drawLevelWinView();
	void drawGameWinView();
	void drawHelpView();


	// openframeworks functions

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

};
