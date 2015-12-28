#pragma once
#include "Thread.h"

#include "XBOXController.h"
#include <iostream>

#define DXUT_INPUT_DEADZONE                 ( 0.24f * FLOAT(0x7FFF) )  // Default to 24% of the +/- 32767 range.

class XboxDataManager;
class XboxControllerThread : public IRunnable
{
	public:
	XboxControllerThread();

	~XboxControllerThread(void);

	virtual unsigned long run();
	bool init();
	virtual void stop();

	void checkXboxInput(void);
	XBOXController* Player[4];

	protected:
		bool _continue;		
		XboxDataManager*				xboxDataManager;
};
