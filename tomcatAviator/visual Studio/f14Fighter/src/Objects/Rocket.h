#pragma once
#include "Ogre.h"
using namespace Ogre;

#define MAX_SPEED 100
class DataManager;
class Rocket
{
public:
	static int				rocketNumber;

	Rocket(Vector3 position, Vector3 direction);
	~Rocket(void);

	void					createRocket(Vector3 position, Vector3 direction);
	void					updateRocket(float dt);

	float					speed;
	Entity*					entity;
	SceneNode*				sceneNode;
	DataManager*			dataManager;
	Vector3					getDirection();
};
