#ifndef _FINISH_H_
#define _FINISH_H_
#include "Ogre.h"
#include "../Defines.h"

using namespace Ogre;

class DataManager;
class Finish
{
public:
	Finish(Vector3 position);
	~Finish(void);
	
	SceneNode*		sceneNode;
private:
	void			createFinish(Vector3 position);

	DataManager*	dataManager;

	Entity*			entity;


	SceneNode*		sceneNodeLeft;
	SceneNode*		sceneNodeRight;

	ParticleSystem* particleSystemLeft;
	ParticleSystem* particleSystemRight;

};
#endif