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
	
}

//--------------------------------------------------------------
void ofApp::update()
{
	
	//std::cout << ofGetLastFrameTime() << std::endl;
	for (auto& particule : m_particlesVerlet) {
		Vector3<float> gravity(0, 9.8, 0);
		particule.applyForce(gravity);
		particule.integrateurVerlet(ofGetLastFrameTime());
	}
	for (auto& particule : m_particlesEuler) {
		Vector3<float> gravity(0, 9.8, 0);
		particule.applyForce(gravity);
		particule.integrateurEuler(ofGetLastFrameTime());
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofSetColor(255, 0, 0);
	ofFill();
	for (auto& particle : m_particlesVerlet) {
		ofDrawCircle(particle.GetPosition(), particle.GetSize());
	}
	ofSetColor(0, 255, 0);
	ofFill();
	for (auto& particle : m_particlesEuler) {
		ofDrawCircle(particle.GetPosition(), particle.GetSize());
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
	if (key == 'p') { 
		SpawnParticle(true); // Verlet 
	}
	if (key == 'o') {
		SpawnParticle(false); // Euler
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

void ofApp::SpawnParticle(bool Verlet) {
	Vector3<float> pos(200.f, 200.f, 0.f);
	Vector3<float> vel(100.f, 0.f, 0.f); 

	float size =  20.f;
	float mass = 2.f;

	Particle particle(pos, vel, size, mass);
	particle.SetAcceleration({ 0,0,0 });
	vel *= ofGetLastFrameTime();
	particle.SetPrevPosition(pos - vel);

	if (Verlet) {
		m_particlesVerlet.push_back(particle);
	}
	else {
		m_particlesEuler.push_back(particle);
	}
}
