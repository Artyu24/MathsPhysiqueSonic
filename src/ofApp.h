#pragma once

#include "ofMain.h"

#include "include/Object.h"
#include "include/Particle.h"
#include "include/ParticleData.h"
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
	void SpawnParticleInWorld();

	Object m_canon;

	bool m_isIntegrateEulerMode = true;
	//Different Particle Data for the Game
	std::array<ParticleData, 4> m_particlesData = {
		ParticleData(Vector3f(50.f,-50.f,0.f), 1.f),
		ParticleData(Vector3f(40.f,-20.f,0.f), 2.f ),
		ParticleData(Vector3f(20.f,-30.f,0.f), 8.f ),
		ParticleData(Vector3f(30.f,-10.f,0.f), 20.f)
	};
	size_t m_particleDataIndex = 0;
};
