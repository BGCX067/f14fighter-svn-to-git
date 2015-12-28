#include "MultiPlayerRace.h"
#include "../../DataManager/DataManager.h"

//--------------------------------------------------------------
MultiPlayerRace::MultiPlayerRace(StateManager *stateManager)
:	State(stateManager), camera1(0), camera2(0), CEGUIWin(0), CEGUISheet(0), elapsedTime(-100), timeStampStartMultiPlayer(-100),
	currentState(F14FIGHTER::MULTIPLAYERRACE::COUNTDOWN),raySceneQuery(0), runWay(0),finish(0), winner(-1)
{
	for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		boostBar[i] = 0;
		timeUntilNextToggleInfoboxPlayer[i] = 0 ;

	}

	
	std::cout << "###########################" << std::endl;
	std::cout << "# MultiPlayerRace created #" << std::endl;
	std::cout << "###########################" << std::endl;
	settingManager.loadFile("MultiPlayerRaceSettings.cfg");
	
}

//--------------------------------------------------------------
MultiPlayerRace::~MultiPlayerRace()
{
	
	dataManager->window->removeViewport(2);
	dataManager->window->removeViewport(1);
	dataManager->window->removeViewport(3);
	dataManager->sceneManager->destroyCamera(camera1);
	dataManager->sceneManager->destroyCamera(camera2);
	dataManager->sceneManager->destroyCamera(camera3);
	std::vector<Torus*>::iterator torusIterator = torus.begin();
	
    while(torusIterator != torus.end())
	{
        delete *torusIterator;
        torusIterator = torus.erase(torusIterator);
        continue;
        ++torusIterator;
    } 
	Torus::torusNumber = 0;

	CEGUIWin->destroyAllWindows();
	delete finish;
	for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		if(boostBar[i])
		{
			boostBar[i]->removeAllEvents();
			boostBar[i]->destroy();
		}
		if(colorBar[i])
		{
			colorBar[i]->removeAllEvents();
			colorBar[i]->destroy();
		}
		if(speedBar[i])
		{
			speedBar[i]->removeAllEvents();
			speedBar[i]->destroy();
		}
		if(boostText[i])
		{
			boostText[i]->removeAllEvents();
			boostText[i]->destroy();
		}
		if(colorText[i])
		{
			colorText[i]->removeAllEvents();
			colorText[i]->destroy();
		}
		if(speedText[i])
		{
			speedText[i]->removeAllEvents();
			speedText[i]->destroy();
		}
		if(infoBox[i])
		{
			infoBox[i]->removeAllEvents();
			infoBox[i]->destroy();
		}
		if(centerTextWindow[i])
		{
			centerTextWindow[i]->removeAllEvents();
			centerTextWindow[i]->destroy();
		}
	}
	dataManager->channel->setPaused(true);
	dataManager->channelEffectsPlayer1->setPaused(true);
	dataManager->channelEffectsPlayer2->setPaused(true);
	dataManager->releaseFMODSystem();
}
//--------------------------------------------------------------
void MultiPlayerRace::setup(void)
{
	createCamera();
}

