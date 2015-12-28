
#include "DataManager.h"


DataManager* DataManager::_instance = 0;
//--------------------------------------------------------------
DataManager* DataManager::getDataManagerAsSingleton()
{
	
	if(_instance == NULL)
		_instance = new DataManager();
	
	return _instance;
}
//--------------------------------------------------------------
DataManager::DataManager()
:	CEGUISystem(0), CEGUIRenderer(0), mHydrax(0), sceneManager(0), root(0), camera(0), window(0),singlePlayerStarted(false),
	xboxThread(0), thread(0)

{
	//settingManagerSinglePlayer.loadFile("singlePlayerSettings.cfg");
	settingManagerSinglePlayerHighscore.loadFile("singlePlayerHighscore.cfg");
	controller = F14FIGHTER::Controller::XBOXCONTROLLER;
}
void DataManager::createFMODSystem()
{
	FMOD::System_Create(&system);
	system->init(128, FMOD_INIT_NORMAL, 0);

	system->createSound("Head Them Up.wav", FMOD_HARDWARE, 0, &backgroundMusicSinglePlayer);
	backgroundMusicSinglePlayer->setMode(FMOD_LOOP_NORMAL);
	system->createSound("Marshall Law.wav", FMOD_HARDWARE, 0, &backgroundMusicMultiPlayer);
	backgroundMusicMultiPlayer->setMode(FMOD_LOOP_NORMAL);
	system->createSound("That Hurts.wav", FMOD_HARDWARE, 0, &backgroundMusicMultiPlayerRacer);
	backgroundMusicMultiPlayerRacer->setMode(FMOD_LOOP_NORMAL);

	system->createSound("Jet_Sound.wav", FMOD_HARDWARE, 0, &jetSound);
	jetSound->setMode(FMOD_LOOP_NORMAL);
	system->createSound("explosion.wav", FMOD_HARDWARE, 0, &explotion);
	explotion->setMode(FMOD_LOOP_OFF);
	system->createSound("blubb.wav", FMOD_HARDWARE, 0, &blubb);
	explotion->setMode(FMOD_LOOP_OFF);

	system->createSound("jetengine_startup.wav", FMOD_HARDWARE, 0, &jetSoundStartup);
	//jetSoundStartup->setMode(FMOD_LOOP_OFF);
}
void DataManager::releaseFMODSystem()
{
	system->release();
}
//--------------------------------------------------------------
DataManager::~DataManager()
{

}

