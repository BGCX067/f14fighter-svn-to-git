/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2006 Torus Knot Software Ltd
Also see acknowledgements in Readme.html

You may use this sample code for anything you like, it is not covered by the
LGPL like the rest of the engine.
-----------------------------------------------------------------------------
*/
/*
-----------------------------------------------------------------------------
Filename:    StandardFrameListener.h
Description: Defines an example frame listener which responds to frame events.
This frame listener just moves a specified camera around based on
keyboard and mouse movements.
Mouse:    Freelook
W or Up:  Forward
S or Down:Backward
A:        Step left
D:        Step right
             PgUp:     Move upwards
             PgDown:   Move downwards
             F:        Toggle frame rate stats on/off
			 R:        Render mode
             T:        Cycle texture filtering
                       Bilinear, Trilinear, Anisotropic(8)
             P:        Toggle on/off display of camera position / orientation
-----------------------------------------------------------------------------
*/

#ifndef __StandardFrameListener_H__
#define __StandardFrameListener_H__

#include "Ogre.h"
#include "OgreStringConverter.h"
#include "OgreException.h"

//Use this define to signify OIS will be used as a DLL
//(so that dll import/export macros are in effect)
#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

using namespace Ogre;

class StandardFrameListener: public FrameListener, public WindowEventListener
{
	public:
		// Constructor takes a RenderWindow because it uses that to determine input context
		StandardFrameListener(RenderWindow* win, Camera* cam, bool bufferedKeys = false, bool bufferedMouse = false, bool bufferedJoy = false );
		virtual ~StandardFrameListener();
		
		//Methods:
		virtual void				windowResized(RenderWindow* rw);//Adjust mouse clipping area
		virtual void				windowClosed(RenderWindow* rw);//Unattach OIS before window shutdown (very important under Linux)
		virtual bool				processUnbufferedKeyInput(const FrameEvent& evt);
		virtual bool				processUnbufferedMouseInput(const FrameEvent& evt);
		virtual void				moveCamera();
		virtual void				showDebugOverlay(bool show);
		bool						frameRenderingQueued(const FrameEvent& evt);// Override frameRenderingQueued event to process that (don't care about frameEnded)
		virtual bool				frameEnded(const FrameEvent& evt);

	protected:
		virtual void				updateStats(void);

		//Attributes:
	protected:
		Camera*						mCamera;

		Vector3						mTranslateVector;
		Real						mCurrentSpeed;
		RenderWindow*				mWindow;
		bool						mStatsOn;

		std::string					mDebugText;

		unsigned int				mNumScreenShots;
		float						mMoveScale;
		float						mSpeedLimit;
		Degree						mRotScale;

		//to stop toggles flipping too fast
		Real						mTimeUntilNextToggle;
		Radian						mRotX, mRotY;
		TextureFilterOptions		mFiltering;
		int							mAniso;

		int							mSceneDetailIndex ;
		Real						mMoveSpeed;
		Degree						mRotateSpeed;
		Overlay*					mDebugOverlay;

		//OIS Input devices
		OIS::InputManager*			mInputManager;
		OIS::Mouse*					mMouse;
		OIS::Keyboard*				mKeyboard;
		OIS::JoyStick*				mJoy;

};

#endif
