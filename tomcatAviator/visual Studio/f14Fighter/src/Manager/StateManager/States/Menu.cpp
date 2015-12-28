#include "Menu.h"
#include "../../DataManager/DataManager.h"

//--------------------------------------------------------------
Menu::Menu(StateManager *stateManager)
:	State(stateManager), _currentState(F14FIGHTER::MENU::NOTHING_SELECTED),	//Load Image
	mImage(0),myTexture(0)
{
	std::cout << "################" << std::endl;
	std::cout << "# Menu created #" << std::endl;
	std::cout << "################" << std::endl;
	dataManagerMenu = DataManagerMenu::getDataManagerAsSingleton();
	
}

//--------------------------------------------------------------
Menu::~Menu()
{
	dataManager->camera->setPosition(0,0,0);

	CEGUI::MouseCursor::getSingleton().hide();		
	dataManagerMenu->CEGUIWin->destroyAllWindows();

	if(dataManagerMenu->newGame)
	{
		dataManagerMenu->newGame->removeAllEvents();
		dataManagerMenu->newGame->destroy();
		dataManagerMenu->newGame = 0;
	}
	if(dataManagerMenu->controller)
	{	
		dataManagerMenu->controller->removeAllEvents();
		dataManagerMenu->controller->destroy();
		dataManagerMenu->controller = 0;
	}	
	if(dataManagerMenu->multiPlayer)
	{
		dataManagerMenu->multiPlayer->removeAllEvents();
		dataManagerMenu->multiPlayer->destroy();
		dataManagerMenu->multiPlayer = 0;
	}	
	if(dataManagerMenu->multiPlayerRace)
	{
		dataManagerMenu->multiPlayerRace->removeAllEvents();
		dataManagerMenu->multiPlayerRace->destroy();
		dataManagerMenu->multiPlayerRace = 0;
	}
	if(dataManagerMenu->quit)
	{
		dataManagerMenu->quit->removeAllEvents();
		dataManagerMenu->quit->destroy();
		dataManagerMenu->quit = 0;
	}
	if(mImage)
	{
		mImage->removeAllEvents();
		mImage->destroy();
		mImage = 0;
	}
	if(dataManagerMenu->about)
	{
		dataManagerMenu->about->removeAllEvents();
		dataManagerMenu->about->destroy();
		dataManagerMenu->about = 0;
	}

	
	//mImage(0),myTexture(0), pImageSet(0)

}

//--------------------------------------------------------------
void Menu::setup(void)
{
	
}

//--------------------------------------------------------------
void Menu::createScene(void)
{
	dataManager->window->reposition(0,0);
	//CAMERA START POSITION
	dataManager->camera->setPosition(1524,137,1217.75);
	dataManager->camera->setOrientation(Ogre::Quaternion(0.824994,-0.00999554,-0.565078,-0.00684747));

	//Just Call once otherwise app will crash, cause some problems in Hydrax Destructor
	createHydrax();

	dataManager->sceneManager->setSkyBox(true, "Sky/ClubTropicana");	
	dataManager->sceneManager->setWorldGeometry("Island.cfg");



}