//--------------------------------------------------------------
void MultiPlayerRace::createScene(void)
{
	f14Player[0] = new F14(0,settingManager.getVector3("startPositionPlayer1"), camera1, "f14_mat", Vector3(0,0,1));
	f14Player[1] = new F14(1,settingManager.getVector3("startPositionPlayer2"), camera2, "f14_mat1", Vector3(0,0,1));
	dataManager->sceneManager->setSkyBox(true, settingManager.getString("skyBox"));
	dataManager->sceneManager->setWorldGeometry(settingManager.getString("worldGeometry"));
	

	runWay = new RunWay(Vector3(2000,300,0), Vector3(6,6,6));	
	
	f14Player[0]->sceneNode->yaw(Degree(settingManager.getFloat("starYaw2Player1")),Node::TS_LOCAL);

	//##########//
	//# FINISH #//
	//##########//
	finish = new Finish(settingManager.getVector3("finishPosition"));
	finish->sceneNode->yaw(Degree(180));

	Entity* terrainEntity= dataManager->sceneManager->createEntity("terrainLeft", "terrain1.mesh");
	terrainEntity->setMaterialName("Island");
	SceneNode* terrainSceneNode = dataManager->sceneManager->getRootSceneNode()->createChildSceneNode();
	terrainSceneNode->attachObject(terrainEntity);
	terrainSceneNode->setPosition(settingManager.getVector3("highTerrainLeft"));
	terrainSceneNode->setScale(settingManager.getVector3("highTerrainLeftScale"));
	terrain.push_back(terrainSceneNode);

	
	terrainEntity= dataManager->sceneManager->createEntity("terrainRight", "terrain1.mesh");
	terrainEntity->setMaterialName("Island");
	terrainSceneNode = dataManager->sceneManager->getRootSceneNode()->createChildSceneNode();
	terrainSceneNode->attachObject(terrainEntity);
	terrainSceneNode->setPosition(settingManager.getVector3("highTerrainRight"));
	terrainSceneNode->setScale(settingManager.getVector3("highTerrainRightScale"));
	terrain.push_back(terrainSceneNode);

	terrainEntity= dataManager->sceneManager->createEntity("terrainBack", "terrain1.mesh");
	terrainEntity->setMaterialName("Island");
	terrainSceneNode = dataManager->sceneManager->getRootSceneNode()->createChildSceneNode();
	terrainSceneNode->attachObject(terrainEntity);
	terrainSceneNode->setPosition(settingManager.getVector3("highTerrainBack"));
	terrainSceneNode->setScale(settingManager.getVector3("highTerrainBackScale"));
	terrain.push_back(terrainSceneNode);

	
	terrainEntity= dataManager->sceneManager->createEntity("terrainFront", "terrain1.mesh");
	terrainEntity->setMaterialName("Island");
	terrainSceneNode = dataManager->sceneManager->getRootSceneNode()->createChildSceneNode();
	terrainSceneNode->attachObject(terrainEntity);
	terrainSceneNode->setPosition(settingManager.getVector3("highTerrainFront"));
	terrainSceneNode->setScale(settingManager.getVector3("highTerrainFrontScale"));
	terrain.push_back(terrainSceneNode);

	int numberOfTours = settingManager.getInt("numberOfTorus");


	//TERRAIN CUBES
	for(int i = 0; i < 2; i++)
	{
		terrainCubeBoundingEntity[i] = dataManager->sceneManager->createEntity("terrainCubeBoundingEntity" + StringConverter::toString(i), "cube.mesh");
		terrainCubeBoundingEntity[i]->setMaterialName("wall2");
		terrainCubeBoundingSceneNode[i] = dataManager->sceneManager->getRootSceneNode()->createChildSceneNode();
		terrainCubeBoundingSceneNode[i]->attachObject(terrainCubeBoundingEntity[i]);
	}

	
	terrainCubeBoundingSceneNode[0]->setPosition(Vector3(0,0,50000));
	terrainCubeBoundingSceneNode[0]->scale(2,100,1000);
	terrainCubeBoundingSceneNode[0]->setVisible(true,false);

	terrainCubeBoundingSceneNode[1]->setPosition(Vector3(3500,0,50000));
	terrainCubeBoundingSceneNode[1]->scale(2,100,1000);
	terrainCubeBoundingSceneNode[1]->setVisible(true,false);

	//terrainCubeBoundingSceneNode[2]->setPosition(Vector3(0,0,19500));
	//terrainCubeBoundingSceneNode[2]->scale(1000,1000,2);
	//terrainCubeBoundingSceneNode[2]->setVisible(false,false);

	//terrainCubeBoundingSceneNode[3]->setPosition(Vector3(0,0,200));
	//terrainCubeBoundingSceneNode[3]->scale(1000,1000,2);
	//terrainCubeBoundingSceneNode[3]->setVisible(false,false);

	//terrainCubeBoundingSceneNode[4]->setPosition(Vector3(0,20000,0));
	//terrainCubeBoundingSceneNode[4]->scale(1000,2,1000);
	//terrainCubeBoundingSceneNode[4]->setVisible(false,false);

	//#########//
	//# TORUS #//
	//#########//
	Torus* newTorus = 0;

	Vector3 torusPathDirection = settingManager.getVector3("finishPosition") - runWay->sceneNode->getPosition();
	torusPathDirection /= numberOfTours + 1;
	
	Vector3	shiftValues = settingManager.getVector3("torusShiftPosition");

	for(int i = 0; i < numberOfTours; i++)
	{
		Vector3 positionShiftVector = Vector3(rand()%(int)shiftValues.x,rand()%(int)shiftValues.y,rand()%(int)shiftValues.x);
	
		Vector3 tempVec = runWay->sceneNode->getPosition() + (torusPathDirection * (i+1));
		tempVec -= Vector3(2000,0,0);
		tempVec.y = runWay->sceneNode->getPosition().y;
		tempVec += positionShiftVector;
	
		float colorProbability = ((float)rand() / RAND_MAX);
		int color = 0;
		
		//GREEN
		if(colorProbability > settingManager.getFloat("greenDegreeOfProbability"))
			color = F14FIGHTER::TORUS::GREEN;
		//RED
		else if(colorProbability > settingManager.getFloat("redDegreeOfProbability"))
			color = F14FIGHTER::TORUS::RED;
		////YELLOW
		//else if(colorProbability > settingManager.getFloat("yellowDegreeOfProbability"))
		//	color = F14FIGHTER::TORUS::YELLOW;
		//BLUE
		else
			color = F14FIGHTER::TORUS::BLUE;

		newTorus = new Torus(tempVec,color);
		newTorus->sceneNode->setScale(Vector3(50,50,50));
		torus.push_back(newTorus);
	}

	raySceneQuery = dataManager->sceneManager->createRayQuery( Ray(f14Player[0]->sceneNode->getPosition(), Vector3::NEGATIVE_UNIT_Y));
	dataManager->createFMODSystem();
	dataManager->system->playSound(FMOD_CHANNEL_FREE, dataManager->backgroundMusicMultiPlayerRacer, false, &dataManager->channel);
	dataManager->channel->setVolume(0.3);
	dataManager->system->playSound(FMOD_CHANNEL_FREE, dataManager->jetSound, false, &dataManager->channelEffectsPlayer1);
	dataManager->channelEffectsPlayer1->setVolume(0.3);
	dataManager->system->playSound(FMOD_CHANNEL_FREE, dataManager->jetSound, false, &dataManager->channelEffectsPlayer2);
	dataManager->channelEffectsPlayer2->setVolume(0.3);
} 
//--------------------------------------------------------------
void MultiPlayerRace::createLights(void)
{
	ColourValue diffuseColor(	settingManager.getVector3("diffuseColor").x,
								settingManager.getVector3("diffuseColor").y,
								settingManager.getVector3("diffuseColor").z);
	ColourValue ambientColor(	settingManager.getVector3("ambientColor").x,
								settingManager.getVector3("ambientColor").y,
								settingManager.getVector3("ambientColor").z);
	// Set ambient light
	dataManager->sceneManager->setAmbientLight(ambientColor);
	
	// Create a light
	Light* l = dataManager->sceneManager->createLight("Light1");
	l->setType(Ogre::Light::LT_DIRECTIONAL);
	l->setDirection(0,-1,0);
	l->setDiffuseColour(diffuseColor);

	l = dataManager->sceneManager->createLight("Light2");
	l->setType(Ogre::Light::LT_DIRECTIONAL);
	l->setDirection(1,-1,0);
	l->setDiffuseColour(diffuseColor);

	l = dataManager->sceneManager->createLight("Light3");
	l->setType(Ogre::Light::LT_DIRECTIONAL);
	l->setDirection(-1,-1,0);
	l->setDiffuseColour(diffuseColor);

	l = dataManager->sceneManager->createLight("Light4");
	l->setType(Ogre::Light::LT_DIRECTIONAL);
	l->setDirection(0,-1,1);
	l->setDiffuseColour(diffuseColor);

	l = dataManager->sceneManager->createLight("Light5");
	l->setType(Ogre::Light::LT_DIRECTIONAL);
	l->setDirection(0,-1,-1);
	l->setDiffuseColour(diffuseColor);
}
//--------------------------------------------------------------
void MultiPlayerRace::setupGUI(void)
{	
	//WINDOW AND SHEET FOR DataManagerMenu
	// Quit button
	CEGUIWin = CEGUI::WindowManager::getSingletonPtr();
	CEGUISheet = CEGUIWin->createWindow("DefaultGUISheet", "CEGUIDemo/Sheet");
	
	setupGuiForPlayer(0);
	setupGuiForPlayer(1);

	dataManager->CEGUISystem->setGUISheet(CEGUISheet);	
	CEGUISheet->show();	
	
}
//--------------------------------------------------------------
void MultiPlayerRace::setupGuiForPlayer(int playerNumber)
{
	float xOffset = 0.0f;
	float yOffset = 0.0f;

	switch(playerNumber)
	{
	case 0:
		xOffset = 0.0f;
		yOffset = 0.0f;
		break;

	case 1:
		xOffset = 0.5f;
		yOffset = 0.0f;
		break;
	}
	/////////////////
	//BOOST BAR
	boostBar[playerNumber] = static_cast<CEGUI::ProgressBar*> (CEGUIWin->createWindow("TaharezLook/AlternateProgressBar", "singlePlayer/boostBar" + StringConverter::toString(playerNumber)));
    boostBar[playerNumber]->setSize(CEGUI::UVector2(CEGUI::UDim(0.075, 0), CEGUI::UDim(0.04, 0)));
	boostBar[playerNumber]->setPosition(CEGUI::UVector2(CEGUI::UDim(xOffset + 0.04, 0), CEGUI::UDim(yOffset + 0, 0)));
	CEGUISheet->addChildWindow(boostBar[playerNumber]);

	
	/////////////////
	//Color BAR
	colorBar[playerNumber] = static_cast<CEGUI::ProgressBar*> (CEGUIWin->createWindow("TaharezLook/AlternateProgressBar", "singlePlayer/colorBar" + StringConverter::toString(playerNumber)));
    colorBar[playerNumber]->setSize(CEGUI::UVector2(CEGUI::UDim(0.075, 0), CEGUI::UDim(0.04, 0)));
	colorBar[playerNumber]->setPosition(CEGUI::UVector2(CEGUI::UDim(xOffset + 0.04, 0), CEGUI::UDim(yOffset + 0.04, 0)));
	CEGUISheet->addChildWindow(colorBar[playerNumber]);

	/////////////////
	//Speed BAR
	speedBar[playerNumber] =  static_cast<CEGUI::ProgressBar*> (CEGUIWin->createWindow("TaharezLook/ProgressBar", "singlePlayer/speedBar"+ StringConverter::toString(playerNumber)));
    speedBar[playerNumber]->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
	
	speedBar[playerNumber]->setPosition(CEGUI::UVector2(CEGUI::UDim(xOffset+0.5-0.15, 0), CEGUI::UDim(yOffset, 0)));
	speedBar[playerNumber]->setVerticalAlignment(CEGUI::VA_BOTTOM);
	CEGUISheet->addChildWindow(speedBar[playerNumber]);

	/////////////////
	//Boost Text
	boostText[playerNumber] = CEGUIWin->createWindow("TaharezLook/StaticText", "singlePlayer/boostText" + StringConverter::toString(playerNumber));
	boostText[playerNumber]->setText("Boost");	
	boostText[playerNumber]->setFont(((CEGUI::utf8*)"BlueHighway-10"));
    boostText[playerNumber]->setSize(CEGUI::UVector2(CEGUI::UDim(0.04, 0), CEGUI::UDim(0.04, 0)));
	boostText[playerNumber]->setPosition(CEGUI::UVector2(CEGUI::UDim(xOffset + 0.00, 0), CEGUI::UDim(yOffset + 0.0, 0)));
	CEGUISheet->addChildWindow(boostText[playerNumber]);

	/////////////////
	//Color Text
	colorText[playerNumber] = CEGUIWin->createWindow("TaharezLook/StaticText", "singlePlayer/colorText" + StringConverter::toString(playerNumber));
	colorText[playerNumber]->setText("Color");	
	colorText[playerNumber]->setFont(((CEGUI::utf8*)"BlueHighway-10"));
    colorText[playerNumber]->setSize(CEGUI::UVector2(CEGUI::UDim(0.04, 0), CEGUI::UDim(0.04, 0)));
	colorText[playerNumber]->setPosition(CEGUI::UVector2(CEGUI::UDim(xOffset + 0.00, 0), CEGUI::UDim(yOffset + 0.04, 0)));
	CEGUISheet->addChildWindow(colorText[playerNumber]);

	/////////////////
	//Speed Text
	speedText[playerNumber] = CEGUIWin->createWindow("TaharezLook/StaticText", "singlePlayer/speedText" + StringConverter::toString(playerNumber));
	speedText[playerNumber]->setText("Speed");	
	speedText[playerNumber]->setFont(((CEGUI::utf8*)"BlueHighway-10"));
    speedText[playerNumber]->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.035, 0)));
	speedText[playerNumber]->setVerticalAlignment(CEGUI::VA_BOTTOM);
	speedText[playerNumber]->setPosition(CEGUI::UVector2(CEGUI::UDim(xOffset+0.5-0.15, 0), CEGUI::UDim(yOffset-0.052, 0)));
	speedText[playerNumber]->setAlpha(0.8);
	CEGUISheet->addChildWindow(speedText[playerNumber]);

	/////////////////
	//InfoBox
	infoBox[playerNumber] = CEGUIWin->createWindow("TaharezLook/StaticText", "singlePlayer/infoBox" + StringConverter::toString(playerNumber));
	infoBox[playerNumber]->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.1, 0)));
	infoBox[playerNumber]->setVerticalAlignment(CEGUI::VA_BOTTOM);
	infoBox[playerNumber]->setPosition(CEGUI::UVector2(CEGUI::UDim(xOffset + 0.15 + 0.0, 0), CEGUI::UDim(yOffset + 0.0, 0)));
	infoBox[playerNumber]->setVisible(false);
	CEGUISheet->addChildWindow(infoBox[playerNumber]);

	
	/////////////////
	//centerTextWindow
	centerTextWindow[playerNumber] = CEGUIWin->createWindow("TaharezLook/StaticText", "singlePlayer/centerTextWindow"+ StringConverter::toString(playerNumber));
	centerTextWindow[playerNumber]->setText("");
	centerTextWindow[playerNumber]->setAlpha(0.8);
	centerTextWindow[playerNumber]->setFont(((CEGUI::utf8*)"BlueHighway-10"));
	centerTextWindow[playerNumber]->setVerticalAlignment(CEGUI::VA_CENTRE);
    centerTextWindow[playerNumber]->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.25, 0)));
	centerTextWindow[playerNumber]->setPosition(CEGUI::UVector2(CEGUI::UDim(xOffset + 0.15, 0), CEGUI::UDim(yOffset, 0)));
	centerTextWindow[playerNumber]->setVisible(false);
	CEGUISheet->addChildWindow(centerTextWindow[playerNumber]);
}
//--------------------------------------------------------------
void MultiPlayerRace::setupEventHandler(void)
{
	
}
//--------------------------------------------------------------
void MultiPlayerRace::createCamera(void)
{
	
	dataManager->window->resize(dataManager->window->getWidth()*2,dataManager->window->getHeight());
	dataManager->window->reposition(0,0);
    // Create the camera
	camera1 = dataManager->sceneManager->createCamera("Player1");
	camera1->setPosition(0,500,0);
    camera1->lookAt(Vector3(0,0,-300));
    camera1->setNearClipDistance(5);

	// Create the camera
    camera2 = dataManager->sceneManager->createCamera("player2");
	camera2->setPosition(0,500,0);
    camera2->lookAt(Vector3(0,0,-300));
    camera2->setNearClipDistance(5);

	// Create one viewport, entire window
	vp[0] = dataManager->window->addViewport(camera1,1);
    vp[0]->setBackgroundColour( ColourValue(0,0,0) );
	vp[0]->setDimensions(0,0,0.5,1);
	vp[0]->setOverlaysEnabled(false);
    // Alter the camera aspect ratio to match the viewport
    camera1->setAspectRatio( Real(vp[0]->getActualWidth()) / Real( vp[0]->getActualHeight() ) );
	Ogre::CompositorManager::getSingleton().addCompositor(vp[0], "Radial Blur");

	// Create one viewport, entire window
	vp[1] = dataManager->window->addViewport(camera2,2);
    vp[1]->setBackgroundColour( ColourValue(0,0,0) );
	vp[1]->setDimensions(0.5,0,0.5,1);
	vp[1]->setOverlaysEnabled(false);
	Ogre::CompositorManager::getSingleton().addCompositor(vp[1], "Radial Blur");
	//vp2->setOverlaysEnabled(false);

    // Alter the camera aspect ratio to match the viewport
    camera2->setAspectRatio( Real(vp[1]->getActualWidth()) / Real( vp[1]->getActualHeight() ) );

	// Create one viewport, entire window
	camera3 = dataManager->sceneManager->createCamera("guiCamera");
	camera3->setPosition(Vector3(0,-100000,0));
	camera3->lookAt(Vector3(0,-1000000,0));
	

	Viewport* vp3 = dataManager->window->addViewport(camera3,3);
	//vp3->setClearEveryFrame(false);
	
    vp3->setBackgroundColour( ColourValue(0,0,0) );
	vp3->setDimensions(0,0,1,1);
	vp3->setClearEveryFrame(false);
	vp3->setSkiesEnabled(false);

	camera3->setAspectRatio( Real(vp3->getActualWidth()) / Real( vp3->getActualHeight() ) );

}
//--------------------------------------------------------------
bool MultiPlayerRace::frameStarted(const FrameEvent& evt)
{
	//Manager Sounde of Jet
	float speedProgress = f14Player[0]->getSpeedProgress();
	if(speedProgress < 0.3)
		speedProgress = 0.3;
	dataManager->channelEffectsPlayer1->setVolume(speedProgress);

	speedProgress = f14Player[1]->getSpeedProgress();
	if(speedProgress < 0.3)
		speedProgress = 0.3;
	dataManager->channelEffectsPlayer2->setVolume(speedProgress);

	switch(currentState)
	{
		case F14FIGHTER::MULTIPLAYERRACE::COUNTDOWN:
			updateCountdown(evt);
			break;
		case F14FIGHTER::MULTIPLAYERRACE::GAME_IS_RUNNING:
			updateGameIsRunning(evt);
			break;
		case F14FIGHTER::MULTIPLAYERRACE::GAME_END:
			updateGameEnd(evt);
			break;
		case F14FIGHTER::MULTIPLAYERRACE::WIN:
			updateGameIsRunning(evt);
			break;
	}
	
	handleTorusRotation(evt.timeSinceLastFrame);
	handleDeleteDestroyedTorus(evt.timeSinceLastFrame);
	handleF14Collision();
	handleToggleValues(evt.timeSinceLastFrame);
	updateGUI();

	return true;
}
void MultiPlayerRace::updateGUI()
{
	for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		infoBox[i]->setAlpha(timeUntilNextToggleInfoboxPlayer[i]/3);
	}
}
//--------------------------------------------------------------
void MultiPlayerRace::handleToggleValues(float dt)
{
	for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		if (timeUntilNextToggleInfoboxPlayer[i] >= 0)
			timeUntilNextToggleInfoboxPlayer[i] -= dt;
	}
}
//--------------------------------------------------------------
void MultiPlayerRace::handleF14Collision()
{
	//handle collision f14 0 and f14 1

	const AxisAlignedBox f140BoundingBox = f14Player[0]->sceneNode->_getWorldAABB();
	const AxisAlignedBox f141BoundingBox = f14Player[1]->sceneNode->_getWorldAABB();

	/////////////////////////////////
	//F14 - F14
	if(f140BoundingBox.intersects(f141BoundingBox))
	{
		for(int i = 0; i < NUMBER_OF_PLAYERS;i++)
		{
			f14Player[i]->letF14Die();
			f14Player[i]->impuls = Vector3(0,0,0);
			Vector3 pos = f14Player[i]->sceneNode->getPosition();
			Vector3 direction = f14Player[i]->getDirection();
			pos -= direction * 100;
			f14Player[i]->sceneNode->setPosition(pos.x,pos.y,  pos.z);
		}
	}
}
//--------------------------------------------------------------
void MultiPlayerRace::handleTorusRotation(float dt)
{
	//rotate Torus
	for(unsigned int i = 0; i < torus.size(); i++)
	{
		torus[i]->moveTorus(dt);

		//MOVE not alive Toruses in direction of f14
		if(!torus[i]->alive)
		{
			torus[i]->sceneNode->translate( f14Player[0]->translationVector );
		}
	}
}
//--------------------------------------------------------------
void MultiPlayerRace::handleDeleteDestroyedTorus(float dt)
{
	//delete Destroyed Toruses
	std::vector<Torus*>::iterator torusIterator = torus.begin();
    while(torusIterator != torus.end())
	{
		if((*torusIterator)->torusDestroyed)
		{	
			delete *torusIterator;
			torusIterator = torus.erase(torusIterator);
			continue;
		}
		++torusIterator;

	} 
}
//--------------------------------------------------------------
bool MultiPlayerRace::frameEnded(const FrameEvent& evt)
{
	//first frameended is from previous state
	if(timeStampStartMultiPlayer == -100)
	{	
		timeStampStartMultiPlayer= F14FIGHTER::TIMER::NOT_INITIALIZED;
		return true;
	}
	if(timeStampStartMultiPlayer == F14FIGHTER::TIMER::NOT_INITIALIZED)
	{
		int countdownValue = settingManager.getInt("countdownBeforeStart");
		timeStampStartMultiPlayer = dataManager->myTimer.getElapsedTime() + countdownValue;
	}

	//timer
	elapsedTime = dataManager->myTimer.getElapsedTime() - timeStampStartMultiPlayer;

	return true;
}
//--------------------------------------------------------------
void MultiPlayerRace::updateCountdown(const FrameEvent& evt)
{
	for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		centerTextWindow[i]->setVisible(true);
	
		//COUNTDOWN WINDOW
		centerTextWindow[i]->setText("Game starts in:\n\n\n" + StringConverter::toString((int)fabs(elapsedTime-1)));
	}
	if(elapsedTime >= 0)
	{
		dataManager->system->playSound(FMOD_CHANNEL_FREE, dataManager->jetSoundStartup, false, &dataManager->channelExplotion);	
		for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
		{
			centerTextWindow[i]->setVisible(false);
		}
		currentState = F14FIGHTER::SINGLEPLAYER::GAME_IS_RUNNING;
	}
}
//--------------------------------------------------------------
void MultiPlayerRace::updateGameIsRunning(const FrameEvent& evt)
{
	for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		f14Player[i]->moveF14(evt.timeSinceLastFrame);
		
		handleCollisionDetection(i,evt);
		handleTerrainCollision(i,evt);
		handleRespawn(i);
	}
	
	updateGui(evt);

	
}
//--------------------------------------------------------------
void MultiPlayerRace::updateGameEnd(const FrameEvent& evt)
{
	for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		f14Player[i]->moveF14(evt.timeSinceLastFrame);
		
		handleCollisionDetection(i,evt);
	}
	
}
//--------------------------------------------------------------
void MultiPlayerRace::updateGui(const FrameEvent& evt)
{
	for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		////Update progress Bars
		speedBar[i]->setProgress(f14Player[i]->getSpeedProgress());	
		boostBar[i]->setProgress(f14Player[i]->getBoostProgress());
		colorBar[i]->setProgress(f14Player[i]->getColorProgress());
		speedText[i]->setText(StringConverter::toString(f14Player[i]->speedRaiseFactor*100) + "% max Speed");
	}
}
//--------------------------------------------------------------
bool MultiPlayerRace::processUnbufferedKeyInput(const FrameEvent& evt, OIS::Keyboard* mKeyboard)
{
	for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		if(dataManager->controller == F14FIGHTER::Controller::KEYBOARD)
		{
			switch(currentState)
			{
				case F14FIGHTER::MULTIPLAYERRACE::COUNTDOWN:
					break;
				case F14FIGHTER::MULTIPLAYERRACE::GAME_IS_RUNNING:
					f14Player[i]->f14Controlls->updateKeyboardControlls(mKeyboard,evt.timeSinceLastFrame, vp[i]);
				break;
			case F14FIGHTER::MULTIPLAYERRACE::WIN:
					break;
			}	
		}
	}
	//MENU
	if( mKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		dataManager->window->resize(dataManager->window->getWidth()/2,dataManager->window->getHeight());
		stateManager->createState(new LoadingScreen(&dataManager->stateManager, F14FIGHTER::MENU::MENU));
	}
	return true;
}
//--------------------------------------------------------------
bool MultiPlayerRace::processUnbufferedXBOXControllerInput(const FrameEvent& evt)
{
	if(dataManager->controller == F14FIGHTER::Controller::XBOXCONTROLLER)
	{
		if(currentState == F14FIGHTER::MULTIPLAYERRACE::GAME_IS_RUNNING)
		{
			f14Player[0]->f14Controlls->updateXboxControlls(evt.timeSinceLastFrame,vp[0]);
			f14Player[1]->f14Controlls->updateXboxControlls(evt.timeSinceLastFrame,vp[1]);
		}
		
	}
	//MENU
	if( xboxDataManager->controller[0].startPressed || xboxDataManager->controller[1].startPressed)
	{
		dataManager->window->resize(dataManager->window->getWidth()/2,dataManager->window->getHeight());
		stateManager->createState(new LoadingScreen(&dataManager->stateManager, F14FIGHTER::MENU::MENU));
	}
	return true;
}

