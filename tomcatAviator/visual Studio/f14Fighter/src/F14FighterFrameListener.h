#ifndef _TEST_APP_FRAME_LISTENER_H_
#define _TEST_APP_FRAME_LISTENER_H_

#include "Ogre.h"
#include "StandardApplication/StandardFrameListener.h"
#include "Manager/DataManager/DataManager.h"
#include "XboxController/XboxDataManager.h"

CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);
CEGUI::MouseButton convertOISMouseButtonToCegui(int buttonID);

class F14FighterFrameListener : public StandardFrameListener
{
	public:
		F14FighterFrameListener(SceneManager* sceneMgr, RenderWindow* win, Camera* cam);

		virtual bool				frameStarted(const FrameEvent& evt);
		virtual bool				frameEnded(const FrameEvent& evt);
		virtual bool				processUnbufferedKeyInput(const FrameEvent& evt);
		virtual bool				processUnbufferedMouseInput(const FrameEvent& evt);

		bool						iskeyDown;
		bool						isRBDown;
	
	private:
	   SceneManager*				_sceneManager;
	   DataManager*					_dataManager;
	   XboxDataManager*				xboxDataManager;
};




#endif