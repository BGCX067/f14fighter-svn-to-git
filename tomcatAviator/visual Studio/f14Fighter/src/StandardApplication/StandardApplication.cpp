#include "StandardApplication.h"
//---------------------------------------------------------------------------
StandardApplication::StandardApplication()
: mSystem(0), mRenderer(0)
{
    _frameListener = 0;
    _root = 0;
	// Provide a nice cross platform solution for locating the configuration files
	// On windows files are searched for in the current working directory, on OS X however
	// you must provide the full path, the helper function macBundlePath does this for us.
	#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
		_resourcePath = macBundlePath() + "/Contents/Resources/";
	#else
		_resourcePath = "";
	#endif
		_dataManager = DataManager::getDataManagerAsSingleton();
}
//---------------------------------------------------------------------------
StandardApplication::~StandardApplication()
{
    
	if (mSystem)
        delete mSystem;

    if (mRenderer)
        delete mRenderer;

	if (_frameListener)
        delete _frameListener;
    if (_root)
        delete _root;
}

//---------------------------------------------------------------------------
void StandardApplication::go(void)
{
    if (!setup())
        return;

    _root->startRendering();

    // clean up
    destroyScene();
}

//---------------------------------------------------------------------------
// These internal methods package up the stages in the startup process
/** Sets up the application - returns false if the user chooses to abandon configuration. */
bool StandardApplication::setup(void)
{

	String pluginsPath;
	// only use plugins.cfg if not static
	#ifndef OGRE_STATIC_LIB
		pluginsPath = _resourcePath + "plugins.cfg";
	#endif
	
    _root = OGRE_NEW Root(pluginsPath, 
        _resourcePath + "ogre.cfg", _resourcePath + "Ogre.log");
	
	
    setupResources();

    bool carryOn = configure();
    if (!carryOn) 
		return false;

    chooseSceneManager();
	_dataManager->sceneManager		= _sceneManager;
	
    createCamera();
	_dataManager->camera			=_camera;
    createViewports();

    // Set default mipmap level (NB some APIs ignore this)
    TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// Create any resource listeners (for loading screens)
	createResourceListener();
	// Load resources
	loadResources();

	// Create the scene
    createScene();
	setupCEGUI();
	createLights();

    createFrameListener();

	//Ogre::ControllerManager::getSingleton().setFrameDelay();
	
	//FILL DataManager
	
	_dataManager->root			 = _root;
	createState();

    return true;

}
//---------------------------------------------------------------------------
/** Configures the application - returns false if the user chooses to abandon configuration. */
bool StandardApplication::configure(void)
{

    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(_root->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        _window = _root->initialise(true);
		
        return true;
    }
    else
    {
        return false;
    }

	
}

//---------------------------------------------------------------------------
 void StandardApplication::chooseSceneManager(void)
{
    // Create the SceneManager, in this case a generic one
    _sceneManager = _root->createSceneManager(ST_GENERIC, "ExampleSMInstance");
}
 
//---------------------------------------------------------------------------
void StandardApplication::createCamera(void)
{
    // Create the camera
    _camera = _sceneManager->createCamera("myCamera");

    // Position it at 500 in Z direction
    //_camera->setPosition(Vector3(0,0,500));
    // Look back along -Z
    _camera->lookAt(Vector3(0,0,-300));
    _camera->setNearClipDistance(5);
}

//---------------------------------------------------------------------------
void StandardApplication::createFrameListener(void)
{
    _frameListener= new StandardFrameListener(_window, _camera);
    _frameListener->showDebugOverlay(true);
    _root->addFrameListener(_frameListener);
}

//---------------------------------------------------------------------------
void StandardApplication::destroyScene(void)
{
}    // Optional to override this

//---------------------------------------------------------------------------
void StandardApplication::createViewports(void)
{
    // Create one viewport, entire window
    Viewport* vp = _window->addViewport(_camera);
    vp->setBackgroundColour( ColourValue(0,0,0) );

    // Alter the camera aspect ratio to match the viewport
    _camera->setAspectRatio( Real(vp->getActualWidth()) / Real( vp->getActualHeight() ) );
	
	_dataManager->window		 = _window;
}

//---------------------------------------------------------------------------
/// Method which will define the source of resources (other than current folder)
void StandardApplication::setupResources(void)
{
    // Load resource paths from config file
    ConfigFile cf;
    cf.load(_resourcePath + "resources.cfg");

    // Go through all sections & settings in the file
    ConfigFile::SectionIterator seci = cf.getSectionIterator();

    String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
		std::cout << "##################################################################" << std::endl;
		std::cout << "SECTION NAME: "<< secName << std::endl;
		std::cout << "##################################################################" << std::endl;
        ConfigFile::SettingsMultiMap *settings = seci.getNext();
        ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
	#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
				// OS X does not set the working directory relative to the app,
				// In order to make things portable on OS X we need to provide
				// the loading with it's own bundle path location
				ResourceGroupManager::getSingleton().addResourceLocation(
					String(macBundlePath() + "/" + archName), typeName, secName);
	#else
				ResourceGroupManager::getSingleton().addResourceLocation(
					archName, typeName, secName);
	#endif
        }
    }
	
}

//---------------------------------------------------------------------------
/// Optional override method where you can create resource listeners (e.g. for loading screens)
void StandardApplication::createResourceListener(void)
{

}

//---------------------------------------------------------------------------
/// Optional override method where you can perform resource group loading
/// Must at least do ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
void StandardApplication::loadResources(void)
{
	mLoadingBar.start(_window, 1, 1, 0.98);
	// Initialise, parse scripts etc
	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	mLoadingBar.finish();
}
