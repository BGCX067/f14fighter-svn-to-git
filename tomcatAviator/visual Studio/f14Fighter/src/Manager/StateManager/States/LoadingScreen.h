#ifndef _LOADING_SCREEN_H_
#define _LOADING_SCREEN_H_

#include "../../../Defines.h"
#include "../State.h"
#include "../StateManager.h"
#include "../../SettingManager/SettingManager.h"
#include "Ogre.h"

#include <CEGUI/CEGUI.h>
#include <OIS/OIS.h>
#include <OgreCEGUIRenderer.h>

using namespace Ogre;

class LoadingScreen : public State {

public:
	LoadingScreen(StateManager *stateManager, int nextState, float timeToShow = 1);
	~LoadingScreen();

	virtual bool			frameStarted(const FrameEvent& evt);
	virtual bool			frameEnded(const FrameEvent& evt);
	virtual bool			processUnbufferedKeyInput(const FrameEvent& evt, OIS::Keyboard* mKeyboard);
	virtual bool			processUnbufferedMouseInput(const FrameEvent& evt, OIS::Mouse* mMouse, const OIS::MouseState* ms);
	virtual bool			processUnbufferedXBOXControllerInput(const FrameEvent& evt);

private:
	virtual void			setup();
	virtual void			createScene(void);
	virtual void			createLights(void);
	virtual void			setupGUI(void);
	virtual void			setupEventHandler(void);

	double					timeStampStartLoadingScreen;
	float					elapsedTime;

	SettingManager			settingManager;
	int						nextState;
	std::string				loadingImage;
	float					timeToShow;
	//Load Image
	CEGUI::Window*			mImage;
	CEGUI::Texture*			myTexture;

	//CEGUI
	CEGUI::WindowManager*	CEGUIWin;
    CEGUI::Window*			CEGUISheet;

	CEGUI::Imageset*		pImageSet;

};

#endif
