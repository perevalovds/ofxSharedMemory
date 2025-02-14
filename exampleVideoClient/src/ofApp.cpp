#include "ofApp.h"


/*
 Sets up a 1280x720 rgb video/camera input image as a memory mapped file.
 - Can be a server (creates/destroys the video) or client (reads the video).
 - A memory key string "MyVideo" is used to identify the shared memory (you can name change this to whatever you want).
 - The source code is identical for exampleVideoClient and exampleVideoServer, except for the variable below 'isServer'
 */


bool isServer = false;
int videoWidth = 1280;
int videoHeight = 720;
int memorySize = videoWidth * videoHeight * 3;
string memoryKey = "MyVideo";


//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofEnableAlphaBlending();
	ofSetLogLevel(OF_LOG_VERBOSE);

	if (isServer) {
		video.load("video-ofxShadertoy.mp4");
	}

	texture.allocate(videoWidth, videoHeight, GL_RGB);

	// setup + connect
	memoryMappedFile.setup(memoryKey, memorySize, isServer);
	isConnected = memoryMappedFile.connect();

	ofLog() << "Memory was mapped? " << isConnected;
	ofLog() << "Memory key: " << memoryKey;
	ofLog() << "Memory size: " << memorySize;
}



//--------------------------------------------------------------
void ofApp::update() {

	ofSetWindowTitle(ofToString(isServer ? "Server connected: " : "Client connected: ") + ofToString(isConnected ? "YES" : "NO") + ", FPS: " + ofToString(ofGetFrameRate()));

	// if not connected, try reconnect every 5 seconds or so
	if (!isConnected && ofGetFrameNum() % 300 == 0) {
		isConnected = memoryMappedFile.connect();
	}

	// server updates video and saves to memory mapped file
	// client loads memory mapped file into texture
	if (isServer) {

		video.update();
		if (video.isFrameNew()) {

			// copy pixel data from video into the memory mapped file buffer
			if (isConnected) memoryMappedFile.setData(video.getPixels().getPixels());

			// not required for server, but loading the memory mapped file data back into a texture for sanity check
			//texture.loadData(memoryMappedFile.getData(), videoWidth, videoHeight, GL_RGB);

			texture.loadData(video.getPixels().getPixels(), videoWidth, videoHeight, GL_RGB);
		}
	}
	else {

		if (isConnected) {
			texture.loadData(memoryMappedFile.getData(), videoWidth, videoHeight, GL_RGB);
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	// server is blue, client is yellow
	(isServer) ? ofBackground(0, 255, 255) : ofBackground(255, 255, 0);

	ofSetColor(255);
	texture.draw(0, 0);
	ofSetColor(0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
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