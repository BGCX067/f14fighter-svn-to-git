#include "MyController.h"

MyController::MyController(void)
:	lx(0), ly(0), rx(0), ry(0), leftTrigger(0), rightTrigger(0), aPressed(false), bPressed(false),
	xPressed(false), yPressed(false), downPressed(false), leftPressed(false), rightPressed(false),
	upPressed(false), backPressed(false), startPressed(false),	lbPressed(false), rbPressed(false), 
	leftThumbPressed(false), rightThumbPressed(false), MAXIMUM_LEFT_TRIGGER_VALUE(255),MAXIMUM_RIGHT_TRIGGER_VALUE(255),
	MAX_JOY_VALUE(32768.0f), MIN_JOY_VALUE(-32768.0f), player(0)
{
}

MyController::~MyController(void)
{
}

float MyController::getLXRel()
{
	return lx/MAX_JOY_VALUE;
}

float MyController::getLYRel()
{
	return ly/MAX_JOY_VALUE;
}

float MyController::getRXRel()
{
	return rx/MAX_JOY_VALUE;
}

float MyController::getRYRel()
{
	return ry/MAX_JOY_VALUE;
}