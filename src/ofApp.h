#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "include/Object.h"
#include "include/Particle.h"
#include "include/ParticleData.h"
#include "include/RigidBody.h"

#include "include/World.h"


class ofApp : public ofBaseApp
{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);


private:
	World m_world;
	ofEasyCam camera;

	ofPlanePrimitive plane;

	ofBoxPrimitive canon;
	glm::vec3 cannonDirection;

	ofxPanel gui;


	ofxIntField planeSizeField;

	ofxFloatSlider speedSlider;
	ofxFloatSlider yawSlider;
	ofxFloatSlider pitchSlider;

	float yaw;   
	float pitch; 
	
	std::vector<shared_ptr<RigidBody>> projectiles; // Liste des projectiles

	shared_ptr<RigidBody> rb;

};
