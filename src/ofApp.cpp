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
	ofSetFrameRate(30);
	ofSetVerticalSync(false);

	//Set background in black
	ofBackground(0, 0, 0);

	//Load canon
	m_canon.GetImage().load("Cannon.png");
	m_canon.SetPosition({ -75.f, ofGetWindowHeight() / 2.f, 0.f });

	m_world = World();
}

//--------------------------------------------------------------
void ofApp::update()
{
	m_world.UpdatePhysics(ofGetLastFrameTime() * 10.f);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	//Draw Canon
	m_canon.GetImage().draw(m_canon.GetPosition(), m_canon.GetImageWidth() * 0.3f, m_canon.GetImageHeight() * 0.3f);

	//Draw Information
	ofDrawBitmapString("Delta Time : " + ofToString(ofGetLastFrameTime()), ofGetWidth() - 200.f, 30.f);
	ofDrawBitmapString("Initial Velocity : " + ofToString(m_particlesData[m_particleDataIndex].initialVelocity.ToString()), ofGetWidth() - 300.f, 60.f);
	ofDrawBitmapString("Mass : " + ofToString(m_particlesData[m_particleDataIndex].mass), ofGetWidth() - 100.f, 90.f);
	if(m_isIntegrateEulerMode)
	{
		ofSetColor(255, 120, 120);
		ofDrawBitmapString("Euler Mode", ofGetWidth() - 100.f, 120.f);
	}
	else
	{
		ofSetColor(120, 219, 255);
		ofDrawBitmapString("Verlet Mode", ofGetWidth() - 100.f, 120.f);
	}

	m_world.Draw();

	ofSetColor(255, 255, 255);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	//Move Canon
	if (key == 'z' || key == 'w' || key == 57357) // Up Arrow
		m_canon.SetPosition(Vector3f(m_canon.GetPosition().x, m_canon.GetPosition().y - 10.f, 0.f));
	else if (key == 's' || key == 57359) // Down Arrow
		m_canon.SetPosition(Vector3f(m_canon.GetPosition().x, m_canon.GetPosition().y + 10.f, 0.f));

	//Switch between different projectile
	if (key == '+') 
	{
		m_particleDataIndex++;
		if (m_particleDataIndex >= m_particlesData.size())
			m_particleDataIndex = 0;
	}
	if (key == '-') {
		if (m_particleDataIndex == 0)
			m_particleDataIndex = m_particlesData.size() - 1;
		else
			m_particleDataIndex--;
	}

	//Spawn Projectile
	if (key == ' ')
		SpawnParticleInWorld();

	//Switch between Euler or Verlet Integrate
	if (key == 'e') //For Euler
		m_isIntegrateEulerMode = true;
	else if (key == 'v') //For Verlet
		m_isIntegrateEulerMode = false;
}

void ofApp::SpawnParticleInWorld()
{
	m_world.SpawnParticle(m_particlesData[m_particleDataIndex], m_canon.GetPosition() + Vector3f(200.f, 50.f, 0.f), m_isIntegrateEulerMode);
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