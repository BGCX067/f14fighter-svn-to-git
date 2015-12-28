#include "MyTimer.h"

MyTimer::MyTimer(void)
: elapsedTime(0)
{
}

MyTimer::~MyTimer(void)
{
}
void MyTimer::updateTimer(float dt)
{
	elapsedTime += dt;
}
float MyTimer::getElapsedTime()
{
	return elapsedTime;
}
std::string MyTimer::getMinutesAndSecondsFormated(double _seconds)
{
	int minutes = _seconds / 60;
	int seconds = _seconds - minutes * 60;
	int centiSeconds = (_seconds - minutes * 60 - seconds) * 100;
	
	std::string resultMinutes = "";
	std::string resultSeconds = "";
	std::string resultCentiSeconds = "";

	if(minutes < 10)
		resultMinutes = "0" + StringConverter::toString(minutes);
	else
		resultMinutes = StringConverter::toString(minutes);

	if(seconds < 10)
		resultSeconds = "0" + StringConverter::toString(seconds);
	else
		resultSeconds = StringConverter::toString(seconds);
	
	if(centiSeconds < 10)
		resultCentiSeconds	= "0" + StringConverter::toString(centiSeconds);
	else
		resultCentiSeconds	= StringConverter::toString(centiSeconds);

	return resultMinutes + ":" + resultSeconds + ":" + resultCentiSeconds;
}