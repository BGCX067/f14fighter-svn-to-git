#include "RunWay.h"
#include "../Manager/DataManager/DataManager.h"

RunWay::RunWay(Vector3 position, Vector3 scale)
{
	dataManager = DataManager::getDataManagerAsSingleton();
	settingManager.loadFile("runWaySettings.cfg");
	createRunWay(position, scale);
}

RunWay::~RunWay(void)
{
}
void RunWay::createRunWay(Vector3 position, Vector3 scale)
{
	float scaleFactor = scale.x;
	entity = dataManager->sceneManager->createEntity("runWay", "runway.mesh");
	sceneNode= dataManager->sceneManager->getRootSceneNode()->createChildSceneNode();
	
	sceneNode->setPosition(position);
	sceneNode->attachObject(entity);
	sceneNode->scale(scale);
	
	Plane plane(Vector3::UNIT_Y, 0);
	
	MeshManager::getSingleton().createPlane("runWayPlane", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, settingManager.getFloat("collisionPlaneWidth"), settingManager.getFloat("collisionPlaneHeight"),1,1,false,0,1,1,Vector3::UNIT_Z);
	entityPlane = dataManager->sceneManager->createEntity("runWayEntity", "runWayPlane");
	sceneNodePlane = sceneNode->createChildSceneNode();
	
	//sceneNodePlane->setPosition(sceneNode->getPosition());
	sceneNodePlane->translate(settingManager.getVector3("translatePlane"));
	sceneNodePlane->attachObject(entityPlane);
	sceneNodePlane->setVisible((bool)settingManager.getInt("showPlane"));
	sceneNodePlane->showBoundingBox((bool)settingManager.getInt("showPlaneBoundingBox"));
}