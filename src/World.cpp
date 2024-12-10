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


	gui.add(planeSizeField.setup("Plane Size", 1000, 1, 3840));
	gui.add(speedSlider.setup("Launch Speed", 25.f, 10.0f, 100.0f));

	gui.add(yawSlider.setup("Canon Yaw", yaw, -180.0f, 180.0f));
	gui.add(pitchSlider.setup("Canon Pitch", pitch, -90.0f, 90.0f));

	gui.add(massField.setup("Projectile Mass", 100.f, 1.0f, 100000.f));

	gui.add(xTorqueField.setup("X Torque", 0.f, -1000.0f, 1000.f));
	gui.add(yTorqueField.setup("Y Torque", 0.f, -1000.0f, 1000.f));
	gui.add(zTorqueField.setup("Z Torque", -100.f, -1000.0f, 1000.f));



	///dimensions for width and height in pixels
	/*plane.setPosition(0, -300, 0); /// position in x y z
	plane.setOrientation({ 90,0,0 });
	plane.setResolution(8, 8);*/

	canon.setPosition(0, 0, 0);

	CreateGameBox(planeSizeField);
}

void World::CreateGameBox(float boxSize)
{
	floor.set(boxSize, boxSize);
	floor.setPosition(0, -boxSize / 2, 0);
	floor.setOrientation({ 90, 0, 0 }); 
	floor.setResolution(8, 8);
	m_walls.push_back(floor);

	auto floorParticle = std::make_shared<Particle>(floor.getPosition());
	auto floorRb = std::make_shared<RigidBody>(floorParticle);
	m_WallRigidBody.push_back(floorRb);
	m_collisionSystem.AddCollider(boxSize, floorParticle);

	/*ceiling.set(boxSize, boxSize); 
	ceiling.setPosition(0, boxSize / 2, 0);
	ceiling.setOrientation({ 90, 0, 0 }); 
	ceiling.setResolution(8, 8);
	m_walls.push_back(ceiling);*/

	frontWall.set(boxSize, boxSize);
	frontWall.setPosition(0, 0, boxSize / 2);
	frontWall.setOrientation({ 0, 0, 0 });
	frontWall.setResolution(8, 8);
	m_walls.push_back(frontWall);

	auto frontWallParticle = std::make_shared<Particle>(frontWall.getPosition());
	auto frontWallRb = std::make_shared<RigidBody>(frontWallParticle);
	m_WallRigidBody.push_back(frontWallRb);
	m_collisionSystem.AddCollider(boxSize, frontWallParticle);

	backWall.set(boxSize, boxSize);
	backWall.setPosition(0, 0, -boxSize / 2);
	backWall.setOrientation({ 0, 0, 0 }); 
	backWall.setResolution(8, 8);
	m_walls.push_back(backWall);

	auto backWallParticle = std::make_shared<Particle>(backWall.getPosition());
	auto backWallRb = std::make_shared<RigidBody>(backWallParticle);
	m_WallRigidBody.push_back(backWallRb);
	m_collisionSystem.AddCollider(boxSize, backWallParticle);

	leftWall.set(boxSize, boxSize);
	leftWall.setPosition(-boxSize / 2, 0, 0);
	leftWall.setOrientation({ 0, 90, 0 }); 
	leftWall.setResolution(8, 8);
	m_walls.push_back(leftWall);

	auto leftWallParticle = std::make_shared<Particle>(leftWall.getPosition());
	auto leftWallRb = std::make_shared<RigidBody>(leftWallParticle);
	m_WallRigidBody.push_back(leftWallRb);
	m_collisionSystem.AddCollider(boxSize, leftWallParticle);

	rightWall.set(boxSize, boxSize);
	rightWall.setPosition(boxSize / 2, 0, 0); 
	rightWall.setOrientation({ 0, 90, 0 }); 
	rightWall.setResolution(8, 8);
	m_walls.push_back(rightWall);

	auto rightWallParticle = std::make_shared<Particle>(rightWall.getPosition());
	auto rightWallRb = std::make_shared<RigidBody>(rightWallParticle);
	m_WallRigidBody.push_back(rightWallRb);
	m_collisionSystem.AddCollider(boxSize, rightWallParticle);
}

void World::UpdateGameBox() {
	float boxSize = planeSizeField;
	for (auto& wall : m_walls) {
		wall.set(boxSize, boxSize);
	}

	m_walls[0].setPosition(0, -boxSize / 2, 0); 
	m_walls[1].setPosition(0, 0, boxSize / 2); 
	m_walls[2].setPosition(0, 0, -boxSize / 2);
	m_walls[3].setPosition(-boxSize / 2, 0, 0);
	m_walls[4].setPosition(boxSize / 2, 0, 0);
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
	UpdateGameBox();
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
	m_OcTree = std::make_unique<OcTree>(Area(Vector3f(0.f,0.f,0.f), planeSizeField), 1, m_collisionSystem);

	for(size_t i = 0 ; i< m_walls.size(); i++)
	{
		/*auto wallObject = std::make_shared<OcTree::Rigidboy>();
		wallObject->Box = m_wallBoxes[i];*/
		
		m_OcTree->InsertObject(m_WallRigidBody[i]);
	}

	for (size_t i = 0; i < m_rigidBody.size(); i++)
	{
		/*auto rbCollision = std::make_shared<OcTree::ObjectCollision>();
		rbCollision->Box = rb->GetBoundingBox();
		rbCollision->Sphere = rb->GetBoundingSphere();*/

		m_OcTree->InsertObject(m_rigidBody[i]);
	}
	

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
	ApplyCollisions();
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
	/*plane.set(planeSizeField, planeSizeField);
	plane.draw();*/
	
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
	
	/*UpdateGameBox();*/
	for (const auto& wall : m_walls)
	{
		ofSetColor(200);
		wall.draw();
	}

	ofNoFill();
	/*UpdateGameBox();*/
	for (const auto& wall : m_walls)
	{
		ofSetColor(200, 200, 200);
		wall.draw();
	}
	ofFill();

	//Draw Particle
	for (auto& rb : m_rigidBody)
	{
		/*if (rb->GetPosition().y > -300) {*/

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
		/*}*/

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
	if (m_OcTree)
	{
		m_OcTree->TestCollision();
	}
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
