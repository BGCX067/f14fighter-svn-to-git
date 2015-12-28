#pragma once

#include "Ogre.h"
#include "../Defines.h"
#include "../Manager/SettingManager/SettingManager.h"

using namespace Ogre;
class DataManager;
class RunWay
{
public:
	RunWay(Vector3 position, Vector3 scale);
	~RunWay(void);
	void			createRunWay(Vector3 position, Vector3 scale);
	Entity*			entity;
	Entity*			entityPlane;

	SceneNode*		sceneNode;
	SceneNode*		sceneNodePlane;
	DataManager*	dataManager;
	SettingManager	settingManager;
};
