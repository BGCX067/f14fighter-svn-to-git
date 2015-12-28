#ifndef _DATA_MANAGER_SINGLE_PLAYER_H_
#define _DATA_MANAGER_SINGLE_PLAYER_H_


#include "../../Objects/Torus.h"


#include "Ogre.h"
#include <CEGUI/CEGUI.h>
using namespace Ogre;

class DataManagerSinglePlayer
{	

public:	
	static DataManagerSinglePlayer*			getDataManagerAsSingleton(); // returns a pointer to a DataManager. DataManager is implemented as Singleton
	




	int										collectedTime;
private:
	DataManagerSinglePlayer(); 
	~DataManagerSinglePlayer();
	static DataManagerSinglePlayer*			_instance;
};
#endif