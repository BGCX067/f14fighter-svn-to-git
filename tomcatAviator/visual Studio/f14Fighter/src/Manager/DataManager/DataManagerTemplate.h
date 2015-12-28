#ifndef _DATA_MANAGER_MENU_H_
#define _DATA_MANAGER_MENU_H_

#include "Ogre.h"

using namespace Ogre;

class DataManagerMenu
{	

public:	
	static DataManagerMenu*			getDataManagerAsSingleton(); // returns a pointer to a DataManager. DataManager is implemented as Singleton

private:
	DataManagerMenu(); 
	~DataManagerMenu();
	static DataManagerMenu*				_instance;
};
#endif