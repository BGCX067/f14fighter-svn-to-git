#include "F14Fighter.h"

//---------------------------------------------------------------------------
F14Fighter::F14Fighter()
{
	dataManagerMenu = DataManagerMenu::getDataManagerAsSingleton();
	xboxDataManager = XboxDataManager::getDataManagerAsSingleton();
	srand(time(0));

	_dataManager->xboxThread = new XboxControllerThread();
	_dataManager->thread= new Thread(_dataManager->xboxThread);
	_dataManager->thread->start();	


}

//---------------------------------------------------------------------------
F14Fighter::~F14Fighter()
{

}

//---------------------------------------------------------------------------
void F14Fighter::createCamera(void)
{
	// Create the camera
	_camera = _sceneManager->createCamera("myCamera");
	_camera->setNearClipDistance(0.1);
    _camera->setFarClipDistance(99999);
	_dataManager->camera = _camera;
}

//---------------------------------------------------------------------------
bool F14Fighter::configure(void)
{
	// Show the configuration dialog and initialise the system
	// You can skip this and use root.restoreConfig() to load configuration
	// settings if you were sure there are valid ones saved in ogre.cfg
	if(_root->restoreConfig() || _root->showConfigDialog())
	{
		// If returned true, user clicked OK so initialise
		// Here we choose to let the system create a default rendering window by passing 'true'
		_window = _root->initialise(true);
		// Let's add a nice window icon
	#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		HWND hwnd;
		_window->getCustomAttribute("WINDOW", (void*)&hwnd);
		LONG iconID   = (LONG)LoadIcon( GetModuleHandle(0), MAKEINTRESOURCE(IDI_APPICON) );
		SetClassLong( hwnd, GCL_HICON, iconID );
	#endif		
		_root->saveConfig();
		return true;
	}
	else
	{
		return false;
	}
}
void F14Fighter::chooseSceneManager(void)
{
    // Create the SceneManager
	_sceneManager = _root->createSceneManager("TerrainSceneManager");
}
//---------------------------------------------------------------------------
void F14Fighter::setupCEGUI(void)
{
	
	mRenderer = new CEGUI::OgreCEGUIRenderer(_window, Ogre::RENDER_QUEUE_OVERLAY, false, 3000, _sceneManager);
	mSystem = new CEGUI::System(mRenderer);
	
	
	_dataManager->CEGUIRenderer = mRenderer;
	_dataManager->CEGUISystem = mSystem;
	
	//Select SKIN of cegui
	CEGUI::SchemeManager::getSingleton().loadScheme((CEGUI::utf8*)"TaharezLookSkin.scheme");
	
	//select Mouse cursor
	mSystem->setDefaultMouseCursor((CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"MouseArrow"); 
	mSystem->setDefaultFont((CEGUI::utf8*)"BlueHighway-12");
	//CEGUI::MouseCursor::getSingleton().setImage("TaharezLook", "MouseArrow");
}

//---------------------------------------------------------------------------
// Just override the mandatory create scene method
void F14Fighter::createScene(void)
{
	
}
//---------------------------------------------------------------------------
void F14Fighter::createLights(void)
{
	// Set ambient light
	_sceneManager->setAmbientLight(ColourValue(1,1,1));

	// Create a light
	Light* l = _sceneManager->createLight("MainLight");
	l->setPosition(0,10000,0);
	l->setDiffuseColour(1,0.9,0.6);
	//_dataManager->mHydrax->setSunColor(Vector3(1, 0.9, 0.6));
}
//---------------------------------------------------------------------------
// Create new frame listener
void F14Fighter::createFrameListener(void)
{
	_frameListener= new F14FighterFrameListener(_sceneManager, _window, _camera);
	//physicsFrameListener = new OgreNewt::BasicFrameListener(_window, _dataManager->world);

	_root->addFrameListener(_frameListener);
	//_root->addFrameListener(physicsFrameListener);
}
//---------------------------------------------------------------------------
void F14Fighter::createPalms(void)
{

}

//---------------------------------------------------------------------------
void F14Fighter::createState(void)
{
	_dataManager->stateManager.createState(new Menu(&_dataManager->stateManager));
}
