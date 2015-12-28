#include "SinglePlayer.h"
#include "../../DataManager/DataManager.h"

//--------------------------------------------------------------
SinglePlayer::SinglePlayer(StateManager *stateManager)
:	State(stateManager), f14(0), currentState(F14FIGHTER::SINGLEPLAYER::COUNTDOWN), finish(0),	torus(0), raySceneQuery(0),
	CEGUIWin(0), CEGUISheet(0), boostBar(0), colorBar(0), speedBar(0), boostText(0), colorText(0), speedText(0), infoBox(0), 
	timeWindow(0), highScore(0), centerTextWindow(0),timeUntilNextToggleRed(0),timeUntilNextToggleYellow(0),timeUntilNextToggleBlue(0),
	timeUntilNextToggleGreen(0), timeUntilNextToggleInfobox(0), elapsedTime(-100), timeStampStartSinglePlayer(-100), collectedTime(0),
	isHighscoreSaved(false), timeStampStopSinglePlayer(F14FIGHTER::TIMER::NOT_INITIALIZED),runWay(0)
{
	std::cout << "########################" << std::endl;
	std::cout << "# SinglePlayer created #" << std::endl;
	std::cout << "########################" << std::endl;	
	settingManager.loadFile("singlePlayerSettings.cfg");

}