//--------------------------------------------------------------
void Menu::createLights(void)
{
	// Set ambient light
	dataManager->sceneManager->setAmbientLight(ColourValue(1,1,1));
	// Create a light
	Light* l = dataManager->sceneManager->createLight("Light");
	l->setPosition(0,10000,0);
	l->setDiffuseColour(1,0.9,0.6);
}
//--------------------------------------------------------------
void Menu::setupGUI(void)
{	
	//stateManager->createState(new SinglePlayer(&dataManager->stateManager));
	/*CEGUI::MouseCursor::getSingleton().show();*/

	//WINDOW AND SHEET FOR DataManagerMenu
	// Quit button
	dataManagerMenu->CEGUIWin = CEGUI::WindowManager::getSingletonPtr();
	dataManagerMenu->CEGUISheet = dataManagerMenu->CEGUIWin->createWindow("DefaultGUISheet", "CEGUIDemo/Sheet");

	float offsetX = 0.1;
	float offsetY = 0.15;
	/////////////////
	//NEW GAME BUTTON
    dataManagerMenu->newGame = dataManagerMenu->CEGUIWin->createWindow("TaharezLook/Button", "menu/newGame");

    dataManagerMenu->newGame->setText("newGame");

    dataManagerMenu->newGame->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
	dataManagerMenu->newGame->setPosition(CEGUI::UVector2(CEGUI::UDim(offsetX, 0), CEGUI::UDim(offsetY, 0)));

	dataManagerMenu->CEGUISheet->addChildWindow(dataManagerMenu->newGame);

	
	///////////////////
	//OPTIONS BUTTON
    dataManagerMenu->controllerText = dataManagerMenu->CEGUIWin->createWindow("TaharezLook/StaticText", "menu/controllerText");

    dataManagerMenu->controllerText->setText("choose Controller");
	dataManagerMenu->controllerText->setFont(((CEGUI::utf8*)"BlueHighway-10"));
    dataManagerMenu->controllerText->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.04, 0)));
	dataManagerMenu->controllerText->setPosition(CEGUI::UVector2(CEGUI::UDim(1-0.15, 0), CEGUI::UDim(offsetY, 0)));

	dataManagerMenu->CEGUISheet->addChildWindow(dataManagerMenu->controllerText);

	///////////////////
	//controller BUTTON
    dataManagerMenu->controller = dataManagerMenu->CEGUIWin->createWindow("TaharezLook/Button", "menu/highScore");

	if(dataManager->controller == F14FIGHTER::Controller::XBOXCONTROLLER)
	   dataManagerMenu->controller->setText("XboxController");
	else
		dataManagerMenu->controller->setText("Keyboard");
	
    dataManagerMenu->controller->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
	dataManagerMenu->controller->setPosition(CEGUI::UVector2(CEGUI::UDim(1-0.15, 0), CEGUI::UDim(offsetY + 0.04, 0)));

	dataManagerMenu->CEGUISheet->addChildWindow(dataManagerMenu->controller);

	///////////////////
	//MULTIPLAYER BUTTON
    dataManagerMenu->multiPlayer = dataManagerMenu->CEGUIWin->createWindow("TaharezLook/Button", "menu/multiPlayer");

    dataManagerMenu->multiPlayer->setText("MultiPlayer - Rings");

    dataManagerMenu->multiPlayer->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
	dataManagerMenu->multiPlayer->setPosition(CEGUI::UVector2(CEGUI::UDim(offsetX, 0), CEGUI::UDim(offsetY + 0.05, 0)));

	dataManagerMenu->CEGUISheet->addChildWindow(dataManagerMenu->multiPlayer);

	///////////////////
	//OPTIONS BUTTON
    dataManagerMenu->multiPlayerRace = dataManagerMenu->CEGUIWin->createWindow("TaharezLook/Button", "menu/multiplayerRace");

    dataManagerMenu->multiPlayerRace->setText("MultiPlayer - Race");

    dataManagerMenu->multiPlayerRace->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
	dataManagerMenu->multiPlayerRace->setPosition(CEGUI::UVector2(CEGUI::UDim(offsetX, 0), CEGUI::UDim(offsetY + 0.1, 0)));

	dataManagerMenu->CEGUISheet->addChildWindow(dataManagerMenu->multiPlayerRace);

	
	///////////////////
	////Boost Text
	//boostText = CEGUIWin->createWindow("TaharezLook/StaticText", "singlePlayer/boostText");
	//boostText->setText("Boost");	
 //   boostText->setSize(CEGUI::UVector2(CEGUI::UDim(0.08, 0), CEGUI::UDim(0.05, 0)));
	//boostText->setPosition(CEGUI::UVector2(CEGUI::UDim(0.00, 0), CEGUI::UDim(0.0, 0)));
	//CEGUISheet->addChildWindow(boostText);

	//////////////
	//QUIT BUTTON
    dataManagerMenu->quit = dataManagerMenu->CEGUIWin->createWindow("TaharezLook/Button", "menu/quit");
	
    dataManagerMenu->quit->setText("Quit");

    dataManagerMenu->quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
	dataManagerMenu->quit->setPosition(CEGUI::UVector2(CEGUI::UDim(offsetX, 0), CEGUI::UDim(offsetY + 0.2, 0)));
	dataManagerMenu->CEGUISheet->addChildWindow(dataManagerMenu->quit);

	//////////////
	//QUIT BUTTON
    dataManagerMenu->about = dataManagerMenu->CEGUIWin->createWindow("TaharezLook/Button", "menu/about");
	
    dataManagerMenu->about->setText("About");

    dataManagerMenu->about->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
	dataManagerMenu->about->setPosition(CEGUI::UVector2(CEGUI::UDim(offsetX, 0), CEGUI::UDim(offsetY + 0.15, 0)));
	dataManagerMenu->CEGUISheet->addChildWindow(dataManagerMenu->about);
	
	mImage = CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"TaharezLook/StaticImage", (CEGUI::utf8*)"menu/image");
	//Load Image
	if(!CEGUI::ImagesetManager::getSingleton().isImagesetPresent("ImageSetName"))
	{
		myTexture = dataManager->CEGUIRenderer->createTexture((CEGUI::utf8*)"mmtLogo.jpg");

		dataManagerMenu->pImageSet = CEGUI::ImagesetManager::getSingleton().createImageset((CEGUI::utf8*)"ImageSetName", myTexture);
		
		dataManagerMenu->pImageSet->defineImage((CEGUI::utf8*)"mmtLogo", CEGUI::Point(0.0f, 0.0f),CEGUI::Size(400,200),   CEGUI::Point(0.0f,0.0f));	
	}

	mImage->setPosition(CEGUI::UVector2(CEGUI::UDim(1-0.4, 0),CEGUI::UDim(1-0.2,0)));
	mImage->setProperty("Image", CEGUI::PropertyHelper::imageToString(&dataManagerMenu->pImageSet->getImage((CEGUI::utf8*)"mmtLogo")));
	mImage->setSize(CEGUI::UVector2(CEGUI::UDim(0.4,0),CEGUI::UDim(0.2, 0)));
	dataManagerMenu->CEGUISheet->addChildWindow(mImage);

	////set Sheet
	dataManager->CEGUISystem->setGUISheet(dataManagerMenu->CEGUISheet);
	CEGUI::MouseCursor::getSingleton().show();
	dataManagerMenu->CEGUISheet->show();

	
	dataManager->CEGUISystem->setGUISheet(dataManagerMenu->CEGUISheet);
}

