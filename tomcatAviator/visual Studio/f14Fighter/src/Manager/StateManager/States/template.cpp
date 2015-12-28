#include "Template.h"
#include "../../DataManager/DataManager.h"

//--------------------------------------------------------------
Template::Template(StateManager *stateManager)
:	State(stateManager)
{
	std::cout << "####################" << std::endl;
	std::cout << "# Template created #" << std::endl;
	std::cout << "####################" << std::endl;
	
}

//--------------------------------------------------------------
Template::~Template()
{
	
}

//--------------------------------------------------------------
void Template::setup(void)
{

}

//--------------------------------------------------------------
void Template::createScene(void)
{
	
}

//--------------------------------------------------------------
void Template::createLights(void)
{
	
}
//--------------------------------------------------------------
void Template::setupGUI(void)
{	
	
}

//--------------------------------------------------------------
void Template::setupEventHandler(void)
{
	
}

//--------------------------------------------------------------
bool Template::frameStarted(const FrameEvent& evt)
{
	
	return true;
}

//--------------------------------------------------------------
bool Template::frameEnded(const FrameEvent& evt)
{
	return true;
}

//--------------------------------------------------------------
bool Template::processUnbufferedKeyInput(const FrameEvent& evt, OIS::Keyboard* mKeyboard)
{
	
	return true;
}
bool Template::processUnbufferedXBOXControllerInput(const FrameEvent& evt)
{
	return true;
}
//--------------------------------------------------------------
bool Template::processUnbufferedMouseInput(const FrameEvent& evt, OIS::Mouse* mMouse, const OIS::MouseState* ms)
{
	return true;
}