//--------------------------------------------------------------
SinglePlayer::~SinglePlayer()
{
	delete f14;
	delete finish;
	//delete Vector
	std::vector<Torus*>::iterator torusIterator = torus.begin();
	
    while(torusIterator != torus.end())
	{
        delete *torusIterator;
        torusIterator = torus.erase(torusIterator);
        continue;
        ++torusIterator;
    } 
	Torus::torusNumber = 0;
	delete raySceneQuery;
	

	CEGUIWin->destroyAllWindows();

	if(boostBar)
	{
		boostBar->removeAllEvents();
		boostBar->destroy();
		boostBar = 0;
	}
	if(colorBar)
	{
		colorBar->removeAllEvents();
		colorBar->destroy();
		colorBar = 0;
	}
	if(timeWindow)
	{
		timeWindow->removeAllEvents();
		timeWindow->destroy();
		timeWindow = 0;
	}
	if(timeWindow)
	{
		timeWindow->removeAllEvents();
		timeWindow->destroy();
		timeWindow = 0;
	}
	if(highScore)
	{
		centerTextWindow->removeAllEvents();
		centerTextWindow->destroy();
		centerTextWindow = 0;
	}
	dataManager->singlePlayerStarted = false;
	Ogre::CompositorManager::getSingleton().setCompositorEnabled(dataManager->window->getViewport(0), "Radial Blur", false);
	dataManager->channel->setPaused(true);
	dataManager->channelEffectsPlayer1->setPaused(true);
	dataManager->channelEffectsPlayer2->setPaused(true);
	dataManager->releaseFMODSystem();
}
//--------------------------------------------------------------
void SinglePlayer::setup(void)
{
	
	
}
//--------------------------------------------------------------
void SinglePlayer::createScene(void)
{
	dataManager->window->reposition(0,0);
	dataManager->settingManagerSinglePlayerHighscore.writeHighscoreToConfigFile("singlePlayerHighscore.cfg");
	//##############################//
	//# WATER && TERRAIN && SKYBOX #//
	//##############################//
	createHydrax();
	
//	dataManager->sceneManager->setWorldGeometry(settingManager.getString("worldGeometry"));
	dataManager->sceneManager->setSkyBox(true, settingManager.getString("skyBox"));

	//###############//
	//# F14 FIGHTER #//
	//###############//
	f14 = new F14(0,settingManager.getVector3("f14StartPosition"), dataManager->camera, "f14_mat1", settingManager.getVector3("finishPosition") - settingManager.getVector3("startPosition"));
	

	//##########//
	//# FINISH #//
	//##########//
	finish = new Finish(settingManager.getVector3("finishPosition"));
	Vector3 tempVec = f14->sceneNode->getPosition() + f14->getDirection()*3500;
	tempVec.y = 200;
	runWay = new RunWay(Vector3(tempVec), Vector3(6,6,6));	
	runWay->sceneNode->yaw(Degree(180));
	
	f14->sceneNode->yaw(Degree(settingManager.getFloat("f14StartYaw")),Node::TS_LOCAL);

	//#########//
	//# TORUS #//
	//#########//
	Torus* newTorus = 0;
	Vector3 torusPathDirection = settingManager.getVector3("finishPosition") - settingManager.getVector3("startPosition");
	torusPathDirection /= settingManager.getInt("torusCount") + 1;
	
	Vector3	shiftValues = settingManager.getVector3("torusShiftPosition");

	for(int i = 0; i < settingManager.getInt("torusCount"); i++)
	{
		Vector3 positionShiftVector = Vector3(rand()%(int)shiftValues.x,rand()%(int)shiftValues.y,rand()%(int)shiftValues.x);

		Vector3 tempVec = settingManager.getVector3("startPosition") + (torusPathDirection * (i+1));
		tempVec.y = settingManager.getVector3("startPosition").y;
		tempVec += positionShiftVector;
	
		float colorProbability = ((float)rand() / RAND_MAX);
		int color = 0;
		
		//GREEN
		if(colorProbability > settingManager.getFloat("greenDegreeOfProbability"))
			color = F14FIGHTER::TORUS::GREEN;
		//RED
		else if(colorProbability > settingManager.getFloat("redDegreeOfProbability"))
			color = F14FIGHTER::TORUS::RED;
		//YELLOW
		else if(colorProbability > settingManager.getFloat("yellowDegreeOfProbability"))
			color = F14FIGHTER::TORUS::YELLOW;
		//BLUE
		else
			color = F14FIGHTER::TORUS::BLUE;

		newTorus = new Torus(tempVec,color);
		newTorus->sceneNode->setScale(Vector3(50,50,50));
		torus.push_back(newTorus);
	}
	//PALMS
	for(int i = 0; i < F14FIGHTER::Palms::NUMBER_OF_PALMS; i++)
	{
		Entity* entity = dataManager->sceneManager->createEntity("palm" + StringConverter::toString(i), "Palm.mesh"); 
		SceneNode* node = dataManager->sceneManager->getRootSceneNode()->createChildSceneNode();
		node->attachObject(entity); //attaching to level node
		node->setPosition(F14FIGHTER::Palms::PALMS[i]);
		node->pitch(Degree(-90));
		node->setScale(Vector3(3,3,3));
	}
	raySceneQuery = dataManager->sceneManager->createRayQuery( Ray(f14->sceneNode->getPosition(), Vector3::NEGATIVE_UNIT_Y));
	
		/*Entity* terrainEntity= dataManager->sceneManager->createEntity("terrain", "terrain1.mesh");
	terrainEsntity->setMaterialName("Island");
	SceneNode* terrainSceneNode = dataManager->sceneManager->getRootSceneNode()->createChildSceneNode();
	terrainSceneNode->attachObject(terrainEntity);
	Vector3 position = settingManager.getVector3("startPosition") - Vector3(400,400,0);
	terrainSceneNode->setPosition(position);
	terrainSceneNode->setScale(Vector3(2,1,2));
	*/

	Ogre::CompositorManager::getSingleton().addCompositor(dataManager->window->getViewport(0), "Radial Blur");
	dataManager->createFMODSystem();
	dataManager->system->playSound(FMOD_CHANNEL_FREE, dataManager->backgroundMusicSinglePlayer, false, &dataManager->channel);
	dataManager->channel->setVolume(0.2);
	dataManager->system->playSound(FMOD_CHANNEL_FREE, dataManager->jetSound, false, &dataManager->channelEffectsPlayer1);
	dataManager->channelEffectsPlayer1->setVolume(0.3);

}
//--------------------------------------------------------------
void SinglePlayer::createLights(void)
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
void SinglePlayer::setupGUI(void)
{
	//WINDOW AND SHEET FOR DataManagerMenu
	// Quit button
	CEGUIWin = CEGUI::WindowManager::getSingletonPtr();
	CEGUISheet = CEGUIWin->createWindow("DefaultGUISheet", "CEGUIDemo/Sheet");

	/////////////////
	//BOOST BAR
    boostBar = static_cast<CEGUI::ProgressBar*> (CEGUIWin->createWindow("TaharezLook/AlternateProgressBar", "singlePlayer/boostBar"));
    boostBar->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
	boostBar->setPosition(CEGUI::UVector2(CEGUI::UDim(0.08, 0), CEGUI::UDim(0, 0)));
	CEGUISheet->addChildWindow(boostBar);
	
	/////////////////
	//Color BAR
	colorBar = static_cast<CEGUI::ProgressBar*> (CEGUIWin->createWindow("TaharezLook/AlternateProgressBar", "singlePlayer/colorBar"));
    colorBar->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
	colorBar->setPosition(CEGUI::UVector2(CEGUI::UDim(0.08, 0), CEGUI::UDim(0.05, 0)));
	CEGUISheet->addChildWindow(colorBar);

	/////////////////
	//Speed BAR
	speedBar =  static_cast<CEGUI::ProgressBar*> (CEGUIWin->createWindow("TaharezLook/ProgressBar", "singlePlayer/speedBar"));
    speedBar->setSize(CEGUI::UVector2(CEGUI::UDim(0.3, 0), CEGUI::UDim(0.05, 0)));
	
	speedBar->setHorizontalAlignment(CEGUI::HA_RIGHT);
	speedBar->setVerticalAlignment(CEGUI::VA_BOTTOM);
	CEGUISheet->addChildWindow(speedBar);
	
	/////////////////
	//Boost Text
	boostText = CEGUIWin->createWindow("TaharezLook/StaticText", "singlePlayer/boostText");
	boostText->setText("Boost");	
    boostText->setSize(CEGUI::UVector2(CEGUI::UDim(0.08, 0), CEGUI::UDim(0.05, 0)));
	boostText->setPosition(CEGUI::UVector2(CEGUI::UDim(0.00, 0), CEGUI::UDim(0.0, 0)));
	CEGUISheet->addChildWindow(boostText);
	
	/////////////////
	//Color Text
	colorText = CEGUIWin->createWindow("TaharezLook/StaticText", "singlePlayer/colorText");
	colorText->setText("Color");	
    colorText->setSize(CEGUI::UVector2(CEGUI::UDim(0.08, 0), CEGUI::UDim(0.05, 0)));
	colorText->setPosition(CEGUI::UVector2(CEGUI::UDim(0.00, 0), CEGUI::UDim(0.05, 0)));
	CEGUISheet->addChildWindow(colorText);

	/////////////////
	//Speed Text
	speedText = CEGUIWin->createWindow("TaharezLook/StaticText", "singlePlayer/speedText");
	speedText->setText("Speed");	
	speedText->setFont(((CEGUI::utf8*)"BlueHighway-10"));
    speedText->setSize(CEGUI::UVector2(CEGUI::UDim(0.3, 0), CEGUI::UDim(0.035, 0)));
	speedText->setVerticalAlignment(CEGUI::VA_BOTTOM);
	speedText->setHorizontalAlignment(CEGUI::HA_RIGHT);
	speedText->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(-0.052, 0)));
	speedText->setAlpha(0.8);
	CEGUISheet->addChildWindow(speedText);

	/////////////////
	//InfoBox
	infoBox = CEGUIWin->createWindow("TaharezLook/StaticText", "singlePlayer/infoBox");
	infoBox->setSize(CEGUI::UVector2(CEGUI::UDim(0.4, 0), CEGUI::UDim(0.1, 0)));
	infoBox->setHorizontalAlignment(CEGUI::HA_CENTRE);
	infoBox->setVerticalAlignment(CEGUI::VA_BOTTOM);
	infoBox->setVisible(false);
	CEGUISheet->addChildWindow(infoBox);

	/////////////////
	//timeWindow
	timeWindow = CEGUIWin->createWindow("TaharezLook/StaticText", "singlePlayer/timeWindow");
	timeWindow->setAlpha(0.8);	
    timeWindow->setSize(CEGUI::UVector2(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.1, 0)));
	timeWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0.8, 0), CEGUI::UDim(0.0, 0)));
	CEGUISheet->addChildWindow(timeWindow);
	
	//TIME WINDOW SET 0
	timeWindow->setText("Total         " + MyTimer::getMinutesAndSecondsFormated(0) + "\n" +
															 "Collected  -"+MyTimer::getMinutesAndSecondsFormated(0) + "\n" +
															 "Highscore   " + MyTimer::getMinutesAndSecondsFormated(0));

	/////////////////
	//highScore
	highScore = CEGUIWin->createWindow("TaharezLook/StaticText", "singlePlayer/highScore");
    highScore->setSize(CEGUI::UVector2(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.2, 0)));
	highScore->setPosition(CEGUI::UVector2(CEGUI::UDim(0.85, 0), CEGUI::UDim(0.1, 0)));
	highScore->setAlpha(0.6);	
	CEGUISheet->addChildWindow(highScore);

	//set Highscore text
	std::string highscoreString ="";
	for(int i = 0; i < 3; i++)
	{
		if(i < dataManager->settingManagerSinglePlayerHighscore.getNumberOfHighscoreEntries())
		{
			highscoreString += StringConverter::toString(i+1) + ". " + dataManager->settingManagerSinglePlayerHighscore.getStringEntry(i) + "\n" + MyTimer::getMinutesAndSecondsFormated(dataManager->settingManagerSinglePlayerHighscore.getFloatEntry(i)) + "\n"; 
		}
	}
	highScore->setText("HighScore\n" + highscoreString);

	/////////////////
	//centerTextWindow
	centerTextWindow = CEGUIWin->createWindow("TaharezLook/StaticText", "singlePlayer/centerTextWindow");
	centerTextWindow->setText("GAME OVER");
	centerTextWindow->setAlpha(0.8);
	centerTextWindow->setHorizontalAlignment(CEGUI::HA_CENTRE);
	centerTextWindow->setVerticalAlignment(CEGUI::VA_CENTRE);
    centerTextWindow->setSize(CEGUI::UVector2(CEGUI::UDim(0.4, 0), CEGUI::UDim(0.5, 0)));
	centerTextWindow->setVisible(false);
	
	CEGUISheet->addChildWindow(centerTextWindow);

	dataManager->CEGUISystem->setGUISheet(CEGUISheet);	
	CEGUISheet->show();	
	ceguiKeyboard.setupGUI(0.2,0.5);
}
//--------------------------------------------------------------
void SinglePlayer::setupEventHandler(void)
{
	ceguiKeyboard.setupEventHandler();
}

