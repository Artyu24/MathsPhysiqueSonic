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
	//ofSetVerticalSync(false);

	//Set background in black
	ofBackground(25);

	//Create World class and Setup
	m_world = std::make_unique<World>();
	m_world->Setup();
}

//--------------------------------------------------------------
void ofApp::update()
{
	m_world->UpdatePhysics(ofGetLastFrameTime() * 10.f);
	m_world->UpdateGame();
	//m_world->ApplyCollisions();
	//m_world->ApplyGroundCollisions();


}

//--------------------------------------------------------------
void ofApp::draw()
{
	
	m_world->Draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	
	if (key == ' ')
	{
		m_world->SpacePressed();
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