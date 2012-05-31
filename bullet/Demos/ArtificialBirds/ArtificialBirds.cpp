

#include "ArtificialBirds.h"
#include "btBulletDynamicsCommon.h"
#include "GlutStuff.h"
#include "GL_ShapeDrawer.h"
#include "LinearMath/btIDebugDraw.h"
#include "GLDebugDrawer.h"
#include "BigBird.h"
#include "BigFeather.h"

btScalar kGravity = -9.80;

void pickingPreTickCallback(btDynamicsWorld *world, btScalar timeStep) {
	ArtificialBirdsDemoApp* app = (ArtificialBirdsDemoApp*)world->getWorldUserInfo();

	for (int ii = 0; ii < app->getFeathers().size(); ++ii) {
		app->getFeathers()[ii]->pretick(timeStep);
	}

	for (int ii = 0; ii < app->getBirds().size(); ++ii) {
		app->getBirds()[ii]->pretick(timeStep);
	}
}

void ArtificialBirdsDemoApp::initPhysics()
{
	// Setup the basic world

	setTexturing(true);
	setShadows(true);

	setCameraDistance(btScalar(5.));

	m_collisionConfiguration = new btDefaultCollisionConfiguration();

	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

	btVector3 worldAabbMin(-10000,-10000,-10000);
	btVector3 worldAabbMax(10000,10000,10000);
	m_broadphase = new btAxisSweep3 (worldAabbMin, worldAabbMax);

	m_solver = new btSequentialImpulseConstraintSolver;
	

	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher,m_broadphase,m_solver,m_collisionConfiguration);
	//m_dynamicsWorld->getDispatchInfo().m_useConvexConservativeDistanceUtil = true;
	//m_dynamicsWorld->getDispatchInfo().m_convexConservativeDistanceThreshold = 0.01f;
	m_dynamicsWorld->setInternalTickCallback(pickingPreTickCallback, this, true);
	m_dynamicsWorld->setGravity(btVector3(0,kGravity,0));

	// Setup a big ground box
	{
		btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(200.),btScalar(10.),btScalar(200.)));
		m_collisionShapes.push_back(groundShape);
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0,-10,0));

#define CREATE_GROUND_COLLISION_OBJECT 1
#ifdef CREATE_GROUND_COLLISION_OBJECT
		btCollisionObject* fixedGround = new btCollisionObject();
		fixedGround->setCollisionShape(groundShape);
		fixedGround->setWorldTransform(groundTransform);
		m_dynamicsWorld->addCollisionObject(fixedGround);
#else
		localCreateRigidBody(btScalar(0.),groundTransform,groundShape);
#endif //CREATE_GROUND_COLLISION_OBJECT

	}

	btVector3 startOffset(0,2,0);
	spawnBigBird(startOffset);

	clientResetScene();		
}

void ArtificialBirdsDemoApp::spawnBigBird(const btVector3& startOffset)
{
	BigBird* bigbird = new BigBird (m_dynamicsWorld, startOffset);
	m_bigbirds.push_back(bigbird);
}

void ArtificialBirdsDemoApp::spawnBigFeather(const btVector3& startOffset)
{
	BigFeather* bigfeather = new BigFeather(m_dynamicsWorld, startOffset, 0, 0);
	m_bigfeathers.push_back(bigfeather);
}

void ArtificialBirdsDemoApp::clientMoveAndDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	//simple dynamics world doesn't handle fixed-time-stepping
	float ms = getDeltaTimeMicroseconds();

	float minFPS = 1000000.f/60.f;
	if (ms > minFPS)
		ms = minFPS;

	if (m_dynamicsWorld)
	{
		m_dynamicsWorld->stepSimulation(ms / 1000000.f, 20);
		
		//optional but useful: debug drawing
		m_dynamicsWorld->debugDrawWorld();


	}

	m_cameraTargetPosition = m_bigbirds[0]->getPosition();

	renderme(); 

	glFlush();

	glutSwapBuffers();
}

void ArtificialBirdsDemoApp::displayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	renderme();

	//optional but useful: debug drawing
	if (m_dynamicsWorld)
		m_dynamicsWorld->debugDrawWorld();

	glFlush();
	glutSwapBuffers();
}

