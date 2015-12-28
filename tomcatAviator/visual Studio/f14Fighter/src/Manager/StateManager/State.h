#ifndef _STATE_H_
#define _STATE_H_

#include "Ogre.h"
//HYDRAX HEADERS
#include "Hydrax.h"
#include "Noise/Perlin/Perlin.h"
#include "Modules/ProjectedGrid/ProjectedGrid.h"

#include <OIS/OIS.h>

#include "../../XboxController/XboxDataManager.h"


using namespace Ogre;
class DataManager;
class StateManager;
class State {
	
public:
	State(StateManager *stateManager);
	virtual ~State();

	void						setupState();
	virtual void				createScene(void) = 0;
	virtual void				createLights(void) = 0;
	virtual void				setupGUI(void) = 0;
	virtual void				setupEventHandler(void) = 0;

	virtual void				setup() = 0;

	virtual bool				frameStarted(const FrameEvent& evt) = 0;
	virtual bool				frameEnded(const FrameEvent& evt) = 0;
	virtual bool				processUnbufferedKeyInput(const FrameEvent& evt, OIS::Keyboard* mKeyboard) = 0;
	virtual bool				processUnbufferedXBOXControllerInput(const FrameEvent& evt) = 0;
	virtual bool				processUnbufferedMouseInput(const FrameEvent& evt, OIS::Mouse* mMouse, const OIS::MouseState* ms) = 0;


	void						createHydrax();

	StateManager*				stateManager;
	DataManager*				dataManager;
	XboxDataManager*			xboxDataManager;
};
#endif