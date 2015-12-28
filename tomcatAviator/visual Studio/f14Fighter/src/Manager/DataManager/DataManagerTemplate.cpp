
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
{

}
//--------------------------------------------------------------
DataManagerMenu::~DataManagerMenu()
{

}