void ArtificialBirdsDemoApp::keyboardCallback(unsigned char key, int x, int y)
{
	switch (key)
	{
<<<<<<< Updated upstream
	case 'd':
=======
	case 'w':
		{
			for (int ii = 0; ii < m_bigbirds.size(); ++ii) {
				m_bigbirds[ii]->applyUpImpulse();
			}
		break;
		}		
	case 's':
		{
			for (int ii = 0; ii < m_bigbirds.size(); ++ii) {
				m_bigbirds[ii]->applyDownImpulse();
			}
		break;
		}		
	case 'd':
		{
			for (int ii = 0; ii < m_bigbirds.size(); ++ii) {
				m_bigbirds[ii]->applyForImpulse();
			}
		break;
		}		
	case 'z':
		{
			for (int ii = 0; ii < m_bigbirds.size(); ++ii) {
				m_bigbirds[ii]->zeroImpulse();
			}
		break;
		}		
	case 'a':
>>>>>>> Stashed changes
		{
			for (int ii = 0; ii < m_bigbirds.size(); ++ii) {
				m_bigbirds[ii]->toggleMotors();
			}
		break;
		}		
<<<<<<< Updated upstream
	case 'w':
		{
			for (int ii = 0; ii < m_bigbirds.size(); ++ii) {
				m_bigbirds[ii]->applyUpImpulse();
			}
		break;
		}		
	case 's':
		{
			for (int ii = 0; ii < m_bigbirds.size(); ++ii) {
				m_bigbirds[ii]->applyDownImpulse();
			}
		break;
		}	
	case 'z':
		{
			for (int ii = 0; ii < m_bigbirds.size(); ++ii) {
				m_bigbirds[ii]->zeroImpulse();
			}
			break;
		}
	case 'a':
		{
			for (int ii = 0; ii < m_bigbirds.size(); ++ii) {
				m_bigbirds[ii]->toggleMotors();
			}
		break;
		}		
=======
	case 'g':
		{
			if (kGravity == 0.0) {
				kGravity = -9.80;
				m_dynamicsWorld->setGravity(btVector3(0,kGravity,0));
			}
			else {
				kGravity = 0.0;
				m_dynamicsWorld->setGravity(btVector3(0,kGravity,0));
			}
		break;
		}
	case 'u':
		{
			for (int ii = 0; ii < m_bigbirds.size(); ++ii) {
				m_bigbirds[ii]->upTailAngle();
			}
		break;
		}
	case 'j':
		{
			for (int ii = 0; ii < m_bigbirds.size(); ++ii) {
				m_bigbirds[ii]->downTailAngle();
			}
		break;
		}
>>>>>>> Stashed changes
	case 'G':
		{
			for (int ii = 0; ii < m_bigbirds.size(); ++ii) {
				m_bigbirds[ii]->applyFeatherImpulse();
			}
		break;
		}
	case 'p':
		{
			for (int ii = 0; ii < m_bigfeathers.size(); ++ii) {
				m_bigfeathers[ii]->applyImpulse();
			}
		break;
		}
	case 'o':
		{
			static btScalar angle = 0;
			angle+= 10;

			for (int ii = 0; ii < m_bigfeathers.size(); ++ii) {
				m_bigfeathers[ii]->orient(btRadians(angle));
				m_bigfeathers[ii]->applyImpulse();
			}
		break;
		}

	case 'e':
		{
		btVector3 startOffset(0,2,0);
		spawnBigBird(startOffset);
		break;
		}
	case 'f':
		{
		btVector3 startOffset(0,2,0);
		spawnBigFeather(startOffset);
		break;
		}
	default:
		DemoApplication::keyboardCallback(key, x, y);
	}

	
}

void ArtificialBirdsDemoApp::exitPhysics()
{

	int i;

	for (i=0;i<m_bigbirds.size();i++)
	{
		BigBird* bird = m_bigbirds[i];
		delete bird;
	}

	for (i=0;i<m_bigfeathers.size();i++)
	{
		BigFeather* feather = m_bigfeathers[i];
		delete feather;
	}

	//cleanup in the reverse order of creation/initialization

	//remove the rigidbodies from the dynamics world and delete them
	
	for (i=m_dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
	{
		btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		m_dynamicsWorld->removeCollisionObject( obj );
		delete obj;
	}
	
	//delete collision shapes
	for (int j=0;j<m_collisionShapes.size();j++)
	{
		btCollisionShape* shape = m_collisionShapes[j];
		delete shape;
	}

	//delete dynamics world
	delete m_dynamicsWorld;

	//delete solver
	delete m_solver;

	//delete broadphase
	delete m_broadphase;

	//delete dispatcher
	delete m_dispatcher;

	delete m_collisionConfiguration;

	
}