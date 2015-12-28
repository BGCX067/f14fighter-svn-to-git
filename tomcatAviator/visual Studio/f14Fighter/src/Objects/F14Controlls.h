#ifndef _F14_CONTROLLS_H_
#define _F14_CONTROLLS_H_
#include "Ogre.h"
#include "../XboxController/XboxDataManager.h"
#include <OIS/OIS.h>

using namespace Ogre;
class F14;
class F14Controlls
{
public:
	F14Controlls(int xboxController, F14* f14);
	~F14Controlls(void);
	void					updateXboxControlls(float dt, Viewport* vp);
	void					updateKeyboardControlls( OIS::Keyboard* mKeyboard, float dt, Viewport* vp);

	void					handleToggleValues(float dt);

private:
	void					handleInputedValues(Viewport* vp, float speed, float boost, float roll,bool rollFast,float pitch, bool pitchFast, bool greenPressed, bool redPressed, bool bluePressed, bool yellowPressed, bool shoot);
	void					handleKeyboardPlayer1( OIS::Keyboard* mKeyboard, float dt, Viewport* vp);
	void					handleKeyboardPlayer2( OIS::Keyboard* mKeyboard, float dt, Viewport* vp);
	int						xboxController;
	F14*					f14;
	XboxDataManager*		xboxDataManager;

	Real					timeUntilNextToggleRed;
	Real					timeUntilNextToggleYellow;
	Real					timeUntilNextToggleBlue;
	Real					timeUntilNextToggleGreen;
};

#endif