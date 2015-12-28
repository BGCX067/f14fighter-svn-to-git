#include "Rocket.h"
#include "../Manager/DataManager/DataManager.h"

int	Rocket::rocketNumber = 0;
Rocket::Rocket(Vector3 position, Vector3 direction)
:	entity(0), sceneNode(0), speed(0)
{
	rocketNumber++;
	dataManager = DataManager::getDataManagerAsSingleton();
	createRocket(position, direction);
}

Rocket::~Rocket(void)
{
}
void Rocket::createRocket(Vector3 position, Vector3 direction)
{
	std::string entityName = "rocket" + StringConverter::toString(rocketNumber);
	entity = dataManager->sceneManager->createEntity(entityName, "rocket.mesh");
	sceneNode = dataManager->sceneManager->getRootSceneNode()->createChildSceneNode();
	sceneNode->attachObject(entity);
	sceneNode->setPosition(position);
	sceneNode->setDirection(direction);
	
}
void Rocket::updateRocket(float dt)
{
	sceneNode->translate(getDirection()*speed);
}
Vector3 Rocket::getDirection()
{
	Matrix3 matrix;
	sceneNode->getOrientation().ToRotationMatrix(matrix);

	return matrix.GetColumn(2);
}