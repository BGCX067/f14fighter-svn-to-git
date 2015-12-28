#include "F14Controlls.h"
#include "F14.h"
F14Controlls::F14Controlls(int xboxController, F14* f14)
: timeUntilNextToggleRed(0),timeUntilNextToggleYellow(0),timeUntilNextToggleBlue(0),timeUntilNextToggleGreen(0)
{
	xboxDataManager = XboxDataManager::getDataManagerAsSingleton();
	this->xboxController = xboxController;
	this->f14 = f14;
}

F14Controlls::~F14Controlls(void)
{
}
void F14Controlls::updateKeyboardControlls( OIS::Keyboard* mKeyboard, float dt, Viewport* vp)
{
	handleToggleValues(dt);

	if(xboxController == 0)
		handleKeyboardPlayer1(mKeyboard, dt, vp);
	else if(xboxController == 1)
		handleKeyboardPlayer2(mKeyboard, dt, vp);
}
void F14Controlls::handleKeyboardPlayer1( OIS::Keyboard* mKeyboard, float dt, Viewport* vp)
{
	float speed			= 0;
	float boost			= 0;

	float roll			= 0;
	bool rollFast		= 0;
	float pitch			= 0;
	bool pitchFast		= 0;
		
	bool greenPressed	= 0;
	bool redPressed		= 0;
	bool bluePressed	= 0;
	bool yellowPressed	= 0;
	bool shoot			= 0;
	if(!f14->f14Destroyed)		
	{
		if( mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			speed = 1.0;

		if( mKeyboard->isKeyDown(OIS::KC_F))
			boost = 1.0;

		if( mKeyboard->isKeyDown(OIS::KC_A))
			roll = -1.0;

		if( mKeyboard->isKeyDown(OIS::KC_D))
			roll = 1.0;

		if( mKeyboard->isKeyDown(OIS::KC_C))
			rollFast = true;

		if( mKeyboard->isKeyDown(OIS::KC_W))
			pitch = 1.0;

		if( mKeyboard->isKeyDown(OIS::KC_S))
			pitch = -1.0;

		if( mKeyboard->isKeyDown(OIS::KC_C))
			pitchFast = true;

		if( mKeyboard->isKeyDown(OIS::KC_1))
			greenPressed = true;

		if( mKeyboard->isKeyDown(OIS::KC_2))
			redPressed= true;

		if( mKeyboard->isKeyDown(OIS::KC_3))
			bluePressed= true;

		if( mKeyboard->isKeyDown(OIS::KC_4))
			yellowPressed = true;

		
		handleInputedValues(vp,speed,boost,roll,rollFast,pitch,pitchFast,greenPressed,redPressed,bluePressed,yellowPressed, shoot);
	}		
}
void F14Controlls::handleKeyboardPlayer2( OIS::Keyboard* mKeyboard, float dt, Viewport* vp)
{
	float speed			= 0;
	float boost			= 0;

	float roll			= 0;
	bool rollFast		= 0;
	float pitch			= 0;
	bool pitchFast		= 0;
		
	bool greenPressed	= 0;
	bool redPressed		= 0;
	bool bluePressed	= 0;
	bool yellowPressed	= 0;
	bool shoot			= 0;
	if(!f14->f14Destroyed)		
	{
		if( mKeyboard->isKeyDown(OIS::KC_RSHIFT))
			speed = 1.0;

		if( mKeyboard->isKeyDown(OIS::KC_RETURN))
			boost = 1.0;

		if( mKeyboard->isKeyDown(OIS::KC_J))
			roll = -1.0;

		if( mKeyboard->isKeyDown(OIS::KC_L))
			roll = 1.0;

		if( mKeyboard->isKeyDown(OIS::KC_H))
			rollFast = true;

		if( mKeyboard->isKeyDown(OIS::KC_I))
			pitch = 1.0;

		if( mKeyboard->isKeyDown(OIS::KC_K))
			pitch = -1.0;

		if( mKeyboard->isKeyDown(OIS::KC_H))
			pitchFast = true;

		if( mKeyboard->isKeyDown(OIS::KC_7))
			greenPressed = true;

		if( mKeyboard->isKeyDown(OIS::KC_8))
			redPressed= true;

		if( mKeyboard->isKeyDown(OIS::KC_9))
			bluePressed= true;

		if( mKeyboard->isKeyDown(OIS::KC_0))
			yellowPressed = true;

		handleInputedValues(vp,speed,boost,roll,rollFast,pitch,pitchFast,greenPressed,redPressed,bluePressed,yellowPressed, shoot);
	}		
}
void F14Controlls::handleInputedValues(Viewport* vp, float speed, float boost, float roll,bool rollFast,float pitch, bool pitchFast, bool greenPressed, bool redPressed, bool bluePressed, bool yellowPressed, bool shoot)
{
//SPEED
	f14->addSpeed(speed);

	//PITCH CONTROLL
	if(pitchFast)
	{
		if(pitch > 0)
			f14->pitchUp(Degree(pitch * 6));
		else if(pitch  < 0)
			f14->pitchDown(Degree(pitch * 6));
		else
			f14->pitchToCenter(Radian(0));
	}
	else
	{
		if(pitch > 0)
			f14->pitchUp(Degree(pitch * 3));
		else if(pitch  < 0)
			f14->pitchDown(Degree(pitch * 3));
		else
			f14->pitchToCenter(Radian(0));
	}
	
	//ROLL COMANDOS
	if(rollFast)
	{
		if( roll > 0.3)
			f14->rollRight(Radian(roll),true);
		else if( roll < -0.3)
			f14->rollLeft(Radian(roll),true);
		else
			f14->rotZ = 0;
	}
	else
	{
		if( roll > 0.3)
			f14->rollRight(Radian(roll));
		else if( roll < -0.3)
			f14->rollLeft(Radian(roll));
		else
			f14->rotZ = 0;
	}
		
	if(f14->boost > 0)
	{
		if(boost)
		{
			f14->activateBoost(true);
			Ogre::CompositorManager::getSingleton().setCompositorEnabled(vp, "Radial Blur", true);
		}
		else
		{
			f14->activateBoost(false);
			Ogre::CompositorManager::getSingleton().setCompositorEnabled(vp, "Radial Blur", false);
		}
	}
	else
		Ogre::CompositorManager::getSingleton().setCompositorEnabled(vp, "Radial Blur", false);

	//COLOR
	if(f14->color > 0)
	{
		//Smoke
		//GREEN
		if(  greenPressed && timeUntilNextToggleGreen <= 0)
		{
			f14->setGreenEmitterEnable(true);
			timeUntilNextToggleGreen = 0.5;
		}
		//RED
		if( redPressed && timeUntilNextToggleRed <= 0)
		{
			f14->setRedEmitterEnable(true);
			timeUntilNextToggleRed = 0.5;
		}

		//Blue
		if( bluePressed && timeUntilNextToggleBlue <= 0)
		{
			f14->setBlueEmitterEnable(true);
			timeUntilNextToggleBlue = 0.5;
		}

		//Yellow
		if( yellowPressed && timeUntilNextToggleYellow <= 0)
		{
			f14->setYellowEmitterEnable(true);
			timeUntilNextToggleYellow = 0.5;
		}		
	}

	if(shoot)
		f14->shootRocket();
}
void F14Controlls::updateXboxControlls(float dt, Viewport* vp)
{
	handleToggleValues(dt);
	if(!f14->f14Destroyed)		
	{
		
			float speed			= xboxDataManager->controller[xboxController].rightTrigger/255.0f;
			float boost			= xboxDataManager->controller[xboxController].leftTrigger/255;

			float roll			= xboxDataManager->controller[xboxController].getLXRel();
			bool rollFast		= xboxDataManager->controller[xboxController].lbPressed;
			float pitch			= xboxDataManager->controller[xboxController].getRYRel();
			bool pitchFast		= xboxDataManager->controller[xboxController].lbPressed;
			//float leftRight		= -xboxDataManager->controller[0].getRXRel();
			
			bool greenPressed	= xboxDataManager->controller[xboxController].aPressed;
			bool redPressed		= xboxDataManager->controller[xboxController].bPressed;
			bool bluePressed	= xboxDataManager->controller[xboxController].xPressed;
			bool yellowPressed	= xboxDataManager->controller[xboxController].yPressed;
			bool shoot			= xboxDataManager->controller[xboxController].rbPressed;

			handleInputedValues(vp,speed,boost,roll,rollFast,pitch,pitchFast,greenPressed,redPressed,bluePressed,yellowPressed, shoot);
	}
}
void F14Controlls::handleToggleValues(float dt)
{
	if (timeUntilNextToggleRed >= 0)
		timeUntilNextToggleRed -= dt;
	if (timeUntilNextToggleGreen >= 0)
		timeUntilNextToggleGreen -= dt;
	if (timeUntilNextToggleBlue >= 0)
		timeUntilNextToggleBlue -= dt;
	if (timeUntilNextToggleYellow >= 0)
		timeUntilNextToggleYellow -= dt;
}