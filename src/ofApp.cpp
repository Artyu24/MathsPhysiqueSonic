#include "ofApp.h"
#include "include/Vector3.h"
#include "include/UnitTest.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//Launch Unit Test
	UnitTest unitTest;
	unitTest.LaunchTest();

	//Set Frame Rate
	ofSetFrameRate(30);
	ofSetVerticalSync(false);

	//Load canon
	m_canon.GetImage().load("Cannon.png");
	m_canon.SetPosition({ -75.f, ofGetWindowHeight() / 2.f, 0.f });
}

//--------------------------------------------------------------
void ofApp::update()
{
	for (auto& particule : m_particles) {
		Vector3f gravity(0, 9.8, 0);
		particule.ApplyForce(gravity);
		particule.Integrate(ofGetLastFrameTime());
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	m_canon.GetImage().draw(m_canon.GetPosition(), m_canon.GetImageWidth() * 0.3f, m_canon.GetImageHeight() * 0.3f);

	//ofSetColor(255, 0, 0);
	//ofFill();
	for (auto& particle : m_particles) {
		ofDrawCircle(particle.GetPosition(), particle.GetSize());
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 57357) // Up Arrow
	{
		m_canon.SetPosition(Vector3f(m_canon.GetPosition().x, m_canon.GetPosition().y - 10.f, 0.f));
	}
	else if (key == 57359) // Down Arrow
	{
		m_canon.SetPosition(Vector3f(m_canon.GetPosition().x, m_canon.GetPosition().y + 10.f, 0.f));
	}

	if (key == 'v') { 
		SpawnParticle(true); // Verlet 
	}
	if (key == 'e') {
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
	Vector3f pos(200.f, 200.f, 0.f);
	Vector3f vel(100.f, 0.f, 0.f); 

	float size =  20.f;
	float mass = 2.f;

	Particle particle(pos, vel, size, mass);
	particle.SetAcceleration({ 0,0,0 });
	Vector3f prevPos = pos;

	particle.Integrate(0.033f);

	particle.SetPrevPosition(prevPos);

	m_particles.push_back(particle);
}
