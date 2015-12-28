#include "State.h"
#include "StateManager.h"
#include "../DataManager/DataManager.h"

//--------------------------------------------------------------
State::State(StateManager *stateManager)
{
	this->stateManager = stateManager;
	

}
//--------------------------------------------------------------
void State::setupState()
{
	
	dataManager = DataManager::getDataManagerAsSingleton();
	xboxDataManager = XboxDataManager::getDataManagerAsSingleton();
	setup();
	createScene();
	createLights();

	setupGUI();
	setupEventHandler();

}
//--------------------------------------------------------------
State::~State()
{
	dataManager->mHydrax->remove();
	dataManager->sceneManager->clearScene();	
}
//--------------------------------------------------------------
void State::createHydrax()
{	

	if(!dataManager->mHydrax)	
	{
		std::cout << "######################" << std::endl;
		std::cout << "# HYDRAX initialized #" << std::endl;
		std::cout << "######################" << std::endl;

		// Create Hydrax object
		dataManager->mHydrax = new Hydrax::Hydrax(dataManager->sceneManager, dataManager->camera, dataManager->window->getViewport(0));
		
		// Create our projected grid module  
		Hydrax::Module::ProjectedGrid *mModule = new Hydrax::Module::ProjectedGrid(dataManager->mHydrax,new Hydrax::Noise::Perlin(),Ogre::Plane(Ogre::Vector3(0,1,0), Ogre::Vector3(0,0,0)),Hydrax::MaterialManager::NM_VERTEX, Hydrax::Module::ProjectedGrid::Options(264));

		// Set our module
		dataManager->mHydrax->setModule(static_cast<Hydrax::Module::Module*>(mModule));

		dataManager->mHydrax->loadCfg("HydraxDemo.hdx");

		dataManager->mHydrax->getMaterialManager()->addDepthTechnique(static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("Island"))->createTechnique());
	}
	
	dataManager->mHydrax->create();
	
	std::cout << "##################" << std::endl;
	std::cout << "# HYDRAX created #" << std::endl;
	std::cout << "##################" << std::endl;

}