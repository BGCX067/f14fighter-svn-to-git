#ifndef _MY_TIMER_H_
#define _MY_TIMER_H_
#include "Ogre.h"

using namespace Ogre;

class MyTimer
{
public:
	MyTimer(void);
	~MyTimer(void);
	void					updateTimer(float dt);
	float					getElapsedTime();
	static std::string		getMinutesAndSecondsFormated(double _seconds);

private:
	float					elapsedTime;
};

#endif