//--------------------------------------------------------------
bool SinglePlayer::frameStarted(const FrameEvent& evt)
{	
	//Manager Sounde of Jet
	float speedProgress = f14->getSpeedProgress();
	if(speedProgress < 0.3)
		speedProgress = 0.3;
	dataManager->channelEffectsPlayer1->setVolume(speedProgress);

	switch(currentState)
	{
		case F14FIGHTER::SINGLEPLAYER::COUNTDOWN:
			//if Countdown is over -> start game and set centerTextWindow invisible
			if(elapsedTime >= 0)
			{
				centerTextWindow->setVisible(false);
				dataManager->system->playSound(FMOD_CHANNEL_FREE, dataManager->jetSoundStartup, false, &dataManager->channelExplotion);	
				currentState = F14FIGHTER::SINGLEPLAYER::GAME_IS_RUNNING;
			}
			break;
		case F14FIGHTER::SINGLEPLAYER::GAME_IS_RUNNING:
			updateGameIsRunning(evt);
			break;
		case F14FIGHTER::SINGLEPLAYER::GAME_OVER:
			break;
		case F14FIGHTER::SINGLEPLAYER::WIN:
			updateGameIsWon(evt);
			
			break;
	}
	
	handleTorusRotation(evt.timeSinceLastFrame);
	handleDeleteDestroyedTorus(evt.timeSinceLastFrame);

	updateGUI(evt.timeSinceLastFrame);

	return true;
}
//--------------------------------------------------------------
void SinglePlayer::updateGUI(float dt)
{
	switch(currentState)
	{
		//COUNTDOWN
		case F14FIGHTER::SINGLEPLAYER::COUNTDOWN:
			centerTextWindow->setVisible(true);
			//COUNTDOWN WINDOW
			centerTextWindow->setText("Game starts in:\n\n\n" + StringConverter::toString((int)fabs(elapsedTime-1)));
			break;

		//GAME IS RUNNING
		case F14FIGHTER::SINGLEPLAYER::GAME_IS_RUNNING:

			//SHOW	ELAPSED TIME
			//		COLLECTED TIME
			//		HIGHSCORE TIME
			timeWindow->setText("Total         " + MyTimer::getMinutesAndSecondsFormated(elapsedTime) + "\n" +
								"Collected  -" + MyTimer::getMinutesAndSecondsFormated(collectedTime) + "\n" +
								"Highscore   " + MyTimer::getMinutesAndSecondsFormated(elapsedTime - collectedTime));

			//Update progress Bars
			speedBar->setProgress(f14->getSpeedProgress());	
			boostBar->setProgress(f14->getBoostProgress());
			colorBar->setProgress(f14->getColorProgress());
			speedText->setText(StringConverter::toString(f14->speedRaiseFactor*100) + "% max Speed");

			break;
		case F14FIGHTER::SINGLEPLAYER::GAME_OVER:
			break;
		case F14FIGHTER::SINGLEPLAYER::WIN:
			ceguiKeyboard.updateKeyboard();

			if(!ceguiKeyboard.showKeyboard)
			{
				isHighscoreSaved = true;
				double neededTime = timeStampStopSinglePlayer - timeStampStartSinglePlayer - collectedTime;
				dataManager->settingManagerSinglePlayerHighscore.insertHighscore(ceguiKeyboard.inputText, neededTime);
				dataManager->settingManagerSinglePlayerHighscore.writeHighscoreToConfigFile("singlePlayerHighscore.cfg");
				centerTextWindow->setVisible(true);
				centerTextWindow->setAlpha(0.6);
				//write Highscore
				std::string highscoreString ="";
				for(int i = 0; i < 10; i++)
				{
					if(i < dataManager->settingManagerSinglePlayerHighscore.getNumberOfHighscoreEntries())
					{
						highscoreString += StringConverter::toString(i+1) + ". " + dataManager->settingManagerSinglePlayerHighscore.getStringEntry(i) + " - " + MyTimer::getMinutesAndSecondsFormated(dataManager->settingManagerSinglePlayerHighscore.getFloatEntry(i)) + "\n"; 
					}
				}

				centerTextWindow->setText("HighScore\n" + highscoreString + "\n\nPress Start");
			}
			break;
	}
	
	//show or hide Keyboard recording to attribute of ceguiKeyboard
	if(ceguiKeyboard.showKeyboard)
		dataManager->CEGUISystem->setGUISheet(ceguiKeyboard.CEGUISheet);
	else
		dataManager->CEGUISystem->setGUISheet(CEGUISheet);
	
	handleToggleValues(dt);
	
	//fade out
	infoBox->setAlpha(timeUntilNextToggleInfobox/3);
}
//--------------------------------------------------------------
void SinglePlayer::handleToggleValues(float dt)
{
	// one of the input modes is immediate, so setup what is needed for immediate movement
	if (timeUntilNextToggleInfobox >= 0)
		timeUntilNextToggleInfobox -= dt;
}

