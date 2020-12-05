#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofBackground(30, 30, 30);

	franklin.load("frabk.ttf", 12);

	gui.setup("Image Processing", "settings.xml", 5, 5);
	gui.add(blur.setup("Blur", IMG_X_OFFSET, 1, 25));
	gui.add(gaussianBlur.setup("Gaussian Blur", IMG_X_OFFSET, 1, 25));
	gui.add(helpText.setup("press d ,w, n,m,e,s,v"," for different functions\n ", 200));

	blur.addListener(this, &ofApp::blurChanged);
	gaussianBlur.addListener(this, &ofApp::gaussianBlurChanged);

	imageLoaded = false;

	image.load("lowerKachura.jpg");
	width = ofGetWidth() - 320;
	height = (float)(width) / (float)(image.getWidth()) * image.getHeight();
	image.resize(width, height);
	imageLoaded = true;

	//cout << width << " " << height;
	canvas.allocate(width, height + CAPTION_OFFSET, GL_RGBA, 4);
	canvas.begin();
	ofClear(30, 30, 30, 255);
	canvas.end();

	cvColorImage.setFromPixels(image.getPixels());

	red.allocate(width, height);
	green.allocate(width, height);
	blue.allocate(width, height);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	//ofDrawBitmapString("\n Press ", 10, 20);
	if (displayBlurImage)
		cvColorImage.draw(IMG_X_OFFSET, 0);
	else
		switch (pressedKey) {

		case 'd':
			ofClear(30, 30, 30, 255);
			image.draw(IMG_X_OFFSET, 0);
			cvColorImage.setFromPixels(image.getPixels());
			franklin.drawString("Basic Image", IMG_X_OFFSET, height + CAPTION_OFFSET);
			break;

		case 'w':
			ofClear(30, 30, 30, 255);
			cvColorImage.setFromPixels(image.getPixels());
			grayImage.setFromColorImage(cvColorImage);
			grayImage.draw(IMG_X_OFFSET, 0);
			franklin.drawString("Grayscale Image", IMG_X_OFFSET, height + CAPTION_OFFSET);
			break;

		case 'n':
			ofClear(30, 30, 30, 255);
			cvColorImage.setFromPixels(image.getPixels());
			cvColorImage.invert();
			cvColorImage.draw(IMG_X_OFFSET, 0);
			franklin.drawString("Negative Image", IMG_X_OFFSET, height + CAPTION_OFFSET);
			break;

		case 'm':
			ofClear(30, 30, 30, 255);
			cvColorImage.setFromPixels(image.getPixels());
			cvColorImage.mirror(FALSE, TRUE);
			cvColorImage.draw(IMG_X_OFFSET, 0);
			franklin.drawString("Mirror Image", IMG_X_OFFSET, height + CAPTION_OFFSET);
			break;

		case 'e': {
			ofClear(30, 30, 30, 255);
			cvColorImage.setFromPixels(image.getPixels());
			cannyImage.setFromColorImage(cvColorImage);
			grayImage.setFromColorImage(cvColorImage);

			int minVal = 60;
			int maxVal = 150;
			cvCanny(grayImage.getCvImage(), cannyImage.getCvImage(), minVal, maxVal, 3);
			cannyImage.flagImageChanged();
			cannyImage.draw(IMG_X_OFFSET, 0);
			franklin.drawString("Edge Detection", IMG_X_OFFSET, height + CAPTION_OFFSET);
		}
				  break;

		case 's':
			ofClear(30, 30, 30, 255);
			cvColorImage.setFromPixels(image.getPixels());
			cvColorImage.convertRgbToHsv();
			cvColorImage.convertToGrayscalePlanarImages(red, green, blue);
			green.draw(IMG_X_OFFSET, 0);
			franklin.drawString("Saturation", IMG_X_OFFSET, height + CAPTION_OFFSET);
			break;

		case 'v':

			ofClear(30, 30, 30, 255);
			cvColorImage.setFromPixels(image.getPixels());
			cvColorImage.convertRgbToHsv();
			cvColorImage.convertToGrayscalePlanarImages(red, green, blue);
			blue.draw(IMG_X_OFFSET, 0);
			franklin.drawString("Brightness", IMG_X_OFFSET, height + CAPTION_OFFSET);

			break;

		default:
			//cout << "key not supported" << endl;
			break;

		}
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::blurChanged(int & blur) {

	if (imageLoaded) {
		cvColorImage.setFromPixels(image.getPixels());
		cvColorImage.blur(blur);
	}
	displayBlurImage = true;
}

//--------------------------------------------------------------
void ofApp::gaussianBlurChanged(int & gaussianBlur) {

	if (imageLoaded) {
		cvColorImage.setFromPixels(image.getPixels());
		cvColorImage.blurGaussian(gaussianBlur);
	}
	displayBlurImage = true;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	displayBlurImage = false;
	pressedKey = key;
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

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
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

//--------------------------------------------------------------
void ofApp::exit() {
	blur.removeListener(this, &ofApp::blurChanged);
	gaussianBlur.removeListener(this, &ofApp::gaussianBlurChanged);
}