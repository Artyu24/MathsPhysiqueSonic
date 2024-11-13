#include "ofApp.h"
#include "include/Vector3.h"
#include "include/UnitTest.h"
#include "include/ParticleGravity.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofEnableDepthTest();
	ofSetVerticalSync(true);

	camera.setDistance(160);

	//Launch Unit Test
	UnitTest unitTest;
	unitTest.LaunchTest();

	//Set Frame Rate
	ofSetFrameRate(60);
	ofSetVerticalSync(false);

	//Set background in black
	ofBackground(25);

	//Create World class and Launch game
	m_world = World();
	m_world.LaunchGame();

	plane.set(1920, 1920);   ///dimensions for width and height in pixels
	plane.setPosition(0, -200, 0); /// position in x y z
	plane.setOrientation({ 90,0,0 });
	plane.setResolution(8, 8);

	
}

//--------------------------------------------------------------
void ofApp::update()
{
	m_world.UpdatePhysics(ofGetLastFrameTime() * 10.f);
	m_world.ApplyCollisions();
	m_world.ApplyGroundCollisions();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	camera.begin();
	//Draw Information
	ofDrawBitmapString("Delta Time : " + ofToString(ofGetLastFrameTime()), ofGetWidth() - 220.f, 30.f);
	ofSetColor(255, 120, 120);

	m_world.Draw();

	ofSetColor(255, 255, 255);

	ofNoFill();
	ofDrawBox(30.f);

	ofSetColor(255.f, 0., 0.);
	ofDrawSphere(5.f);

	ofSetColor(100.f);
	plane.draw();

	camera.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	//Divide Blob in the game
	if (key == ' ')
		m_world.SpacePressed();


	if (key == 57356) // Left Arrow
	{
		m_world.Movement({-25.f,0.f,0.f});
	}
	if (key == 57358) // Right Arrow
	{
		m_world.Movement({ 25.f,0.f,0.f });
	}

	if (key == 57357)
	{
		m_world.Movement({ 0.f,-100.f,0.f });
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

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