//--------------------------------------------------------------
void SinglePlayer::handleTorusRotation(float dt)
{
	//rotate Torus
	for(unsigned int i = 0; i < torus.size(); i++)
	{
		torus[i]->moveTorus(dt);

		//MOVE not alive Toruses in direction of f14
		if(!torus[i]->alive)
		{
			torus[i]->sceneNode->translate( f14->translationVector );
	
		}
	}
}
//--------------------------------------------------------------
void SinglePlayer::handleDeleteDestroyedTorus(float dt)
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
void SinglePlayer::updateGameIsRunning(const FrameEvent& evt)
{
	//f14
	f14->moveF14(evt.timeSinceLastFrame);
	handleCollisionDetection(evt);
}
//--------------------------------------------------------------
bool SinglePlayer::frameEnded(const FrameEvent& evt)
{
	//first frameended is from previous state
	if(timeStampStartSinglePlayer == -100)
	{	
		timeStampStartSinglePlayer= F14FIGHTER::TIMER::NOT_INITIALIZED;
		return true;
	}
	if(timeStampStartSinglePlayer == F14FIGHTER::TIMER::NOT_INITIALIZED)
	{
		int countdownValue = settingManager.getInt("countdownBeforeStart");
		timeStampStartSinglePlayer = dataManager->myTimer.getElapsedTime() + countdownValue;
	}
	//timer
	elapsedTime = dataManager->myTimer.getElapsedTime() - timeStampStartSinglePlayer;
	
	return true;
}
//--------------------------------------------------------------
bool SinglePlayer::processUnbufferedKeyInput(const FrameEvent& evt, OIS::Keyboard* mKeyboard)
{
	if(dataManager->controller == F14FIGHTER::Controller::KEYBOARD)
	{
		switch(currentState)
		{
			case F14FIGHTER::SINGLEPLAYER::COUNTDOWN:
				break;
			case F14FIGHTER::SINGLEPLAYER::GAME_IS_RUNNING:
				f14->f14Controlls->updateKeyboardControlls(mKeyboard,evt.timeSinceLastFrame, dataManager->window->getViewport(0));
			break;
			case F14FIGHTER::SINGLEPLAYER::GAME_OVER:
				break;
			case F14FIGHTER::SINGLEPLAYER::WIN:
				break;
		}	
	}

	//MENU
	if( mKeyboard->isKeyDown(OIS::KC_ESCAPE))
		stateManager->createState(new Menu(stateManager));
	return true;
}

