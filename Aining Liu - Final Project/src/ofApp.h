#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxAssimpModelLoader.h"

#include "utils.h"
#include "world.h"
#include "animationEmitter.h"
#include "cannon.h"
#include "Guardian.h"
#include "bullet.h"

struct ShipConfig {
	int type;
	int x,y,z;
	int vx,vz;
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
	float MIN_SHOOT_SPEED = 10;
	float MAX_SHOOT_SPEED = 90;
	ofFbo fbo;
	ofxXmlSettings gamestate;
	ofxXmlSettings settings;
	Config config;

	ofSoundPlayer sound_splash;
	ofSoundPlayer sound_explode;
	ofSoundPlayer sound_cannon;
	ofSoundPlayer sound_win;
	ofSoundPlayer sound_lose;
	ofSoundPlayer sound_background;
	ofSoundPlayer sound_background2;

	ofxAssimpModelLoader palmtree1Model;
	ofxAssimpModelLoader palmtree2Model;

	ofTrueTypeFont	verdana14;
	ofTrueTypeFont	verdana30;

	ofImage skull_image;
	ofImage wincup_image;
	ofImage cannon_image;
	ofImage galleon_image;
	
	ofLight light_directional;
	ofLight light_ambient;

	ofEasyCam camera0;
	ofEasyCam camera1;
	ofEasyCam camera2;
	ofEasyCam camera3;
	ofEasyCam camera4;

	vector<ofEasyCam*> cameras;
	int camera_selected = 1;
	
	World world;
	Cannon cannon;
	vector<Guardian> guard;
	Bullet bullet;
	AnimationEmitter animationEmitter;
	
	bool help_visible = false;
	bool shoot_key_pressed = false;
	bool left_key_pressed = false;
	bool right_key_pressed = false;
	bool up_key_pressed = false;
	bool down_key_pressed = false;
	float shoot_press_start_time = 0;
	float bullet_speed_perc = 0;
	
	bool game_started = false;
	string game_status = "START";
	int current_level = 0;

public:
	void loadConfig();
	void loadSounds();
	void loadModels();
	void loadFonts();
	void loadImages();
	
	void configureLights();
	void configureCameras();
	
	void setup_level(int level);
	void updateGameStatus();

	void drawIndicators();
	void drawStartView();
	void drawGameOverView();
	void drawLevelWinView();
	void drawGameWinView();
	void drawHelpView();

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
