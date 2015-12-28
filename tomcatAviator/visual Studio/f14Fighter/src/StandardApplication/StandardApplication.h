#ifndef __StandardApplication_H__
#define __StandardApplication_H__

#include "Ogre.h"
#include "OgreConfigFile.h"
#include "ExampleLoadingBar.h"

#include "StandardFrameListener.h"
#include "../Manager/DataManager/DataManager.h"

#include <CEGUI/CEGUI.h>
#include <OIS/OIS.h>
#include <OgreCEGUIRenderer.h>


#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#include <CoreFoundation/CoreFoundation.h>

// This function will locate the path to our application on OS X,
// unlike windows you can not rely on the curent working directory
// for locating your configuration files and resources.
std::string macBundlePath()
{
    char path[1024];
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    assert(mainBundle);

    CFURLRef mainBundleURL = CFBundleCopyBundleURL(mainBundle);
    assert(mainBundleURL);

    CFStringRef cfStringRef = CFURLCopyFileSystemPath( mainBundleURL, kCFURLPOSIXPathStyle);
    assert(cfStringRef);

    CFStringGetCString(cfStringRef, path, 1024, kCFStringEncodingASCII);

    CFRelease(mainBundleURL);
    CFRelease(cfStringRef);

    return std::string(path);
}
#endif

using namespace Ogre;

/** Base class which manages the standard startup of an Ogre application.
    Designed to be subclassed for specific examples if required.
*/
class StandardApplication
{
	public:
		StandardApplication();
		virtual ~StandardApplication();
	
	//Methods:
		virtual void				go(void);
	protected:  
		virtual bool				setup(void);
		virtual bool				configure(void);
		virtual void				chooseSceneManager(void);
		virtual void				createCamera(void);
		virtual void				createFrameListener(void);
		virtual void				createScene(void) = 0;
		virtual void				createLights(void) = 0;
		virtual void				setupCEGUI(void) = 0;
		virtual void				createState(void) = 0;
		virtual void				destroyScene(void);
		virtual void				createViewports(void);
		virtual void				setupResources(void);
		virtual void				createResourceListener(void);
		virtual void				loadResources(void);

	//Attributes:
		Root*						_root;
		Camera*						_camera;
		SceneManager*				_sceneManager;
		StandardFrameListener*		_frameListener;
		RenderWindow*				_window;
		Ogre::String				_resourcePath;
		DataManager*				_dataManager;

	   CEGUI::System*				mSystem;
	   CEGUI::OgreCEGUIRenderer*	mRenderer;
	   ExampleLoadingBar			mLoadingBar;

};


#endif
