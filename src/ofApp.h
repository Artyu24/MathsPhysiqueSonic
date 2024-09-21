#pragma once

#include "ofMain.h"

#include "include/Object.h"
#include "include/Particle.h"

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
	Object m_canon;

	std::vector<Particle> m_particles;
	void SpawnParticle();

	bool m_isIntegrateEulerMode = true;

	//Temporary structure, just for the game and create different projectile
	struct ParticleData
	{
		ParticleData(Vector3f vel, float mass) : initialVelocity(vel), mass(mass) {}
		Vector3f initialVelocity;
		float mass;
	};
	std::array<ParticleData, 4> m_particlesData = {
		ParticleData(Vector3f(100.f,0.f,0.f), 50.f),
		ParticleData(Vector3f(450.f,0.f,0.f), 20.f ),
		ParticleData(Vector3f(200.f,0.f,0.f), 80.f ),
		ParticleData(Vector3f(500.f,0.f,0.f), 200.f)
	};
	size_t m_particleDataIndex = 0;
};
