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

	m_world = World();
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
	if(m_isIntegrateEulerMode)
	{
		ofSetColor(255, 120, 120);
		ofDrawBitmapString("Euler Mode", ofGetWidth() - 100.f, 120.f);
	}
	/*else
	{
		ofSetColor(120, 219, 255);
		ofDrawBitmapString("Verlet Mode", ofGetWidth() - 100.f, 120.f);
	}*/

	m_world.Draw();

	ofSetColor(255, 255, 255);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	//Spawn Projectile
	if (key == ' ')
		SpawnParticleInWorld();

	////Switch between Euler or Verlet Integrate
	//if (key == 'e') //For Euler
	//	m_isIntegrateEulerMode = true;
	//else if (key == 'v') //For Verlet
	//	m_isIntegrateEulerMode = false;
}

void ofApp::SpawnParticleInWorld()
{
	m_world.SpawnBlob();
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