#ifndef _DATA_MANAGER_MENU_H_
#define _DATA_MANAGER_MENU_H_


#include <CEGUI/CEGUI.h>

#include "Ogre.h"

using namespace Ogre;

class DataManagerMenu
{	

public:	
	static DataManagerMenu*			getDataManagerAsSingleton(); // returns a pointer to a DataManager. DataManager is implemented as Singleton

    CEGUI::WindowManager*			CEGUIWin;
    CEGUI::Window*					CEGUISheet;

	CEGUI::Window*					newGame;
	CEGUI::Window*					controller;
	CEGUI::Window*					multiPlayer;
	CEGUI::Window*					multiPlayerRace;
	CEGUI::Window*					quit;
	CEGUI::Imageset*				pImageSet;
	CEGUI::Window*					controllerText;
	CEGUI::Window*					about;
	
	
private:
	DataManagerMenu(); 
	~DataManagerMenu();
	static DataManagerMenu*				_instance;
};
#endif