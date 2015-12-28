#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include "../../../Defines.h"
#include "../State.h"
#include "../StateManager.h"

#include "Ogre.h"

#include <CEGUI/CEGUI.h>
#include <OIS/OIS.h>
#include <OgreCEGUIRenderer.h>

using namespace Ogre;

class Template : public State {

public:
	Template(StateManager *stateManager);
	~Template();

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
};

#endif
