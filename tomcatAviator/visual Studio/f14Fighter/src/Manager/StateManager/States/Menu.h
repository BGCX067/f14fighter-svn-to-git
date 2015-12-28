#ifndef _MENU_H_
#define _MENU_H_

#include "../../../Defines.h"
#include "../State.h"
#include "../StateManager.h"
#include "../../DataManager/DataManagerMenu.h"

#include "Ogre.h"

#include <CEGUI/CEGUI.h>
#include <OIS/OIS.h>
#include <OgreCEGUIRenderer.h>

using namespace Ogre;

class Menu : public State {

public:
	Menu(StateManager *stateManager);
	~Menu();

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


	bool					newGame(const CEGUI::EventArgs &e);
	bool					controller(const CEGUI::EventArgs &e);
	bool					multiPlayer(const CEGUI::EventArgs &e);
	bool					multiPlayerRace(const CEGUI::EventArgs &e);
	bool					quit(const CEGUI::EventArgs &e);
	bool					about(const CEGUI::EventArgs &e);
	
	DataManagerMenu*		dataManagerMenu;
	int						_currentState;

	//Load Image
	CEGUI::Window*			mImage;
	CEGUI::Texture*			myTexture;
};

#endif
