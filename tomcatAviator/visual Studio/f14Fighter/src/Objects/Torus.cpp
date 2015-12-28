#include "Torus.h"
#include "../Manager/DataManager/DataManager.h"

int	Torus::torusNumber = 0;

//--------------------------------------------------------------
Torus::Torus(Vector3 position, int color)
: entity(0), sceneNode(0), alive(true), torusDestroyed(false),	particleSystemExplotion(0), sceneNodeExplotion(0), dieTime(0)
{
	this->color = color;
	dataManager = DataManager::getDataManagerAsSingleton();
	uniqueNumber = torusNumber++;

	createTorus(position);

}

Torus::~Torus(void)
{
	std::cout << "Torus Deleted"<< std::endl;
	dataManager->sceneManager->destroySceneNode(sceneNode);
	dataManager->sceneManager->destroyEntity(entity);
	dataManager->sceneManager->destroyParticleSystem(particleSystemExplotion);
}

//--------------------------------------------------------------
void Torus::createTorus(Vector3 position)
{
	//##############//
	//# SCENE NODE #//
	//##############//
	std::string entityName = "torus" + StringConverter::toString(uniqueNumber);
	std::cout << entityName << " created at (" << position.x << "," << position.y << "," << position.z << ")" << std::endl;
	entity = dataManager->sceneManager->createEntity(entityName, "torus.mesh");
	
	std::string particleSystem = "";
	switch(color)
	{
	case F14FIGHTER::TORUS::BLUE:
		entity->setMaterialName("blueTorus");
		particleSystem = "F14/blueExplotion";
		break;
	case F14FIGHTER::TORUS::GREEN:
		entity->setMaterialName("greenTorus");
		particleSystem = "F14/greenExplotion";
		break;
	case F14FIGHTER::TORUS::RED:
		entity->setMaterialName("redTorus");
		particleSystem = "F14/redExplotion";
		break;
	case F14FIGHTER::TORUS::YELLOW:
		entity->setMaterialName("yellowTorus");
		particleSystem = "F14/yellowExplotion";
		break;
	}
	
	sceneNode = dataManager->sceneManager->getRootSceneNode()->createChildSceneNode();
	sceneNode->setPosition(position);
	sceneNode->attachObject(entity);

	sceneNode->yaw(Radian(((float)rand() / RAND_MAX))*2);
	std::string particleName = "explotion" + StringConverter::toString(uniqueNumber);
	//PARTICLE SYSTEM
	particleSystemExplotion = dataManager->sceneManager->createParticleSystem(particleName, particleSystem);
	particleSystemExplotion->setKeepParticlesInLocalSpace(true);
	particleSystemExplotion->getEmitter(0)->setEnabled(false);


	// Create shared node for 2 fountains
	sceneNodeExplotion =  sceneNode->createChildSceneNode();
	sceneNodeExplotion->attachObject(particleSystemExplotion);
	
}

//--------------------------------------------------------------
void Torus::moveTorus(float dt)
{
	if(sceneNode)
		sceneNode->yaw(Radian(dt));
	
	if(!alive && !torusDestroyed)
		die();
}

//--------------------------------------------------------------
void Torus::die()
{
	particleSystemExplotion->getEmitter(0)->setEnabled(true);
	sceneNode->setVisible(false, false);

	if(dataManager->myTimer.getElapsedTime()-dieTime > 2)
	{
		particleSystemExplotion->getEmitter(0)->setEnabled(false);
		torusDestroyed = true;
		dieTime = 0;
	}
}

//--------------------------------------------------------------
void Torus::letTorusDie()
{
	if(alive)
	{
		dataManager->system->playSound(FMOD_CHANNEL_FREE, dataManager->blubb, false, &dataManager->channelExplotion);
		alive = false;
		dieTime = dataManager->myTimer.getElapsedTime();
	}
}