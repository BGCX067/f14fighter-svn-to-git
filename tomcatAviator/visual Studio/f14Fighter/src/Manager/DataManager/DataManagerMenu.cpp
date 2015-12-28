
#include "DataManagerMenu.h"


DataManagerMenu* DataManagerMenu::_instance = 0;
//--------------------------------------------------------------
DataManagerMenu* DataManagerMenu::getDataManagerAsSingleton()
{
	
	if(_instance == NULL)
		_instance = new DataManagerMenu();
	
	return _instance;
}
//--------------------------------------------------------------
DataManagerMenu::DataManagerMenu()
:	CEGUIWin(0), CEGUISheet(0),  newGame(0), controller(0), multiPlayer(0), multiPlayerRace(0), quit(0),	pImageSet(0),controllerText(0), about(0)
{
}
//--------------------------------------------------------------
DataManagerMenu::~DataManagerMenu()
{

}