#include "LoadingScreen.h"
#include "../../DataManager/DataManager.h"

//--------------------------------------------------------------
LoadingScreen::LoadingScreen(StateManager *stateManager, int nextState, float timeToShow)
:	State(stateManager),mImage(0),myTexture(0), CEGUIWin(0), CEGUISheet(0), pImageSet(0),elapsedTime(-100), timeStampStartLoadingScreen(-100)
{
	
	std::cout << "#########################" << std::endl;
	std::cout << "# LoadingScreen created #" << std::endl;
	std::cout << "#########################" << std::endl;
	this->nextState = nextState;
	this->timeToShow = timeToShow;
	settingManager.loadFile("loadingScreenSettings.cfg");
	
	
	switch(nextState)
	{
		case F14FIGHTER::MENU::LOADING_SCREEN:
			loadingImage = settingManager.getString("testImage");
			break;
		case F14FIGHTER::MENU::NEW_GAME:
			loadingImage = settingManager.getString("singlePlayerImage");
			break;
		case F14FIGHTER::MENU::MULTIPLAYER:
			loadingImage = settingManager.getString("multiPlayerImage");
			break;
		case F14FIGHTER::MENU::MULTIPLAYER_RACE:
			loadingImage = settingManager.getString("multiPlayerRaceImage");
			break;
		case F14FIGHTER::MENU::MENU:
			loadingImage = settingManager.getString("menuImage");

		case F14FIGHTER::MENU::ABOUT:
			loadingImage = settingManager.getString("aboutImage");
			break;
	}
}

//--------------------------------------------------------------
LoadingScreen::~LoadingScreen()
{
	CEGUIWin->destroyAllWindows();

	if(mImage)
	{
		mImage->removeAllEvents();
		mImage->destroy();
		mImage = 0;
	}
	pImageSet->undefineImage("testImage");
	CEGUI::ImagesetManager::getSingleton().destroyImageset(pImageSet);
}

//--------------------------------------------------------------
void LoadingScreen::setup(void)
{

}

//--------------------------------------------------------------
void LoadingScreen::createScene(void)
{
	
}

//--------------------------------------------------------------
void LoadingScreen::createLights(void)
{
	
}
//--------------------------------------------------------------
void LoadingScreen::setupGUI(void)
{	
	//WINDOW AND SHEET 
	CEGUIWin = CEGUI::WindowManager::getSingletonPtr();
	CEGUISheet = CEGUIWin->createWindow("DefaultGUISheet", "CEGUIDemo/Sheet");

	mImage = CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"TaharezLook/StaticImage", (CEGUI::utf8*)"loadingScreen/image");
	
	
	myTexture = dataManager->CEGUIRenderer->createTexture(loadingImage);
	
	if(!CEGUI::ImagesetManager::getSingleton().isImagesetPresent("ImageSetTestImage"))
		pImageSet = CEGUI::ImagesetManager::getSingleton().createImageset((CEGUI::utf8*)"ImageSetTestImage", myTexture);
	else
		pImageSet = CEGUI::ImagesetManager::getSingleton().getImageset("ImageSetTestImage");
	
	if(!pImageSet->isImageDefined("testImage"))
	{	
		std::cout << "newImage created >>>>> " << std::endl;
		pImageSet->defineImage((CEGUI::utf8*)"testImage", CEGUI::Point(0.0f, 0.0f),CEGUI::Size(1920,1080),   CEGUI::Point(0.0f,0.0f));	
	}
	
	mImage->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0),CEGUI::UDim(0,0)));
	mImage->setProperty("Image", CEGUI::PropertyHelper::imageToString(&pImageSet->getImage((CEGUI::utf8*)"testImage")));
	mImage->setSize(CEGUI::UVector2(CEGUI::UDim(1,0),CEGUI::UDim(1, 0)));
	CEGUISheet->addChildWindow(mImage);
	
	////set Sheet
	dataManager->CEGUISystem->setGUISheet(CEGUISheet);
	
	CEGUISheet->show();

}

//--------------------------------------------------------------
void LoadingScreen::setupEventHandler(void)
{
	
}

//--------------------------------------------------------------
bool LoadingScreen::frameStarted(const FrameEvent& evt)
{
	//dataManager->window->setFullscreen(true,dataManager->window->getWidth(),dataManager->window->getHeight());
	if(elapsedTime > 0)
	{
		switch(nextState)
		{
			case F14FIGHTER::MENU::LOADING_SCREEN:
				stateManager->createState(new Menu(&dataManager->stateManager));
				break;
			case F14FIGHTER::MENU::NEW_GAME:
				stateManager->createState(new SinglePlayer(&dataManager->stateManager));
				break;
			case F14FIGHTER::MENU::MULTIPLAYER:
				stateManager->createState(new MultiPlayer(&dataManager->stateManager));
				break;
			case F14FIGHTER::MENU::MULTIPLAYER_RACE:
				stateManager->createState(new MultiPlayerRace(&dataManager->stateManager));
				break;
			case F14FIGHTER::MENU::MENU:
				stateManager->createState(new Menu(&dataManager->stateManager));
				break;
			case F14FIGHTER::MENU::ABOUT:
				stateManager->createState(new Menu(&dataManager->stateManager));
				break;
			
		}
	}
	
	return true;
}

//--------------------------------------------------------------
bool LoadingScreen::frameEnded(const FrameEvent& evt)
{
	//first frameended is from previous state
	if(timeStampStartLoadingScreen == -100)
	{	
		timeStampStartLoadingScreen= F14FIGHTER::TIMER::NOT_INITIALIZED;
		return true;
	}
	if(timeStampStartLoadingScreen == F14FIGHTER::TIMER::NOT_INITIALIZED)
	{
		int timeToShowInSeconds = timeToShow;
		timeStampStartLoadingScreen = dataManager->myTimer.getElapsedTime() + timeToShowInSeconds;
		//dataManager->window->setFullscreen(true,dataManager->window->getWidth(),dataManager->window->getHeight());
	}

	//timer
	elapsedTime = dataManager->myTimer.getElapsedTime() - timeStampStartLoadingScreen;
	return true;
}

//--------------------------------------------------------------
bool LoadingScreen::processUnbufferedKeyInput(const FrameEvent& evt, OIS::Keyboard* mKeyboard)
{
	
	return true;
}
bool LoadingScreen::processUnbufferedXBOXControllerInput(const FrameEvent& evt)
{

	////MENU
	//if( xboxDataManager->controller[0].startPressed)
	//{
	//	stateManager->createState(new Menu(stateManager));
	//}
	return true;
}
//--------------------------------------------------------------
bool LoadingScreen::processUnbufferedMouseInput(const FrameEvent& evt, OIS::Mouse* mMouse, const OIS::MouseState* ms)
{
	return true;
}
