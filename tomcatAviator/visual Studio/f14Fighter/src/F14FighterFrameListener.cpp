#include "F14FighterFrameListener.h"
#include <stdlib.h>

//---------------------------------------------------------------------------
F14FighterFrameListener::F14FighterFrameListener(SceneManager *sceneMgr, RenderWindow* win, Camera* cam)
:	StandardFrameListener(win, cam),
	_sceneManager(sceneMgr),
	iskeyDown(false),isRBDown(false)
{
	_dataManager = DataManager::getDataManagerAsSingleton();
	xboxDataManager = XboxDataManager::getDataManagerAsSingleton();
	StandardFrameListener::showDebugOverlay(false);
}
//---------------------------------------------------------------------------
bool F14FighterFrameListener::frameStarted(const FrameEvent& evt)
{ 
	// Update Hydrax (After any camera position/orientation/... change)
	if(_dataManager->mHydrax)
		_dataManager->mHydrax->update(evt.timeSinceLastFrame);

	/////////////////////////////////////////////////
	//STATE SPEZIFIC frameStarted
	_dataManager->stateManager.frameStarted(evt);
	_dataManager->myTimer.updateTimer(evt.timeSinceLastFrame);

	return StandardFrameListener::frameStarted(evt);
}

//---------------------------------------------------------------------------
bool F14FighterFrameListener::frameEnded(const FrameEvent& evt)
{
	/////////////////////////////////////////////////
	//STATE SPEZIFIC frameEnded
	_dataManager->stateManager.frameEnded(evt);
	return StandardFrameListener::frameEnded(evt);
}

//---------------------------------------------------------------------------
bool F14FighterFrameListener::processUnbufferedKeyInput(const FrameEvent& evt)
{
	/////////////////////////////////////////////////
	//STATE SPEZIFIC INPUT
	_dataManager->stateManager.processUnbufferedKeyInput(evt, mKeyboard);

	/////////////////////////////////////////////////
	//GENERAL INPUT

	//SCREENSHOT
	if(mKeyboard->isKeyDown(OIS::KC_P) && mTimeUntilNextToggle <= 0)
	{
		std::ostringstream ss;
		ss << "screenshot_" << ++mNumScreenShots << ".png";
		mWindow->writeContentsToFile(ss.str());
		mTimeUntilNextToggle = 0.5;
		mDebugText = "Saved: " + ss.str();
	}

	// Return true to continue rendering
	return true;
}

//---------------------------------------------------------------------------
bool F14FighterFrameListener::processUnbufferedMouseInput(const FrameEvent& evt)
{
	
	const OIS::MouseState &ms = mMouse->getMouseState();

	/////////////////////////////////////////////////
	//STATE SPEZIFIC INPUT 
	_dataManager->stateManager.processUnbufferedMouseInput(evt, mMouse, &ms);
	
	/////////////////////////////////////////////////
	//CEGUI SPEZIFIC INPUT
	CEGUI::System::getSingleton().injectMouseMove(xboxDataManager->controller[0].getLXRel()*3,-xboxDataManager->controller[0].getLYRel()*3);
	CEGUI::System::getSingleton().injectMouseMove(xboxDataManager->controller[0].getRXRel()*3,-xboxDataManager->controller[0].getRYRel()*3);
	CEGUI::System::getSingleton().injectMouseMove(-xboxDataManager->controller[0].leftPressed*3+xboxDataManager->controller[0].rightPressed*3,xboxDataManager->controller[0].downPressed*3-xboxDataManager->controller[0].upPressed*3);
	CEGUI::System::getSingleton().injectMouseMove(ms.X.rel, ms.Y.rel);
	
	//CALLED TWICE -> otherwise button has to be clicked twice
	{
		//mouse button down
		CEGUI::System::getSingleton().injectMouseButtonDown(convertOISMouseButtonToCegui(ms.buttons));
		
		//Left mouse button up
		if(iskeyDown == true && ms.buttonDown(OIS::MB_Left) == false)
			CEGUI::System::getSingleton().injectMouseButtonUp(convertOISMouseButtonToCegui(ms.buttons));
		

		//mouse button down
		CEGUI::System::getSingleton().injectMouseButtonDown(convertOISMouseButtonToCegui(ms.buttons));
		
		//Left mouse button up
		if(iskeyDown == true && ms.buttonDown(OIS::MB_Left) == false)
			CEGUI::System::getSingleton().injectMouseButtonUp(convertOISMouseButtonToCegui(ms.buttons));
		
	}
	

	CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);

	if(xboxDataManager->controller[0].aPressed == false && isRBDown == true)
		CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::LeftButton);
	
	CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);

	if(xboxDataManager->controller[0].aPressed == false && isRBDown == true)
		CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::LeftButton);
	
	iskeyDown = ms.buttonDown(OIS::MB_Left);
	isRBDown = xboxDataManager->controller[0].aPressed;

	/////////////////////////////////////////////////
	//GENERAL INPUT

	//SHOW CAMERA DETAILS
	static bool displayCameraDetails = false;
	if(mKeyboard->isKeyDown(OIS::KC_I) && mTimeUntilNextToggle <= 0)
	{
		displayCameraDetails = !displayCameraDetails;
		mTimeUntilNextToggle = 0.5;
		if (!displayCameraDetails)
			mDebugText = "";
	}
	// Print camera details
	if(displayCameraDetails)
		mDebugText = "P: " + StringConverter::toString(mCamera->getDerivedPosition()) + " " + "O: " + StringConverter::toString(mCamera->getDerivedOrientation());

	return true;
}

CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;

    case OIS::MB_Right:
        return CEGUI::RightButton;

    case OIS::MB_Middle:
        return CEGUI::MiddleButton;

    default:
        return CEGUI::LeftButton;
    }
}

CEGUI::MouseButton convertOISMouseButtonToCegui(int buttonID)
{
    switch (buttonID)
    {
	case 0: return CEGUI::LeftButton;
	case 1: return CEGUI::RightButton;
	case 2:	return CEGUI::MiddleButton;
	case 3: return CEGUI::X1Button;
	default: return CEGUI::LeftButton;
    }
}