//--------------------------------------------------------------
bool SinglePlayer::processUnbufferedMouseInput(const FrameEvent& evt, OIS::Mouse* mMouse, const OIS::MouseState* ms)
{
	return true;
}
//--------------------------------------------------------------
bool SinglePlayer::processUnbufferedXBOXControllerInput(const FrameEvent& evt)
{
	if(dataManager->controller == F14FIGHTER::Controller::XBOXCONTROLLER)
	{
		switch(currentState)
		{
			case F14FIGHTER::SINGLEPLAYER::COUNTDOWN:
				break;
			case F14FIGHTER::SINGLEPLAYER::GAME_IS_RUNNING:
				f14->f14Controlls->updateXboxControlls(evt.timeSinceLastFrame, dataManager->window->getViewport(0));
				break;
			case F14FIGHTER::SINGLEPLAYER::GAME_OVER:
				break;
			case F14FIGHTER::SINGLEPLAYER::WIN:
				break;
		}
	}
	//MENU
		if( xboxDataManager->controller[0].startPressed)
			stateManager->createState(new Menu(stateManager));
	return true;
}
//--------------------------------------------------------------
void SinglePlayer::handleCollisionDetection(const FrameEvent& evt)
{
	handleF14TorusCollision();
	handleF14RunwayCollision();
	handleF14HydraxCollision();
	handleF14WorldGeometryCollision();
	handleF14FinishCollision();

	//yaw camera if f14 is destroyed
	if(f14->f14Destroyed)
		f14->sceneNode->yaw(Radian(settingManager.getFloat("cameraYawValueAfterF14Destroyed")*evt.timeSinceLastFrame),Node::TS_WORLD);
}
//--------------------------------------------------------------
void SinglePlayer::handleF14TorusCollision()
{
	const AxisAlignedBox f14BoundingBox = f14->sceneNode->_getWorldAABB();

	/////////////////////////////////
	//F14 - TORUS COLLISION DETECTION
	for(unsigned int i = 0; i < torus.size(); i++)
	{
		if(f14BoundingBox.intersects(torus[i]->sceneNode->_getWorldAABB()))
		{	
			if(torus[i]->color == f14->activeEmitter)
				handleTorusCollision(torus[i], true);
			else
				handleTorusCollision(torus[i], false);
		}
	}
}
//--------------------------------------------------------------
void SinglePlayer::handleF14RunwayCollision()
{
	/////////////////////////////////
	//F14 - RUNWAY
	if(f14->currentPhase == F14FIGHTER::F14::START_PHASE)
	{
		
		if(f14->getSpeedProgress() > 0.45)
		{
			f14->currentPhase = F14FIGHTER::F14::FLYING_PHASE;
		}
		/////////////////////////////////
		//F14 - Runway Plane START
		if(CollisionHandler::checkBottomCollision(f14->sceneNode->_getWorldAABB(), runWay->sceneNodePlane->_getWorldAABB()))
		{
			f14->impuls.y = 0;	
			Vector3 newPosition = f14->sceneNode->getPosition();
			newPosition.y = runWay->sceneNode->getPosition().y + runWay->sceneNodePlane->getPosition().y + runWay->settingManager.getFloat("runWayAdjustHeight");
			f14->sceneNode->setPosition(newPosition);
		}
		else
		{
			f14->currentPhase = F14FIGHTER::F14::FLYING_PHASE;
		}
	}
	else if(f14->currentPhase == F14FIGHTER::F14::FLYING_PHASE)
	{
		while(true)
		{
			if(CollisionHandler::checkBottomCollision(f14->sceneNode->_getWorldAABB(), runWay->sceneNodePlane->_getWorldAABB()))
			{
				f14->sceneNode->translate(0,0.1,0);
				f14->sceneNode->_update(true,false);
			}
			else
			{
				break;
			}
		}
	}
}
//--------------------------------------------------------------
void SinglePlayer::handleF14HydraxCollision()
{
	//////////////////////
	// F14 - HYDRAX
	if(dataManager->mHydrax->getPosition().y >= f14->sceneNode->getPosition().y - 2)
	{
		f14->letF14Die();
		f14->impuls = Vector3(0,0,0);

		f14->sceneNode->setPosition(f14->sceneNode->getPosition().x, 200, f14->sceneNode->getPosition().z);
	}
}
//--------------------------------------------------------------
void SinglePlayer::handleF14WorldGeometryCollision()
{
	///////////////////////
	//F14 - World Geometry
	static Ray updateRay;
	updateRay.setOrigin(f14->sceneNode->getPosition());
	updateRay.setDirection(Vector3::UNIT_Y);
	raySceneQuery->setRay(updateRay);
	RaySceneQueryResult& qryResult = raySceneQuery->execute();
	RaySceneQueryResult::iterator i = qryResult.begin();
	if (i != qryResult.end() && i->worldFragment)
	{
		
		f14->letF14Die();
		Vector3 pos = f14->sceneNode->getPosition();
		f14->impuls = Vector3(0,0,0);
		f14->sceneNode->setPosition(pos.x,i->worldFragment->singleIntersection.y + 10,  pos.z);
	}
}
//--------------------------------------------------------------
void SinglePlayer::handleF14FinishCollision()
{
	const AxisAlignedBox f14BoundingBox = f14->sceneNode->_getWorldAABB();
	if(f14BoundingBox.intersects(finish->sceneNode->_getWorldAABB()))
	{
		currentState = F14FIGHTER::SINGLEPLAYER::WIN;
		ceguiKeyboard.showKeyboard= true;
		timeStampStopSinglePlayer = dataManager->myTimer.getElapsedTime();
	}
}
//--------------------------------------------------------------
void SinglePlayer::handleTorusCollision(Torus* torus, bool extra)
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
				infoBox->setText(StringConverter::toString(multiplikator) + "x Boost");			
				infoBox->setVisible(true);
				timeUntilNextToggleInfobox = 3;
				f14->addBoost(multiplikator*10);
				break;
		
			case F14FIGHTER::TORUS::RED:
				infoBox->setText(StringConverter::toString(multiplikator) + "x Color");
				infoBox->setVisible(true);
				timeUntilNextToggleInfobox = 3;
				f14->addColor(multiplikator*10);
				break;
		
			case F14FIGHTER::TORUS::GREEN:
				infoBox->setText(StringConverter::toString(multiplikator) + "x Max Speed");
				infoBox->setVisible(true);
				timeUntilNextToggleInfobox = 3;
				f14->raiseMaxSpeed(multiplikator*0.1);
				break;
		
			case F14FIGHTER::TORUS::YELLOW:
				infoBox->setText(StringConverter::toString(multiplikator) + "x -Time");
				infoBox->setVisible(true);
				timeUntilNextToggleInfobox = 3;
				collectedTime += multiplikator*1;
				break;
		}
	}
}
//--------------------------------------------------------------
void SinglePlayer::updateGameIsWon(const FrameEvent& evt)
{
	f14->moveF14(evt.timeSinceLastFrame);
	handleCollisionDetection(evt);
}