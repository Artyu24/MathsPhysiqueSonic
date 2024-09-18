#include "ofApp.h"
#include "include/Vector3.h"
#include "include/UnitTest.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	UnitTest unitTest;
	unitTest.LaunchTest();

	ofSetFrameRate(30);
	ofSetVerticalSync(false);

	cannon.load("Cannon.png");
	cannonPos = { -75, (ofGetWindowHeight() / 2), 0 };

	m_particles.push_back(Particle({ 200.f, 200.f,0.f }, { 50.f, 0.f,0.f }, 100.f, 50.f));
}

//--------------------------------------------------------------
void ofApp::update()
{
	
	//std::cout << ofGetLastFrameTime() << std::endl;
	for (auto& particule : m_particles) {
		Vector3<float> gravity(0, 9.8, 0);
		particule.applyForce(gravity);
		particule.integrateurEuler(ofGetLastFrameTime());
	}
	
}

//--------------------------------------------------------------
void ofApp::draw()
{
	for (size_t i = 0; i < m_particles.size(); i++)
	{
		ofDrawCircle(m_particles[i].GetPosition(), 20);
	}

	//cannon.draw(cannonPos, cannon.getWidth() * 0.3f, cannon.getHeight() * 0.3f);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 57357) // Up Arrow
	{
		cannonPos.y -= 10.0f;
	}
	else if (key == 57359) // Down Arrow
	{
		cannonPos.y += 10.0f;
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
