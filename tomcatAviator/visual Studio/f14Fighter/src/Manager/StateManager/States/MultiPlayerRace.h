#ifndef _MULTIPLAYER_RACE_H_
#define _MULTIPLAYER_RACE_H_

#define NUMBER_OF_PLAYERS 2
#include "../../../Defines.h"
#include "../State.h"
#include "../StateManager.h"
#include "../../SettingManager/SettingManager.h"
#include "Hydrax.h"
#include "../../../Objects/F14.h"
#include "../../../Objects/Torus.h"
#include "../../../Objects/RunWay.h"
#include "../../../Objects/Finish.h"

#include "Ogre.h"

#include <CEGUI/CEGUI.h>
#include <OIS/OIS.h>
#include <OgreCEGUIRenderer.h>

using namespace Ogre;

class MultiPlayerRace : public State {

public:
	MultiPlayerRace(StateManager *stateManager);
	~MultiPlayerRace();

	virtual bool			frameStarted(const FrameEvent& evt);
	virtual bool			frameEnded(const FrameEvent& evt);
	virtual bool			processUnbufferedKeyInput(const FrameEvent& evt, OIS::Keyboard* mKeyboard);
	virtual bool			processUnbufferedMouseInput(const FrameEvent& evt, OIS::Mouse* mMouse, const OIS::MouseState* ms);
	virtual bool			processUnbufferedXBOXControllerInput(const FrameEvent& evt);

private:
	virtual void			setup();
	virtual void			createScene(void);
	virtual void			createLights(void);
	virtual void			setupGUI(void);
	void					setupGuiForPlayer(int playerNumber);
	virtual void			setupEventHandler(void);
	void					updateGui(const FrameEvent& evt);
	void					createCamera(void);
	
	void					handleRespawn(int player);
	void					handleCollisionDetection(int player, const FrameEvent& evt);
	void					handleTorusCollision(int player, Torus* torus, bool extra);
	void					handleF14Collision();
	void					handleTerrainCollision(int player, const FrameEvent& evt);
	void					handleTorusRotation(float dt);
	void					handleDeleteDestroyedTorus(float dt);
	void					handleToggleValues(float dt);

	void					handleF14TorusCollision(int player);
	void					handleF14RunwayCollision(int player);
	void					handleF14WorldGeometryCollision(int player);

	void					handleF14FinishCollision(int player);

	void					updateCountdown(const FrameEvent& evt);
	void					updateGameIsRunning(const FrameEvent& evt);
	void					updateGameEnd(const FrameEvent& evt);
	void					updateGUI();

	Camera*					camera1;
	Camera*					camera2;
	Camera*					camera3;
	F14*					f14Player[NUMBER_OF_PLAYERS];
	RunWay*					runWay;
	Finish*					finish;
	std::vector<Torus*>		torus;
	std::vector<SceneNode*> terrain;
	
	
	Entity*					terrainCubeBoundingEntity[2];
	SceneNode*				terrainCubeBoundingSceneNode[2];

	Viewport*				vp[2];
	int						currentState;
	double					timeStampStartMultiPlayer;
	float					elapsedTime;

	
	//CEGUI
	CEGUI::WindowManager*	CEGUIWin;
    CEGUI::Window*			CEGUISheet;

	CEGUI::ProgressBar*		boostBar[NUMBER_OF_PLAYERS];
	CEGUI::ProgressBar*		colorBar[NUMBER_OF_PLAYERS];
	CEGUI::ProgressBar*		speedBar[NUMBER_OF_PLAYERS];
	
	CEGUI::Window*			boostText[NUMBER_OF_PLAYERS];
	CEGUI::Window*			colorText[NUMBER_OF_PLAYERS];
	CEGUI::Window*			speedText[NUMBER_OF_PLAYERS];
	CEGUI::Window*			infoBox[NUMBER_OF_PLAYERS];
	

	CEGUI::Window*			centerTextWindow[NUMBER_OF_PLAYERS];
	RaySceneQuery*			raySceneQuery;

	SettingManager			settingManager;

	Real					timeUntilNextToggleInfoboxPlayer[NUMBER_OF_PLAYERS];

	int						winner;
};

#endif
