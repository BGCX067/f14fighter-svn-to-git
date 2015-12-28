
#include "DataManagerSinglePlayer.h"


DataManagerSinglePlayer* DataManagerSinglePlayer::_instance = 0;
//--------------------------------------------------------------
DataManagerSinglePlayer* DataManagerSinglePlayer::getDataManagerAsSingleton()
{
	
	if(_instance == NULL)
		_instance = new DataManagerSinglePlayer();
	
	return _instance;
}
//--------------------------------------------------------------
DataManagerSinglePlayer::DataManagerSinglePlayer()
: collectedTime(0)
{

}
//--------------------------------------------------------------
DataManagerSinglePlayer::~DataManagerSinglePlayer()
{

}