//--------------------------------------------------------------
void Menu::setupEventHandler(void)
{
	//EVENTHANDLER
	dataManagerMenu->newGame->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menu::newGame, this));
	dataManagerMenu->controller->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menu::controller, this));
	dataManagerMenu->multiPlayer->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menu::multiPlayer, this));
	dataManagerMenu->multiPlayerRace->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menu::multiPlayerRace, this));
	dataManagerMenu->quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menu::quit, this));
	dataManagerMenu->about->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menu::about, this));
}

//--------------------------------------------------------------
bool Menu::newGame(const CEGUI::EventArgs &e)
{
	_currentState = F14FIGHTER::MENU::NEW_GAME;
	
	return true;
}

//--------------------------------------------------------------
bool Menu::controller(const CEGUI::EventArgs &e)
{
	
	
	if(dataManager->controller == F14FIGHTER::Controller::XBOXCONTROLLER)
	{
		dataManager->controller = F14FIGHTER::Controller::KEYBOARD;
		dataManagerMenu->controller->setText("Keyboard");
	}
	else if(dataManager->controller == F14FIGHTER::Controller::KEYBOARD)
	{
		dataManager->controller = F14FIGHTER::Controller::XBOXCONTROLLER;
		dataManagerMenu->controller->setText("XboxController");
	}
	else
	{
		dataManager->controller = F14FIGHTER::Controller::KEYBOARD;
		dataManagerMenu->controller->setText("Keyboard");
	}

	return true;
}

//--------------------------------------------------------------
bool Menu::multiPlayer(const CEGUI::EventArgs &e)
{
	_currentState = F14FIGHTER::MENU::MULTIPLAYER;
	return true;
}

//--------------------------------------------------------------
bool Menu::multiPlayerRace(const CEGUI::EventArgs &e)
{
	_currentState = F14FIGHTER::MENU::MULTIPLAYER_RACE;
	return true;
}
//--------------------------------------------------------------
bool Menu::quit(const CEGUI::EventArgs &e)
{
	std::cout << "QUIT";
	exit(0);
	return true;
}
bool Menu::about(const CEGUI::EventArgs &e)
{
	_currentState = F14FIGHTER::MENU::ABOUT;
	return true;
}


//--------------------------------------------------------------
bool Menu::frameStarted(const FrameEvent& evt)
{
	
	switch(_currentState)
	{
		case F14FIGHTER::MENU::NEW_GAME:
			stateManager->createState(new LoadingScreen(&dataManager->stateManager, F14FIGHTER::MENU::NEW_GAME));
			break;
		case F14FIGHTER::MENU::MULTIPLAYER:
		stateManager->createState(new LoadingScreen(&dataManager->stateManager, F14FIGHTER::MENU::MULTIPLAYER));
			break;
		case F14FIGHTER::MENU::LOADING_SCREEN:
			stateManager->createState(new LoadingScreen(&dataManager->stateManager, F14FIGHTER::MENU::LOADING_SCREEN));
			break;
		case F14FIGHTER::MENU::MULTIPLAYER_RACE:
			stateManager->createState(new LoadingScreen(&dataManager->stateManager, F14FIGHTER::MENU::MULTIPLAYER_RACE));
			break;
		case F14FIGHTER::MENU::ABOUT:
			stateManager->createState(new LoadingScreen(&dataManager->stateManager, F14FIGHTER::MENU::ABOUT, 10));
			break;
	}
	
	return true;
}

//--------------------------------------------------------------
bool Menu::frameEnded(const FrameEvent& evt)
{
	return true;
}

//--------------------------------------------------------------
bool Menu::processUnbufferedKeyInput(const FrameEvent& evt, OIS::Keyboard* mKeyboard)
{
	if( mKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		delete dataManager->xboxThread;
		delete dataManager->thread;
		exit(0);
	}
	return true;
}
bool Menu::processUnbufferedXBOXControllerInput(const FrameEvent& evt)
{
	////MENU
	//if( xboxDataManager->controller[0].startPressed)
	//{
	//	delete dataManager->xboxThread;
	//	delete dataManager->thread;
	//	exit(0);
	//}
	return true;
}
//--------------------------------------------------------------
bool Menu::processUnbufferedMouseInput(const FrameEvent& evt, OIS::Mouse* mMouse, const OIS::MouseState* ms)
{
	return true;
}
