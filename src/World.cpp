#include "include/World.h"

#include "include/ParticleGravity.h"
#include "include/ParticleFrictionCinetique.h"
#include "include/ParticleFrictionStatic.h"
#include "include/ParticleSpring.h"
#include "include/ParticleSpringFixedPoint.h"
#include "include/SphereCollider.h"

World::World() :
m_particles(),
m_forceRegistry(std::make_unique<ParticleForceRegistry>()) //Create Force Registry
{
	cannonDirection = Vector3f(1.f,0.f,0.f);
	yaw = 0.0f;
	pitch = 0.0f;

}

void World::Setup()
{
	ofEnableDepthTest();
	ofSetVerticalSync(true);

	camera.setDistance(160);

	gui.setup();

	ofxGuiSetTextColor(ofColor::white);


	gui.add(planeSizeField.setup("Plane Size", 1920, 1, 3840));
	gui.add(speedSlider.setup("Launch Speed", 25.f, 10.0f, 100.0f));

	gui.add(yawSlider.setup("Canon Yaw", yaw, -180.0f, 180.0f));
	gui.add(pitchSlider.setup("Canon Pitch", pitch, -90.0f, 90.0f));

	gui.add(massField.setup("Projectile Mass", 100.f, 1.0f, 100000.f));

	gui.add(xTorqueField.setup("X Torque", 0.f, -1000.0f, 1000.f));
	gui.add(yTorqueField.setup("Y Torque", 0.f, -1000.0f, 1000.f));
	gui.add(zTorqueField.setup("Z Torque", -100.f, -1000.0f, 1000.f));



	///dimensions for width and height in pixels
	plane.setPosition(0, -300, 0); /// position in x y z
	plane.setOrientation({ 90,0,0 });
	plane.setResolution(8, 8);

	canon.setPosition(0, 0, 0);
}

void World::UpdateGame()
{
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

void World::SpacePressed()
{
	float speed = speedSlider;

	Vector3f velocity = cannonDirection * speed;

	auto newProjectile = SpawnRigidBody({ velocity, massField }, cannonDirection, ofGetLastFrameTime() * 10.f);

}



Vector3f World::m_gravity = Vector3f(0.0, -9.81f, 0.0f);

std::shared_ptr<Particle>  World::SpawnParticle(ParticleData data, Vector3f pos, bool isIntegrateEulerMode)
{
	//Create Particle
	Particle particle(pos, data.initialVelocity, data.mass, 0.05f, isIntegrateEulerMode);
	std::shared_ptr<Particle> particleShared = std::make_shared<Particle>(particle);
	 
	//Add Gravity
	ParticleGravity gravity(m_gravity);
	std::shared_ptr<ParticleGravity> forceGeneratorGravity = std::make_shared<ParticleGravity>(gravity);
	m_forceRegistry->Add(particleShared, forceGeneratorGravity, GRAVITY);

	//Add Collider
	m_collisionSystem.AddCollider(particle.GetSize(), particleShared);

	//Add Particle to list
	m_particles.push_back(particleShared);

	return particleShared;
}

std::shared_ptr<RigidBody>  World::SpawnRigidBody(ParticleData data, Vector3f pos, float duration)
{
	std::shared_ptr<Particle> particleShared = SpawnParticle(data, pos);
	
	RigidBody rb(particleShared);
	std::shared_ptr<RigidBody> rigidBodyShared = std::make_shared<RigidBody>(rb);
	m_rigidBody.push_back(rigidBodyShared);

	return rigidBodyShared;
}

void World::UpdatePhysics(float duration)
{
	m_OcTree = std::make_unique<OcTree>(Area(Vector3f(0.f,0.f,0.f), 200.f), 1, m_collisionSystem);

	m_forceRegistry->UpdateForces(duration);
	
	for (auto& rb : m_rigidBody) 
	{
		rb->ApplyTorque({ xTorqueField,yTorqueField, zTorqueField });
		rb->UpdateState(duration);
	}

	for (auto& particule : m_particles)
	{
		particule->Integrate(duration);
	}
}

void World::Draw()
{
	ofEnableDepthTest();

	//Draw Information
	ofDrawBitmapString("Delta Time : " + ofToString(ofGetLastFrameTime()), ofGetWidth() - 220.f, 30.f);
	ofSetColor(255, 120, 120);


	ofSetColor(255, 255, 255);
	camera.begin();



	//Draw Canon
	ofSetColor(100.f);
	plane.set(planeSizeField, planeSizeField);
	plane.draw();

	{
		ofPushMatrix();
		ofTranslate(0, 0, 0);
		ofRotateYDeg(yaw);
		ofRotateXDeg(-pitch);
		ofSetColor(255);
		canon.set(20);
		canon.draw();
		ofPopMatrix();
	}
		
	//Draw Particle
	for (auto& rb : m_rigidBody)
	{
		if (rb->GetPosition().y > -300) {

			ofPushMatrix();

			ofTranslate(rb->GetPosition());

			glm::quat orientation = glm::quat(rb->GetOrientation().GetNormalize());
			glm::mat4 rotationMat = glm::toMat4(orientation);
			ofMultMatrix(rotationMat);


			ofNoFill();
			ofSetColor(255);
			ofDrawBox(0, 0, 0, 50);

			ofSetColor(255.f, 0.f, 0.f);
			ofDrawSphere(0, 0, 0, 5.f);

			ofPopMatrix();
		}

	}


	//OCTREE
	ofNoFill();
	std::vector<std::shared_ptr<OcTree>> octreeAreas;
	m_OcTree->GetQuads(octreeAreas);
	for(auto ocTree : octreeAreas)
	{
		ofSetColor(0.f, 50.f * ocTree->GetDepth(), 0.f);
		ofDrawBox(ocTree->GetArea().pos, ocTree->GetArea().sideSize);
	}
	ofFill();

	camera.end();

	ofDisableDepthTest();
	gui.draw();
	
}

void World::ApplyCollisions()
{
	m_collisionSystem.ApplyCollisions();
}

void World::ApplyGroundCollisions()
{
	m_collisionSystem.ApplyGroundCollisions();
}

Vector3f World::GetGravity()
{
	return m_gravity;
}

void World::SetGravity(Vector3f gravity)
{
	m_gravity = gravity;
}