//--------------------------------------------------------------
bool MultiPlayerRace::processUnbufferedMouseInput(const FrameEvent& evt, OIS::Mouse* mMouse, const OIS::MouseState* ms)
{
	
	return true;

}
//--------------------------------------------------------------
void MultiPlayerRace::handleRespawn(int player)
{
	
	if(f14Player[player]->f14Destroyed)
	{
		dataManager->system->playSound(FMOD_CHANNEL_FREE, dataManager->jetSoundStartup, false, &dataManager->channelExplotion);	
		f14Player[player]->sceneNode->setVisible(true);
		f14Player[player]->sceneNode->resetOrientation();
		
		Vector3 newPosition = f14Player[player]->sceneNode->getPosition();
		if(player == 1)
			newPosition.x = 1000;
		else
			newPosition.x = 3000;

		newPosition.y = 1000;

		f14Player[player]->sceneNode->setPosition(newPosition);
		f14Player[player]->impuls = settingManager.getVector3("respawnStartImpuls");
		f14Player[player]->alive=true;
		f14Player[player]->f14Destroyed=false;
		
	}	
}
//--------------------------------------------------------------
void MultiPlayerRace::handleCollisionDetection(int player, const FrameEvent& evt)
{
	
	handleF14TorusCollision(player);
	handleF14RunwayCollision(player);
	handleF14WorldGeometryCollision(player);
	handleF14FinishCollision(player);
	
}
//--------------------------------------------------------------
void MultiPlayerRace::handleF14TorusCollision(int player)
{
	const AxisAlignedBox f14BoundingBox = f14Player[player]->sceneNode->_getWorldAABB();

	/////////////////////////////////
	//F14 - TORUS COLLISION DETECTION
	for(unsigned int i = 0; i < torus.size(); i++)
	{
		if(f14BoundingBox.intersects(torus[i]->sceneNode->_getWorldAABB()))
		{	
			if(torus[i]->color == f14Player[player]->activeEmitter)
				handleTorusCollision(player, torus[i], true);
			else
				handleTorusCollision(player, torus[i], false);
		}
	}
}
//--------------------------------------------------------------
void MultiPlayerRace::handleF14WorldGeometryCollision(int player)
{
	///////////////////////
	//F14 - World Geometry
	static Ray updateRay;
	for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		updateRay.setOrigin(f14Player[i]->sceneNode->getPosition());
		updateRay.setDirection(Vector3::UNIT_Y);
		raySceneQuery->setRay(updateRay);
		RaySceneQueryResult& qryResult = raySceneQuery->execute();
		RaySceneQueryResult::iterator it = qryResult.begin();
		if (it != qryResult.end() && it->worldFragment)
		{
			
			f14Player[i]->letF14Die();
			Vector3 pos = f14Player[i]->sceneNode->getPosition();
			f14Player[i]->impuls = Vector3(0,0,0);
			//f14Player[i]->lockGravity(true);
			f14Player[i]->sceneNode->setPosition(pos.x,it->worldFragment->singleIntersection.y + 200,  pos.z);
		}	
	}
}
//--------------------------------------------------------------
void MultiPlayerRace::handleF14RunwayCollision(int player)
{
	/////////////////////////////////
	//F14 - RUNWAY
	if(f14Player[player]->currentPhase == F14FIGHTER::F14::START_PHASE)
	{
		
		if(f14Player[player]->getSpeedProgress() > 0.3)
		{
			f14Player[player]->currentPhase = F14FIGHTER::F14::FLYING_PHASE;
		}
		/////////////////////////////////
		//F14 - Runway Plane START
		if(CollisionHandler::checkBottomCollision(f14Player[player]->sceneNode->_getWorldAABB(), runWay->sceneNodePlane->_getWorldAABB()))
		{
			f14Player[player]->impuls.y = 0;
			f14Player[player]->impuls.x = 0;									//otherwise f14 tries to go left after crash and respawn
			Vector3 newPosition = f14Player[player]->sceneNode->getPosition();
			newPosition.y = runWay->sceneNode->getPosition().y + runWay->sceneNodePlane->getPosition().y + runWay->settingManager.getFloat("runWayAdjustHeight");
			f14Player[player]->sceneNode->setPosition(newPosition);
		}
		else
		{
			f14Player[player]->currentPhase = F14FIGHTER::F14::FLYING_PHASE;
		}
	}
	else if(f14Player[player]->currentPhase == F14FIGHTER::F14::FLYING_PHASE)
	{
		while(true)
		{
			if(CollisionHandler::checkBottomCollision(f14Player[player]->sceneNode->_getWorldAABB(), runWay->sceneNodePlane->_getWorldAABB()))
			{
				f14Player[player]->sceneNode->translate(0,0.1,0);
				f14Player[player]->sceneNode->_update(true,false);
			}
			else
			{
				break;
			}
		}
	}
}

