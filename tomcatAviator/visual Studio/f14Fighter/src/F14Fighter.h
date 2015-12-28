#ifndef _F14_FIGHTER_H_
#define _F14_FIGHTER_H_

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif

#include "StandardApplication/StandardApplication.h"
#include "F14FighterFrameListener.h"

#include "Manager/StateManager/States/States.h"
#include "Manager/DataManager/DataManagerMenu.h"

#include "XboxController/XboxDataManager.h"


#include "fmod.hpp"
#include "fmod_errors.h"

class F14Fighter : public StandardApplication
{
	public:
		F14Fighter(void);
		~F14Fighter(void);

		void						createPalms(void);

	//Mehtods:
	protected:
		virtual void				createCamera(void);
		virtual bool				configure(void);
		virtual void				createScene(void);// Just override the mandatory create scene method
		virtual void				createLights(void);
		virtual void				setupCEGUI(void);
		virtual void				createState(void);
		void						createFrameListener(void);// Create new frame listener
		virtual void				chooseSceneManager(void);
		
		DataManagerMenu*			dataManagerMenu;
		
		XboxDataManager*			xboxDataManager;
		
};

#endif 