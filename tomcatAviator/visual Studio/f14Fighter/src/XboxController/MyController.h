#ifndef _MY_CONTROLLER_H_
#define _MY_CONTROLLER_H_
#include "XBOXController.h"

class MyController
{
public:
	MyController(void);
	~MyController(void);
	
	XBOXController*				player;
	
	float						getLXRel();
	float						getLYRel();

	float						getRXRel();
	float						getRYRel();

	//JOYS
	int							lx;
	int							ly;
	int							rx;
	int							ry;
	const float					MAX_JOY_VALUE;
	const float					MIN_JOY_VALUE;

	//TRIGGER
	int							leftTrigger;
	int							rightTrigger;
	const int					MAXIMUM_LEFT_TRIGGER_VALUE;
	const int					MAXIMUM_RIGHT_TRIGGER_VALUE;
	//BUTTONS
	bool						aPressed;
	bool						bPressed;
	bool						xPressed;
	bool						yPressed;
	
	//DPAD
	bool						downPressed;
	bool						leftPressed;
	bool						rightPressed;
	bool						upPressed;
	
	//BACK START
	bool						backPressed;
	bool						startPressed;

	//SHOULDER
	bool						lbPressed;
	bool						rbPressed;

	//THUMBS
	bool						leftThumbPressed;
	bool						rightThumbPressed;


};
#endif