//--------------------------------------------------------------
void MultiPlayerRace::handleTerrainCollision(int player, const FrameEvent& evt)
{
	const AxisAlignedBox f14BoundingBox1 = f14Player[0]->sceneNode->_getWorldAABB();
	const AxisAlignedBox f14BoundingBox2 = f14Player[1]->sceneNode->_getWorldAABB();

	const AxisAlignedBox f14BoundingBox = f14Player[player]->sceneNode->_getWorldAABB();
		
	for(int i = 0; i < 2; i++)
	{
		
		if(f14BoundingBox.intersects(terrainCubeBoundingSceneNode[i]->_getWorldAABB()))
		{
			f14Player[player]->letF14Die();
			f14Player[player]->impuls = Vector3(0,0,0);

			Vector3 pos = f14Player[player]->sceneNode->getPosition();
			Vector3 direction = f14Player[player]->getDirection();
			pos -= direction * 100;
			f14Player[player]->sceneNode->setPosition(pos.x,pos.y,  pos.z);
		}
	}

}

//--------------------------------------------------------------
void MultiPlayerRace::handleTorusCollision(int player, Torus* torus, bool extra)
{
	if(F14FIGHTER::MULTIPLAYERRACE::GAME_IS_RUNNING)
	{
		int multiplikator = 1;
		if(torus->alive)
		{
			torus->letTorusDie();
			if(extra)
				multiplikator = 2;
			
			switch(torus->color)
			{
				case F14FIGHTER::TORUS::BLUE:
					infoBox[player]->setText(StringConverter::toString(multiplikator) + "x Boost\n+ " );			
					infoBox[player]->setVisible(true);
					timeUntilNextToggleInfoboxPlayer[player] = 3;
					f14Player[player]->addBoost(multiplikator*10);
					break;
			
				case F14FIGHTER::TORUS::RED:
					infoBox[player]->setText(StringConverter::toString(multiplikator) + "x Color\n+ ");		
					infoBox[player]->setVisible(true);
					timeUntilNextToggleInfoboxPlayer[player] = 3;
					f14Player[player]->addColor(multiplikator*10);

					break;
			
				case F14FIGHTER::TORUS::GREEN:
					infoBox[player]->setText(StringConverter::toString(multiplikator) + "x Max Speed\n+ ");	
					infoBox[player]->setVisible(true);
					timeUntilNextToggleInfoboxPlayer[player] = 3;
					f14Player[player]->raiseMaxSpeed(multiplikator*0.1);
					break;
			
				case F14FIGHTER::TORUS::YELLOW:
					infoBox[player]->setText( "+ " + StringConverter::toString(multiplikator*2) + " " );	
					infoBox[player]->setVisible(true);
					timeUntilNextToggleInfoboxPlayer[player] = 3;
					break;
			}
		}
	}
}
//--------------------------------------------------------------
void MultiPlayerRace::handleF14FinishCollision(int player)
{
	if(winner < 0)
	{
		const AxisAlignedBox f14BoundingBox = f14Player[player]->sceneNode->_getWorldAABB();
		if(f14BoundingBox.intersects(finish->sceneNode->_getWorldAABB()))
		{
			currentState = F14FIGHTER::MULTIPLAYERRACE::WIN;
		//	timeStampStopSinglePlayer = dataManager->myTimer.getElapsedTime();
			winner = player;

			centerTextWindow[0]->setVisible(true);
			centerTextWindow[1]->setVisible(true);
			if(player == 0)
			{
				centerTextWindow[0]->setText("WON\n\nPress Start");
				centerTextWindow[1]->setText("LOSE\n\n\nPress Start");
			}
			else
			{
				centerTextWindow[0]->setText("LOSE\n\n\nPress Start");
				centerTextWindow[1]->setText("WON\n\nPress Start");		
			}
		}
	}
	
}