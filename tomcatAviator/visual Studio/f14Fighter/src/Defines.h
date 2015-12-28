#ifndef F14_CONSTANTS_H_
#define F14_CONSTANTS_H_
#include "Ogre.h"

namespace F14FIGHTER 
{
	namespace Controller
	{
		enum {XBOXCONTROLLER, KEYBOARD};
	}
	namespace F14
	{
		enum {START_PHASE, FLYING_PHASE, TAKE_OFF};
	}
	namespace MENU
	{
		enum { NOTHING_SELECTED, NEW_GAME, MULTIPLAYER, MULTIPLAYER_RACE, LOADING_SCREEN, MENU, ABOUT};
	}
	namespace SINGLEPLAYER 
	{ 
		enum { COUNTDOWN, GAME_IS_RUNNING, GAME_OVER, WIN, BACK_TO_MENU };
	}
	namespace MULTIPLAYER 
	{ 
		enum { COUNTDOWN, GAME_IS_RUNNING, GAME_END, WIN, BACK_TO_MENU };
	}
	namespace MULTIPLAYERRACE 
	{ 
		enum { COUNTDOWN, GAME_IS_RUNNING, GAME_END, WIN, BACK_TO_MENU };
	}
	namespace TIMER
	{
		const float NOT_INITIALIZED = -101.0;
	}
	namespace TORUS
	{
		enum{ NOTHING, YELLOW, BLUE, GREEN, RED };
	}
	namespace Palms
	{
		const int NUMBER_OF_PALMS					= 3;
		const Ogre::Vector3 PALMS[NUMBER_OF_PALMS] = {	Ogre::Vector3(1382,111,11776),
														Ogre::Vector3(1415,110,11652),
														Ogre::Vector3(1356,129,11004)  };
	}
	
	
	
}
#endif