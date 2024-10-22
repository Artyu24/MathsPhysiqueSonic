#include "ofApp.h"
#include "include/Vector3.h"
#include "include/UnitTest.h"
#include "include/ParticleGravity.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//Launch Unit Test
	UnitTest unitTest;
	unitTest.LaunchTest();

	//Set Frame Rate
	ofSetFrameRate(60);
	ofSetVerticalSync(false);

	//Set background in black
	ofBackground(0, 0, 0);

	//Create World class and Launch game
	m_world = World();
	m_world.LaunchGame();
}

//--------------------------------------------------------------
void ofApp::update()
{
	m_world.UpdatePhysics(ofGetLastFrameTime() * 10.f);
	m_world.ApplyCollisions();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	//Draw Information
	ofDrawBitmapString("Delta Time : " + ofToString(ofGetLastFrameTime()), ofGetWidth() - 200.f, 30.f);
	ofSetColor(255, 120, 120);

	m_world.Draw();

	ofSetColor(255, 255, 255);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	//Divide Blob in the game
	if (key == ' ')
		m_world.SpacePressed();

	if (key == 57356) // Left Arrow
	{
		m_world.Movement({-50.f,0.f,0.f});
	}
	else if (key == 57358) // Right Arrow
	{
		m_world.Movement({ 50.f,0.f,0.f });
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}