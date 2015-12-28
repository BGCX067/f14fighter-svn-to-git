#ifndef _DATA_MANAGER_H_
#define _DATA_MANAGER_H_

//HYDRAX
#include "Hydrax.h"

#include "Ogre.h"
#include "../../Defines.h"

#include "../SettingManager/SettingManager.h"
#include "../HighscoreManager/HighscoreManager.h"

#include "../StateManager/StateManager.h"
#include "../StateManager/States/States.h"

#include "../../other/MyTimer.h"

#include "../../XboxController/Thread.h"
#include "../../XboxController/XboxControllerThread.h"

#include "fmod.hpp"
#include "fmod_errors.h"

using namespace Ogre;

class DataManager
{	

public:	
	static DataManager*				getDataManagerAsSingleton(); // returns a pointer to a DataManager. DataManager is implemented as Singleton

	MyTimer							myTimer;
	// Hydrax pointer
	Hydrax::Hydrax*					mHydrax;

	SceneManager*					sceneManager;
	Root*							root;
	RenderWindow*					window;
	Camera*							camera;	

	StateManager					stateManager;
	//SettingManager					settingManagerSinglePlayer;
	HighscoreManager				settingManagerSinglePlayerHighscore;
	CEGUI::System*					CEGUISystem;
	CEGUI::OgreCEGUIRenderer*		CEGUIRenderer;

	bool							singlePlayerStarted;
	
	XboxControllerThread*			xboxThread;
	Thread*							thread;
	int								controller;
	FMOD::System*					system;
	FMOD::Sound*					backgroundMusicSinglePlayer;
	FMOD::Sound*					backgroundMusicMultiPlayer;
	FMOD::Sound*					backgroundMusicMultiPlayerRacer;

	FMOD::Sound*					explotion;
	FMOD::Sound*					blubb;
	FMOD::Sound*					jetSound;
	FMOD::Sound*					jetSoundStartup;



	FMOD::Channel*					channel;
	FMOD::Channel*					channelEffectsPlayer1;
	FMOD::Channel*					channelEffectsPlayer2;
	FMOD::Channel*					channelExplotion;
	FMOD::Channel*					channelStartUp;
	void							createFMODSystem();
	void							releaseFMODSystem();
private:
	DataManager(); 
	~DataManager();
	static DataManager*				_instance;
};
#endif