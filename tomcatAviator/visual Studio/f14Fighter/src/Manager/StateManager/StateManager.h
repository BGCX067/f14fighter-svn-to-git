#ifndef STATE_MANAGER_H_
#define STATE_MANAGER_H_
#include <OIS/OIS.h>

#include "Ogre.h"

using namespace Ogre;

class State;
class StateManager  {
public:
	StateManager();
	
	void			createState(State* state);

	bool			frameStarted(const FrameEvent& evt);
	bool			frameEnded(const FrameEvent& evt);
	bool			processUnbufferedKeyInput(const FrameEvent& evt, OIS::Keyboard* mKeyboard);
	bool			processUnbufferedMouseInput(const FrameEvent& evt, OIS::Mouse* mMouse, const OIS::MouseState* ms);
private:
	State*			_currentState;
};
#endif