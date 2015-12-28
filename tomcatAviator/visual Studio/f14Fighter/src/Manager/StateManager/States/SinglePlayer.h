#ifndef _SINGLE_PLAYER_H_
#define _SINGLE_PLAYER_H_

#include "../State.h"
#include "../StateManager.h"
#include "../../SettingManager/SettingManager.h"
#include "Ogre.h"

#include <CEGUI/CEGUI.h>
#include <OIS/OIS.h>
#include <OgreCEGUIRenderer.h>

#include "../../../Objects/F14.h"
#include "../../../Objects/Finish.h"
#include "../../../Objects/Torus.h"
#include "../../../Objects/RunWay.h"
#include "../../../other/CollisionHandler.h"
#include "../../../other/CEGUIKeyboard.h"


using namespace Ogre;

class SinglePlayer : public State {
	
public:
	SinglePlayer(StateManager *stateManager);
	~SinglePlayer();

	virtual bool					frameStarted(const FrameEvent& evt);
	virtual bool					frameEnded(const FrameEvent& evt);
	virtual bool					processUnbufferedKeyInput(const FrameEvent& evt, OIS::Keyboard* mKeyboard);
	virtual bool					processUnbufferedMouseInput(const FrameEvent& evt, OIS::Mouse* mMouse, const OIS::MouseState* ms);
	virtual bool					processUnbufferedXBOXControllerInput(const FrameEvent& evt);

private:
	virtual void					setup(void);
	virtual void					createScene(void);
	virtual void					createLights(void);
	virtual void					setupGUI(void);
	virtual void					setupEventHandler(void);
	
	void							updateGameIsRunning(const FrameEvent& evt);
	void							updateGameIsWon(const FrameEvent& evt);
	void							updateGUI(float dt);
	
	void							handleCollisionDetection(const FrameEvent& evt);
	void							handleTorusCollision(Torus* torus, bool extra);
	void							handleF14TorusCollision();
	void							handleF14RunwayCollision();
	void							handleF14HydraxCollision();
	void							handleF14WorldGeometryCollision();
	void							handleF14FinishCollision();

	void							handleTorusRotation(float dt);
	void							handleDeleteDestroyedTorus(float dt);
	void							handleToggleValues(float dt);
	int								currentState;

	F14*							f14;
	Finish*							finish;
	std::vector<Torus*>				torus;
	RunWay*							runWay;

	RaySceneQuery*					raySceneQuery;

	//CEGUI
	CEGUI::WindowManager*					CEGUIWin;
    CEGUI::Window*							CEGUISheet;

	CEGUI::ProgressBar*						boostBar;
	CEGUI::ProgressBar*						colorBar;
	CEGUI::ProgressBar*						speedBar;
	
	CEGUI::Window*							boostText;
	CEGUI::Window*							colorText;
	CEGUI::Window*							speedText;
	CEGUI::Window*							infoBox;

	CEGUI::Window*							timeWindow;
	CEGUI::Window*							highScore;

	CEGUI::Window*							centerTextWindow;
	
	
	Real									timeUntilNextToggleRed;
	Real									timeUntilNextToggleYellow;
	Real									timeUntilNextToggleBlue;
	Real									timeUntilNextToggleGreen;
	Real									timeUntilNextToggleInfobox;
	double									timeStampStartSinglePlayer;
	double									timeStampStopSinglePlayer;

	float									elapsedTime;
	float									collectedTime;
	CEGUIKeyboard							ceguiKeyboard;
	bool									isHighscoreSaved;
	
	SettingManager							settingManager;

};

#endif
