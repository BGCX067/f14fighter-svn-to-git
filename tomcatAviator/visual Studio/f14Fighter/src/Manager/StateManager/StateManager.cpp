#include "StateManager.h"
#include "State.h"

//--------------------------------------------------------------
StateManager::StateManager()
{
	_currentState = 0;
}

//--------------------------------------------------------------
void StateManager::createState(State* state)
{
	if (_currentState != 0) 
		delete _currentState;

	_currentState = state;
	_currentState->setupState();
}

//--------------------------------------------------------------
bool StateManager::frameStarted(const FrameEvent& evt)
{
	_currentState->processUnbufferedXBOXControllerInput(evt);
	return _currentState->frameStarted(evt);

}
bool StateManager::frameEnded(const FrameEvent& evt)
{
	return _currentState->frameEnded(evt);
}
//--------------------------------------------------------------
bool StateManager::processUnbufferedKeyInput(const FrameEvent& evt, OIS::Keyboard* mKeyboard)
{
	return _currentState->processUnbufferedKeyInput(evt, mKeyboard);
}

//--------------------------------------------------------------
bool StateManager::processUnbufferedMouseInput(const FrameEvent& evt, OIS::Mouse* mMouse, const OIS::MouseState* ms)
{
	return _currentState->processUnbufferedMouseInput(evt, mMouse, ms);

}