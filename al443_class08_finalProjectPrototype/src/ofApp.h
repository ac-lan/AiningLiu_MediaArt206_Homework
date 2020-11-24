#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxGui.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
  
		void exit();
		void createContourEdge(ofPolyline p);

	 ofxPanel gui;
	ofxButton uiLearn;
	ofxButton uiClearCircles;
	 ofxButton uiClearContourEdge;
	 ofxIntSlider uiThreshold;

	ofVideoGrabber kinect;

	ofxCvColorImage color;
	ofxCvGrayscaleImage gs,bg,diff;
	ofxCvContourFinder contour;
  
	 ofxBox2d box2d;
	vector <shared_ptr<ofxBox2dCircle>> circles;
	 ofxBox2dEdge *contourEdge;
		
};









