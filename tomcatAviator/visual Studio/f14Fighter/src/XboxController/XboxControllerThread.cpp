#include "XboxControllerThread.h"
#include "XboxDataManager.h"

XboxControllerThread::XboxControllerThread()
{
	xboxDataManager = XboxDataManager::getDataManagerAsSingleton();
	Player[0] = new XBOXController(1);
	Player[1] = new XBOXController(2);
	Player[2] = new XBOXController(3);
	Player[3] = new XBOXController(4);
	
	for(int i = 0; i < 4; i++)
	{
		xboxDataManager->controller[0].player = Player[i];
		if(!Player[i]->IsConnected())
			std::cout << "\n\tERROR! PLAYER " << i+1 << " - XBOX 360 Controller Not Found!\n";
	}
}



XboxControllerThread::~XboxControllerThread(void)
{
	stop();
	for(int i = 0; i < 4; i ++)
	{
		std::cout << "deleted " << i << std::endl;
		delete(Player[i]);
	}
}

void XboxControllerThread::stop()
{
	
	_continue = false;
}

       

unsigned long XboxControllerThread::run()
{
	init();
	_continue=true;

	while(_continue)
	{
		checkXboxInput();
		Sleep(1);
	}
    return 0;
}


bool XboxControllerThread::init()
{

	return true;
}


void XboxControllerThread::checkXboxInput(void)
{
	for(int i = 0; i < 4; i++)
		{
			if(Player[i]->IsConnected())
			{
				//Player[i]->Vibrate(65535, 0);
				//THUMBS
				if( Player[i]->GetState().Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && Player[i]->GetState().Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE )
			    		xboxDataManager->controller[i].lx = 0;
				else
					xboxDataManager->controller[i].lx = Player[i]->GetState().Gamepad.sThumbLX;

				if( Player[i]->GetState().Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && Player[i]->GetState().Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE )
			    		xboxDataManager->controller[i].ly = 0;
				else
					xboxDataManager->controller[i].ly = Player[i]->GetState().Gamepad.sThumbLY;


				if( Player[i]->GetState().Gamepad.sThumbRX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && Player[i]->GetState().Gamepad.sThumbRX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE )
					xboxDataManager->controller[i].rx = 0;
				else
					xboxDataManager->controller[i].rx = Player[i]->GetState().Gamepad.sThumbRX;

				if( Player[i]->GetState().Gamepad.sThumbRY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && Player[i]->GetState().Gamepad.sThumbRY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE )
			    		xboxDataManager->controller[i].ry = 0;
				else
					xboxDataManager->controller[i].ry = Player[i]->GetState().Gamepad.sThumbRY;


				//TRIGGER
				if(Player[i]->GetState().Gamepad.bRightTrigger)
				{
					xboxDataManager->controller[i].rightTrigger = Player[i]->GetState().Gamepad.bRightTrigger;
				}
				else
					xboxDataManager->controller[i].rightTrigger = 0;

				if(Player[i]->GetState().Gamepad.bLeftTrigger)
				{
					xboxDataManager->controller[i].leftTrigger= Player[i]->GetState().Gamepad.bLeftTrigger;
				}
				else
					xboxDataManager->controller[i].leftTrigger= 0;

				//BUTTONS
				if(Player[i]->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
				{
					xboxDataManager->controller[i].aPressed = true;
					
				}
				else
					xboxDataManager->controller[i].aPressed = false;

				if(Player[i]->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
				{
					xboxDataManager->controller[i].bPressed = true;		
				}
				else
					xboxDataManager->controller[i].bPressed = false;

				if(Player[i]->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
				{
					xboxDataManager->controller[i].xPressed = true;
					
				}
				else
					xboxDataManager->controller[i].xPressed = false;


				if(Player[i]->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
				{
					xboxDataManager->controller[i].yPressed = true;
					
				}
				else
					xboxDataManager->controller[i].yPressed = false;


				//BACK START
				if(Player[i]->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
				{
					xboxDataManager->controller[i].backPressed = true;
					
				}
				else
					xboxDataManager->controller[i].backPressed = false;

				if(Player[i]->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START)
				{
					xboxDataManager->controller[i].startPressed= true;
					
				}
				else
					xboxDataManager->controller[i].startPressed= false;


				//shoulder
				if(Player[i]->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
				{
					xboxDataManager->controller[i].lbPressed= true;
				}
				else
					xboxDataManager->controller[i].lbPressed= false;


				if(Player[i]->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
				{
					xboxDataManager->controller[i].rbPressed= true;
				}
				else
					xboxDataManager->controller[i].rbPressed= false;


				//left thumb
				if(Player[i]->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
				{
					
					xboxDataManager->controller[i].rightThumbPressed= true;
				}
				else
					xboxDataManager->controller[i].rightThumbPressed= false;

				if(Player[i]->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
				{
					xboxDataManager->controller[i].leftThumbPressed= true;
					
				}
				else
					xboxDataManager->controller[i].leftThumbPressed= false;



				//DPAD
				if(Player[i]->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
				{
					xboxDataManager->controller[i].downPressed= true;
					
				}
				else
					xboxDataManager->controller[i].downPressed= false;

				if(Player[i]->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
				{
					xboxDataManager->controller[i].leftPressed= true;
					
				}
				else
					xboxDataManager->controller[i].leftPressed= false;

				if(Player[i]->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
				{
					xboxDataManager->controller[i].rightPressed= true;
					
				}
				else
					xboxDataManager->controller[i].rightPressed = false;


				if(Player[i]->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
				{
						xboxDataManager->controller[i].upPressed= true;

				}
				else
					xboxDataManager->controller[i].upPressed = false;
				
			}
			
		}
}
	
