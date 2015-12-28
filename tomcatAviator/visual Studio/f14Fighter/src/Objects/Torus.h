#ifndef _TORUS_H_
#define	_TORUS_H_

#include "../Defines.h"
#include "Ogre.h"

using namespace Ogre;

class DataManager;
class Torus
{
public:
	Torus(Vector3 position, int color);
	~Torus(void);

	static int			torusNumber;
	
	void				moveTorus(float dt);
	void				letTorusDie();
	
	bool				torusDestroyed;
	int					color;
	float				dieTime;
	Entity*				entity;
	SceneNode*			sceneNode;
	int					uniqueNumber;
	bool				alive;
	
private:
	void				createTorus(Vector3 position);
	void				die();

	
	ParticleSystem*		particleSystemExplotion;
	SceneNode*			sceneNodeExplotion;
	DataManager*		dataManager;
};

#endif