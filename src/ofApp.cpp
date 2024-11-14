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

	gui.setup();

	ofxGuiSetTextColor(ofColor::white);	


	gui.add(planeSizeField.setup("Plane Size", 1920, 1, 3840));
	gui.add(speedSlider.setup("Launch Speed", 25.f, 10.0f, 100.0f));

	gui.add(yawSlider.setup("Yaw", yaw, -180.0f, 180.0f));
	gui.add(pitchSlider.setup("Pitch", pitch, -90.0f, 90.0f));

	yaw = 0.0f;
	pitch = 0.0f;

	rb = make_shared<RigidBody>(100, Vector3f(0.f,0.f,0.f));

	///dimensions for width and height in pixels
	plane.setPosition(0, -300, 0); /// position in x y z
	plane.setOrientation({ 90,0,0 });
	plane.setResolution(8, 8);

	canon.setPosition(0, 0, 0);
	cannonDirection = glm::vec3(1, 0, 0);

	

	//Launch Unit Test
	UnitTest unitTest;
	unitTest.LaunchTest();

	//Set Frame Rate
	ofSetFrameRate(60);
	//ofSetVerticalSync(false);

	//Set background in black
	ofBackground(25);

	//Create World class and Launch game
	m_world = World();
	m_world.LaunchGame();

	

	
}

//--------------------------------------------------------------
void ofApp::update()
{
	m_world.UpdatePhysics(ofGetLastFrameTime() * 10.f);
	//m_world.ApplyCollisions();
	//m_world.ApplyGroundCollisions();

	rb->ApplyForce(World::GetGravity() * rb->GetMass());
	rb->UpdateState(ofGetLastFrameTime() * 10.f);


	float yawRad = glm::radians(yaw);
	float pitchRad = glm::radians(pitch);

	yaw = yawSlider;
	pitch = pitchSlider;

	cannonDirection = glm::vec3(
		cos(pitchRad) * cos(yawRad),
		sin(pitchRad),
		cos(pitchRad) * sin(yawRad)
	);

	
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofEnableDepthTest();

	//Draw Information
	ofDrawBitmapString("Delta Time : " + ofToString(ofGetLastFrameTime()), ofGetWidth() - 220.f, 30.f);
	ofSetColor(255, 120, 120);

	
	ofSetColor(255, 255, 255);
	camera.begin();

	

	// Dessin des projectiles
	for (const auto& projectile : projectiles) {
		if (projectile->GetPosition().y > -300) {

			m_world.Draw();
		}
	}

	ofSetColor(100.f);
	plane.set(planeSizeField, planeSizeField);
	plane.draw();

	{
		ofPushMatrix();
		ofTranslate(0,0,0);
		ofRotateYDeg(yaw);
		ofRotateXDeg(-pitch);
		ofSetColor(255);
		canon.set(20);
		canon.draw();
		ofPopMatrix();

		
	}

	camera.end();

	ofDisableDepthTest();
	gui.draw();
	

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	////Divide Blob in the game
	//if (key == ' ')
	//	m_world.SpacePressed();


	//if (key == 57356) // Left Arrow
	//{
	//	m_world.Movement({-25.f,0.f,0.f});
	//}
	//if (key == 57358) // Right Arrow
	//{
	//	m_world.Movement({ 25.f,0.f,0.f });
	//}

	//if (key == 57357)
	//{
	//	m_world.Movement({ 0.f,-100.f,0.f });
	//}

	if (key == 'a')
	{
		float speed = speedSlider;
		
		Vector3f velocity = cannonDirection * speed;

		auto newProjectile = m_world.SpawnParticle({velocity, 1000.f}, cannonDirection);
		

		projectiles.push_back(newProjectile);
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