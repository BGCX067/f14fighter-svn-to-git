#include "XboxDataManager.h"

XboxDataManager* XboxDataManager::_instance = 0;
//--------------------------------------------------------------
XboxDataManager* XboxDataManager::getDataManagerAsSingleton()
{
	
	if(_instance == 0)
		_instance = new XboxDataManager();
	
	return _instance;
}


XboxDataManager::XboxDataManager(void)
{
}

XboxDataManager::~XboxDataManager(void)
{
}

