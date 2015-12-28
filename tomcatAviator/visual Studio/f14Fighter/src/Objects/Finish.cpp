#include "Finish.h"
#include "../Manager/DataManager/DataManager.h"

Finish::Finish(Vector3 position)
: entity(0), sceneNode(0), sceneNodeLeft(0), sceneNodeRight(0), particleSystemLeft(0), particleSystemRight(0)
{
	dataManager = DataManager::getDataManagerAsSingleton();
	createFinish(position);
}

Finish::~Finish(void)
{
}
void Finish::createFinish(Vector3 position)
{
	Plane plane(Vector3::UNIT_Z, 0);
	
	//MeshManager::getSingleton().createPlane("finishPlane", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 800,1500,1,1,true,0,1,1,Vector3::UNIT_Y);
	entity = dataManager->sceneManager->createEntity("finishEntity", "cube.mesh");
	sceneNode = dataManager->sceneManager->getRootSceneNode()->createChildSceneNode();
	
	sceneNode->setPosition(position);
	sceneNode->scale(20,40,40);
	sceneNode->attachObject(entity);
	sceneNode->setVisible(false, false);
	sceneNode->showBoundingBox(false);

	//LEFT
	particleSystemLeft = dataManager->sceneManager->createParticleSystem("finishLeft", "F14/greenFontain");
	//particleSystemLeft->getEmitter(0)->setEnabled(false);
	// Create shared node for 2 fountains
	sceneNodeLeft =  sceneNode->createChildSceneNode();
	sceneNodeLeft->attachObject(particleSystemLeft);
	sceneNodeLeft->translate(Vector3(-30,0,50));


	//RIGHT
	particleSystemRight = dataManager->sceneManager->createParticleSystem("finishRight", "F14/greenFontain");
	//particleSystemRight->getEmitter(0)->setEnabled(false);	
	
	// Create shared node for 2 fountains
	sceneNodeRight =  sceneNode->createChildSceneNode();
	sceneNodeRight->attachObject(particleSystemRight);
	sceneNodeRight->translate(Vector3(30,0,50));
	

}