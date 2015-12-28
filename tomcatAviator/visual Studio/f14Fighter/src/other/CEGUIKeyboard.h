#ifndef _CEGUI_KEYBOARD_H_
#define _CEGUI_KEYBOARD_H_

#include <CEGUI/CEGUI.h>
#include <OIS/OIS.h>
#include <OgreCEGUIRenderer.h>
#include "Ogre.h"

using namespace Ogre;

class DataManager;
class CEGUIKeyboard
{
public:
	CEGUIKeyboard(void);
	~CEGUIKeyboard(void);
	void							setupGUI(float positionX,float positionY);
	void							setupEventHandler(void);
	void							updateKeyboard(void);
	CEGUI::WindowManager*			CEGUIWin;
    CEGUI::Window*					CEGUISheet;
	DataManager*					dataManager;
	bool							showKeyboard;
	std::string						inputText;

	CEGUI::Window*					text;

	CEGUI::Window*					buttonA;
	CEGUI::Window*					buttonB;
	CEGUI::Window*					buttonC;
	CEGUI::Window*					buttonD;
	CEGUI::Window*					buttonE;
	CEGUI::Window*					buttonF;
	CEGUI::Window*					buttonG;
	CEGUI::Window*					buttonH;
	CEGUI::Window*					buttonI;
	CEGUI::Window*					buttonJ;
	CEGUI::Window*					buttonK;
	CEGUI::Window*					buttonL;
	CEGUI::Window*					buttonM;
	CEGUI::Window*					buttonN;
	CEGUI::Window*					buttonO;
	CEGUI::Window*					buttonP;
	CEGUI::Window*					buttonQ;
	CEGUI::Window*					buttonR;
	CEGUI::Window*					buttonS;
	CEGUI::Window*					buttonT;
	CEGUI::Window*					buttonU;
	CEGUI::Window*					buttonV;
	CEGUI::Window*					buttonW;
	CEGUI::Window*					buttonX;
	CEGUI::Window*					buttonY;
	CEGUI::Window*					buttonZ;
	
	CEGUI::Window*					buttonAT;
	CEGUI::Window*					buttonATFhsalzburg;
	CEGUI::Window*					buttonATGmx;
	CEGUI::Window*					buttonATHotmail;
	CEGUI::Window*					buttonATGmail;
	CEGUI::Window*					buttonATYahoo;
	
	CEGUI::Window*					buttonDot;
	CEGUI::Window*					buttonUnderline;
	CEGUI::Window*					buttonMinus;
	
	CEGUI::Window*					buttonDel;
	CEGUI::Window*					buttonReturn;

	bool							aPressed(const CEGUI::EventArgs &e);
	bool							bPressed(const CEGUI::EventArgs &e);
	bool							cPressed(const CEGUI::EventArgs &e);
	bool							dPressed(const CEGUI::EventArgs &e);
	bool							ePressed(const CEGUI::EventArgs &e);
	bool							fPressed(const CEGUI::EventArgs &e);
	bool							gPressed(const CEGUI::EventArgs &e);
	bool							hPressed(const CEGUI::EventArgs &e);
	bool							iPressed(const CEGUI::EventArgs &e);
	bool							jPressed(const CEGUI::EventArgs &e);
	bool							kPressed(const CEGUI::EventArgs &e);
	bool							lPressed(const CEGUI::EventArgs &e);
	bool							mPressed(const CEGUI::EventArgs &e);
	bool							nPressed(const CEGUI::EventArgs &e);
	bool							oPressed(const CEGUI::EventArgs &e);
	bool							pPressed(const CEGUI::EventArgs &e);
	bool							qPressed(const CEGUI::EventArgs &e);
	bool							rPressed(const CEGUI::EventArgs &e);
	bool							sPressed(const CEGUI::EventArgs &e);
	bool							tPressed(const CEGUI::EventArgs &e);
	bool							uPressed(const CEGUI::EventArgs &e);
	bool							vPressed(const CEGUI::EventArgs &e);
	bool							wPressed(const CEGUI::EventArgs &e);
	bool							xPressed(const CEGUI::EventArgs &e);
	bool							yPressed(const CEGUI::EventArgs &e);
	bool							zPressed(const CEGUI::EventArgs &e);
	
	bool							buttonATPressed(const CEGUI::EventArgs &e);
	bool							buttonATFhsalzburgPressed(const CEGUI::EventArgs &e);
	bool							buttonATGmxPressed(const CEGUI::EventArgs &e);
	bool							buttonATHotmailPressed(const CEGUI::EventArgs &e);
	bool							buttonATGmailPressed(const CEGUI::EventArgs &e);
	bool							buttonATYahooPressed(const CEGUI::EventArgs &e);
	
	bool							delPressed(const CEGUI::EventArgs &e);
	bool							returnPressed(const CEGUI::EventArgs &e);

	bool							buttonDotPressed(const CEGUI::EventArgs &e);
	bool							buttonUnderlinePressed(const CEGUI::EventArgs &e);
	bool							buttonMinusPressed(const CEGUI::EventArgs &e);

};

#endif