#include "F14.h"
#include "../Manager/DataManager/DataManager.h"

int	F14::f14Number = 0;
//--------------------------------------------------------------
F14::F14(int xboxController, Vector3 startPosition, Camera* camera, std::string material,  Vector3 lookingDirection)
:	entity(0), sceneNode(0), cameraNode(0), sceneNodeAfterBurnerLeft(0), sceneNodeAfterBurnerRight(0), 
	particleSystemAfterBurnerLeft(0), particleSystemAfterBurnerRight(0), rotX(0), rotY(0), speed(0),
	alive(true), dieTime(0), sceneNodeExplotion(0), particleSystemExplotion(0),f14Destroyed(false), color(0), 
	activeEmitter(F14FIGHTER::TORUS::NOTHING), boostPower(0), boostActivated(false), maximumSpeedRaiseFactor(0), speedRaiseFactor(1), translateLeftRight(0),
	quat1(Quaternion()), quat2(Quaternion()), rotXOld(0), rotZOld(0), camera(0), isRollLocked(true), isPitchLocked(true),  currentPhase(F14FIGHTER::F14::START_PHASE),
	leftBoneWing(0),rightBoneWing(0), leftPitchElevator(0), rightPitchElevator(0)
{
	settingManager.loadFile("f14Settings.cfg");
	
	uniqueNumber = f14Number++;
	this->camera = camera;
	dataManager = DataManager::getDataManagerAsSingleton();
	createF14(startPosition, material, lookingDirection);
	boost = settingManager.getFloat("f14BoostStartValue");
	color = settingManager.getFloat("f14ColorStartValue");

	maximumSpeedRaiseFactor = settingManager.getFloat("f14MaximumSpeedRaiseFactor");
	maximumSpeed = settingManager.getFloat("f14MaximumSpeedForward");
	maximumBoost = settingManager.getFloat("f14MaximumBoostForward");
	maximumColor = settingManager.getFloat("f14MaximumColorForward");

	impuls = settingManager.getVector3("startImpuls");
	mass = settingManager.getFloat("mass");
	airResistance = settingManager.getVector3("airResistance");
	gravitation = settingManager.getVector3("gravitation");
	attitude = Vector3(0,0,0);
	f14Controlls = new F14Controlls(xboxController,this);
}

//--------------------------------------------------------------
F14::~F14()
{
	std::vector<Rocket*>::iterator rocketIterator= rockets.begin();
	
    while(rocketIterator!= rockets.end())
	{
        delete *rocketIterator;
        rocketIterator = rockets.erase(rocketIterator);
        continue;
        ++rocketIterator;
    } 
}

//--------------------------------------------------------------
void F14::moveF14(float dt)
{
	if(sceneNode)
	{
		updateRockets(dt);
		handleBoost(dt);
		handlePhysics(dt);
		handleMovement(dt);
		handleCamera(dt);
		handleAfterBurner(dt);		
		handleCondensTrail(dt);
		handleColor(dt);
		handleWingControll(dt);
		autoCoordination(dt);
		
		if(!alive && !f14Destroyed)
		{
			die();
			gravitation = Vector3(0,0,0);
		}
		else
		{
			gravitation = settingManager.getVector3("gravitation");
		}
	}
}
//--------------------------------------------------------------
void F14::handleWingControll(float dt)
{
	if(getSpeedProgress() > settingManager.getFloat("wingControllStart"))
	{
		if(leftBoneWing->getOrientation().getYaw().valueDegrees() < settingManager.getFloat("maxWingValue"))
			leftBoneWing->yaw(Degree(settingManager.getFloat("wingAcceleration")));

		if(rightBoneWing->getOrientation().getYaw().valueDegrees() > -settingManager.getFloat("maxWingValue"))
			rightBoneWing->yaw(Degree(settingManager.getFloat("wingAcceleration")));
	}
	else
	{
		if(leftBoneWing->getOrientation().getYaw().valueDegrees() > settingManager.getFloat("minWingValue"))
			leftBoneWing->yaw(Degree(-settingManager.getFloat("wingAcceleration")));
		
		if(rightBoneWing->getOrientation().getYaw().valueDegrees() < -settingManager.getFloat("minWingValue"))
			rightBoneWing->yaw(Degree(-settingManager.getFloat("wingAcceleration")));
	}
	
}
//--------------------------------------------------------------
void F14::activateBoost(bool value)
{
	boostActivated = value;
}
//--------------------------------------------------------------
void F14::handleBoost(float  dt)
{
	//change boostPower
	if(boost < 0)
		boostActivated = false;

	if(boostActivated && boostPower < maximumBoost)
		boostPower += 3;
	
	if(boostActivated)
	{
		boost -= settingManager.getFloat("decreaseValueOfBoost")*dt;
	}
	if (boostActivated == false && boostPower > 0)
		boostPower -= 1;
	
}
//--------------------------------------------------------------
void F14::handlePhysics(float dt)
{
	//calculate velocityOfApproach relative to object
	//(w)world = -v = -(p/m)
	Vector3 velocityOfApproachWorld = -(impuls/mass);			
	
	//calculate (w)f14 - velocityofapproach in f14 coordinates
	Matrix3 rotationMatrix;
	sceneNode->getOrientation().ToRotationMatrix(rotationMatrix);
	
	//RT = R^-1					--> inverted rotationMatrix		
	Matrix3 inverseRotationMatrix = rotationMatrix.Transpose();
	
	//(w)14 = (w)world * RT
	Vector3 velocityOfApproachF14 = inverseRotationMatrix * velocityOfApproachWorld;			

	//(Fd)f14
	Vector3 fd = (velocityOfApproachF14 * airResistance) * velocityOfApproachF14.length();
	
	float fpFaktor;
	if(boostActivated)
		fpFaktor = settingManager.getFloat("boost") * speedRaiseFactor;
	else
		fpFaktor = settingManager.getFloat("thrust")* speedRaiseFactor;
	
	Vector3 fp = Vector3(0,0,fpFaktor*speed);
		
	Vector3 fWorld = rotationMatrix * (fd+fp);
	
	Vector3 fTotal = (mass*gravitation) + fWorld;
	impuls += fTotal*dt;
		
	translationVector = Vector3(impuls/mass*dt*0.5);

	//just translate scene if f14 is alive
	if(alive)
		sceneNode->translate(translationVector);
	
}
//--------------------------------------------------------------
void F14::autoCoordination(float dt)
{
	Vector3 velocity = impuls/mass;
	if(velocity.length() > 0.001)
	{
		Vector3 xn = Vector3::UNIT_Y.crossProduct(getDirection());
		Vector3 yn = getDirection().crossProduct(xn);

		float phi = getLeftVector().dotProduct(yn) * settingManager.getFloat("autoCoordinateFaktor") * Ogre::Math::PI/2;
		
		float v = velocity.length();
		float omega = gravitation.y * phi / v;
		sceneNode->yaw(Radian(omega*dt),Ogre::Node::TS_WORLD);
	}
}
//--------------------------------------------------------------
void F14::handleMovement(float dt)
{
	if(currentPhase == F14FIGHTER::F14::START_PHASE)
	{
		lockPitch(true);
		lockRoll(true);
	}
	else
	{
		lockPitch(false);
		lockRoll(false);
	}
	//MOVE SCENE NODE
	Quaternion quatOrientation = sceneNode->getOrientation();
	sceneNode->setOrientation(quatOrientation * quat1 * quat2);

	//roll and translate right
	//YAW
	if(currentPhase != F14FIGHTER::F14::START_PHASE)
	{
		sceneNode->yaw(rotY * 1.0 * dt);
		//LEFT YAW
		if(rotY > Radian(0))
			sceneNode->roll(-rotY*1.5*dt);
		
		//RIGHT YAW
		if(rotY < Radian(0))
			sceneNode->roll(-rotY*1.5*dt);
		
		//PITCH
		Radian smoothValueX = (rotX * settingManager.getFloat("pitchAverageNew")) + (rotXOld * settingManager.getFloat("pitchAverageOld"));
		sceneNode->pitch(smoothValueX*dt);
		rotXOld = smoothValueX;

		//ROLL
		Radian smoothValueZ = (rotZ *settingManager.getFloat("rollAverageNew")) + (rotZOld * settingManager.getFloat("rollAverageOld"));
		sceneNode->roll(smoothValueZ * dt);
		rotZOld = smoothValueZ;
	}
	
}
void F14::handleCamera(float dt)
{
	if(alive)
	{
		float alpha = exp(-settingManager.getFloat("cameraLambda")*dt);
		Vector3 targetPosition = -getDirection()*settingManager.getFloat("cameraOffset") +sceneNode->getPosition();
		camera->setPosition(camera->getPosition()*alpha + targetPosition*(1-alpha)) ;
		camera->lookAt(sceneNode->getPosition());
	}
}
void F14::handleAfterBurner(float dt)
{
	
	//Change Speed of Particle Systems
	float particleSpeed = speed / (maximumSpeed * speedRaiseFactor )+ 0.3;
	particleSystemAfterBurnerLeft->getEmitter(0)->setEnabled(true);
	particleSystemAfterBurnerLeft->setSpeedFactor(particleSpeed);
	particleSystemAfterBurnerRight->getEmitter(0)->setEnabled(true);
	particleSystemAfterBurnerRight->setSpeedFactor(particleSpeed);
	
	//Change Z Position of Particle System
	float particleZPosition = -2 -  2* (speed / (maximumSpeed* speedRaiseFactor)); //Values from -3 .... -6
	Vector3 afterBurnerLeftPosition = sceneNodeAfterBurnerLeft->getPosition();
	Vector3 afterBurnerRightPosition = sceneNodeAfterBurnerRight->getPosition();
	afterBurnerLeftPosition.z = afterBurnerRightPosition.z = particleZPosition;
	sceneNodeAfterBurnerLeft->setPosition(afterBurnerLeftPosition);
	sceneNodeAfterBurnerRight->setPosition(afterBurnerRightPosition);
}
void F14::handleCondensTrail(float dt)
{
	//Activate or Deactivate Condensation Trails
	float speedPercentage = speed / (maximumSpeed * speedRaiseFactor);

	//inner Particles
	if(speedPercentage > 0.5)
	{
		particleSystemCondensationTrailLeft->getEmitter(0)->setEnabled(true);
		particleSystemCondensationTrailRight->getEmitter(0)->setEnabled(true);
	}
	else
	{
		particleSystemCondensationTrailLeft->getEmitter(0)->setEnabled(false);
		particleSystemCondensationTrailRight->getEmitter(0)->setEnabled(false);
	}
}
void F14::handleColor(float dt)
{

	switch(activeEmitter)
	{
		case F14FIGHTER::TORUS::NOTHING:
			activateEmitter(false);
			break;

		case F14FIGHTER::TORUS::BLUE:
			particleSystemBlueLeft->getEmitter(0)->setEnabled(true);
			particleSystemBlueRight->getEmitter(0)->setEnabled(true);
			break;
		case F14FIGHTER::TORUS::GREEN:
			particleSystemGreenLeft->getEmitter(0)->setEnabled(true);
			particleSystemGreenRight->getEmitter(0)->setEnabled(true);
			break;
		case F14FIGHTER::TORUS::RED:
			particleSystemRedLeft->getEmitter(0)->setEnabled(true);
			particleSystemRedRight->getEmitter(0)->setEnabled(true);
			break;
		case F14FIGHTER::TORUS::YELLOW:
			particleSystemYellowLeft->getEmitter(0)->setEnabled(true);
			particleSystemYellowRight->getEmitter(0)->setEnabled(true);
			break;
	}
	if(color <= 0)
		activeEmitter = F14FIGHTER::TORUS::NOTHING;

	if(activeEmitter != F14FIGHTER::TORUS::NOTHING)
		color -= 5*dt;
	
}
void F14::lockPitch(bool lock)
{
	isPitchLocked = lock;
}
void F14::lockGravity(bool lock)
{
	if(lock)
		gravitation = Vector3(0,0,0);
	else
		gravitation = settingManager.getVector3("gravitation");
}
void F14::lockRoll(bool lock)
{
	isRollLocked = lock;
}

//--------------------------------------------------------------
void F14::addSpeed(float addValue)
{
	speed = maximumSpeed * speedRaiseFactor * addValue;
}

//--------------------------------------------------------------
void F14::removeSpeed(float removeValue)
{
	speed = maximumSpeed * speedRaiseFactor * removeValue;
}

//--------------------------------------------------------------
void F14::addBoost(float addValue)
{
	
	if(boost < maximumBoost)
		boost += addValue;
	else
		boost = maximumBoost;
}

//--------------------------------------------------------------
void F14::removeBoost(float removeValue)
{
	if(boost > 0)
		boost -= removeValue;
	else
		boost = 0;
}

//--------------------------------------------------------------
void F14::addColor(float addValue)
{
	if(color < maximumColor)
		color += addValue;
	else
		color = maximumColor;
}
//--------------------------------------------------------------
void F14::removeColor(float removeValue)
{
	if(color > 0)
		color -= removeValue;
	else
		color = 0;
}

//--------------------------------------------------------------
void F14::rollLeft(Radian value, bool rollFast)
{
	if(isRollLocked)
		return;

	if(rollFast)
	{
		if( rotZ > -Radian(3*settingManager.getFloat("f14MaximumRollValue")))
			rotZ += value;
	}
	else
	{
		if( rotZ > -Radian(settingManager.getFloat("f14MaximumRollValue")))
			rotZ += value;
	}
}
//--------------------------------------------------------------
void F14::rollRight(Radian value, bool rollFast)
{
	if(isRollLocked)
		return;

	if(rollFast)
	{
		if( rotZ < Radian(3*settingManager.getFloat("f14MaximumRollValue")))
			rotZ += value;
	}
	else
	{
		if( rotZ < Radian(settingManager.getFloat("f14MaximumRollValue")))
			rotZ += value;
	}

}
//--------------------------------------------------------------
void F14::rollToCenter(Radian value)
{
	if(sceneNode)
	{
		Radian roll = sceneNode->getOrientation().getRoll();

		//stop at PI Radians
		if((roll == Radian(Ogre::Math::PI)) || (roll < Radian(-Ogre::Math::PI)+Radian(0.005)) || (roll > Radian(Ogre::Math::PI)-Radian(0.005)))
		{
			rotZ = 0;
			Radian rollTo =Radian(Ogre::Math::PI) - roll;
			sceneNode->roll(-rollTo);
		}
		else if(roll < Radian(0))
			rollRight( value, true);
		else if(roll > Radian(0))
			rollLeft ( value, true);
	}
}
//--------------------------------------------------------------
void F14::pitchUp(Radian value)
{
	/*if(rightPitchElevator->getOrientation().getRoll().valueDegrees() > settingManager.getFloat("minPitchElevator"))
		rightPitchElevator->roll(Degree(-1));
	if(leftPitchElevator->getOrientation().getRoll().valueDegrees() > settingManager.getFloat("minPitchElevator"))
		leftPitchElevator->roll(Degree(-1));*/

	if(isRollLocked)
		return;
	
	rotX = value * 10;
}
//--------------------------------------------------------------
void F14::pitchDown(Radian value)
{

	//if(rightPitchElevator->getOrientation().getRoll().valueDegrees() < settingManager.getFloat("maxPitchElevator"))
	//	rightPitchElevator->roll(Degree(1));		
	//if(leftPitchElevator->getOrientation().getRoll().valueDegrees() < settingManager.getFloat("maxPitchElevator"))
	//	leftPitchElevator->roll(Degree(1));		
	//	

	if(isRollLocked)
		return;
	rotX = value *10;
}
//--------------------------------------------------------------
void F14::pitchToCenter(Radian value)
{
	rotX = value;
}
//--------------------------------------------------------------
void F14::yawLeft(Radian value)
{
	rotY = value;
}
//--------------------------------------------------------------
void F14::yawRight(Radian value)
{
	rotY = value;
}
//--------------------------------------------------------------
void F14::yawToCenter(Radian value)
{
	rotY = value;	
}
//--------------------------------------------------------------
void F14::createF14(Vector3 startPosition, std::string material, Vector3 lookingDirection)
{
	//##############//
	//# SCENE NODE #//
	//##############//
	std::string entityName = "f14" + StringConverter::toString(uniqueNumber);
	entity = dataManager->sceneManager->createEntity(entityName, "f14Fighter.mesh");
	entity->setMaterialName(material);
	sceneNode = dataManager->sceneManager->getRootSceneNode()->createChildSceneNode();
	sceneNode->attachObject(entity);
	sceneNode->setPosition(startPosition);
	sceneNode->setDirection(-lookingDirection.x,0,-lookingDirection.z);
	sceneNode->setScale(10,10,10);
	

	//###################//
	//# F14 AFTERBURNER #//
	//###################//
	///////////////////////////////////////
	//LEFT
	particleSystemAfterBurnerLeft = dataManager->sceneManager->createParticleSystem("afterBurnerLeft" + StringConverter::toString(uniqueNumber), "F14/Afterburner");
	particleSystemAfterBurnerLeft->setKeepParticlesInLocalSpace(true);
	particleSystemAfterBurnerLeft->getEmitter(0)->setEnabled(false);
	particleSystemAfterBurnerLeft->setSpeedFactor(0.1);

	// Create shared node for 2 fountains
	sceneNodeAfterBurnerLeft =  sceneNode->createChildSceneNode();
	sceneNodeAfterBurnerLeft->translate(0.75,-0.1,-7);//(0.8,1.6,-6);
	
	sceneNodeAfterBurnerLeft->attachObject(particleSystemAfterBurnerLeft);

	///////////////////////////////////////
	//RIGHT
	particleSystemAfterBurnerRight= dataManager->sceneManager->createParticleSystem("afterBurnerRight"  + StringConverter::toString(uniqueNumber) , "F14/Afterburner");
	particleSystemAfterBurnerRight->setKeepParticlesInLocalSpace(true);
	particleSystemAfterBurnerRight->getEmitter(0)->setEnabled(false);
	particleSystemAfterBurnerRight->setSpeedFactor(0.1);
	
	
	// Create shared node for 2 fountains
	sceneNodeAfterBurnerRight =  sceneNode->createChildSceneNode();
	sceneNodeAfterBurnerRight->translate(-0.75,-0.1,-7);
	sceneNodeAfterBurnerRight->attachObject(particleSystemAfterBurnerRight);
	
	//#####################//
	//# CONDESATION TRAIL #//
	//###############ä#####//
	//////////////////////////////////////
	//LEFT 1
	particleSystemCondensationTrailLeft = dataManager->sceneManager->createParticleSystem("condensationTrailLeft1" + StringConverter::toString(uniqueNumber), "F14/CondensationTrail");
	particleSystemCondensationTrailLeft->setSpeedFactor(4); 
	particleSystemCondensationTrailLeft->getEmitter(0)->setEnabled(false);
	// Create shared node for 2 fountains
	sceneNodeCondensationTrailLeft =  sceneNode->createChildSceneNode();
	sceneNodeCondensationTrailLeft->translate(0.8, -0.5,-6);
	sceneNodeCondensationTrailLeft->yaw(Radian(-0.1));
	sceneNodeCondensationTrailLeft->attachObject(particleSystemCondensationTrailLeft);

	///////////////////////////////////////
	//RIGHT 1
	particleSystemCondensationTrailRight = dataManager->sceneManager->createParticleSystem("condensationTrailRight1" + StringConverter::toString(uniqueNumber), "F14/CondensationTrail");
	particleSystemCondensationTrailRight->setSpeedFactor(4); 
	particleSystemCondensationTrailRight->getEmitter(0)->setEnabled(false);

	// Create shared node for 2 fountains
	sceneNodeCondensationTrailRight =  sceneNode->createChildSceneNode();
	sceneNodeCondensationTrailRight->translate(-0.8, -0.5,-6);
	sceneNodeCondensationTrailRight->yaw(Radian(0.1));
	sceneNodeCondensationTrailRight->attachObject(particleSystemCondensationTrailRight);

	//###############//
	//# COLOR TRAIL #//
	//###############// 
	particleSystemYellowLeft = dataManager->sceneManager->createParticleSystem("yellowSmokeLeft" + StringConverter::toString(uniqueNumber), "F14/yellowSmoke");
	particleSystemYellowLeft->setSpeedFactor(4); 
	particleSystemYellowLeft->setKeepParticlesInLocalSpace(false);
	particleSystemYellowLeft->getEmitter(0)->setEnabled(false);

	particleSystemYellowRight = dataManager->sceneManager->createParticleSystem("yellowSmokeRight" + StringConverter::toString(uniqueNumber), "F14/yellowSmoke");
	particleSystemYellowRight->setSpeedFactor(4); 
	particleSystemYellowRight->setKeepParticlesInLocalSpace(false);
	particleSystemYellowRight->getEmitter(0)->setEnabled(false);

	particleSystemRedLeft = dataManager->sceneManager->createParticleSystem("redSmokeLeft" + StringConverter::toString(uniqueNumber), "F14/redSmoke");
	particleSystemRedLeft->setSpeedFactor(4); 
	particleSystemRedLeft->setKeepParticlesInLocalSpace(false);
	particleSystemRedLeft->getEmitter(0)->setEnabled(false);

	particleSystemRedRight = dataManager->sceneManager->createParticleSystem("redSmokeRight" + StringConverter::toString(uniqueNumber), "F14/redSmoke");
	particleSystemRedRight->setSpeedFactor(4); 
	particleSystemRedRight->setKeepParticlesInLocalSpace(false);
	particleSystemRedRight->getEmitter(0)->setEnabled(false);

	particleSystemBlueLeft = dataManager->sceneManager->createParticleSystem("blueSmokeLeft" + StringConverter::toString(uniqueNumber), "F14/blueSmoke");
	particleSystemBlueLeft->setSpeedFactor(4); 
	particleSystemBlueLeft->setKeepParticlesInLocalSpace(false);
	particleSystemBlueLeft->getEmitter(0)->setEnabled(false);

	particleSystemBlueRight = dataManager->sceneManager->createParticleSystem("blueSmokeRight" + StringConverter::toString(uniqueNumber), "F14/blueSmoke");
	particleSystemBlueRight->setSpeedFactor(4); 
	particleSystemBlueRight->setKeepParticlesInLocalSpace(false);
	particleSystemBlueRight->getEmitter(0)->setEnabled(false);

	particleSystemGreenLeft = dataManager->sceneManager->createParticleSystem("greenSmokeLeft" + StringConverter::toString(uniqueNumber), "F14/greenSmoke");
	particleSystemGreenLeft->setSpeedFactor(4); 
	particleSystemGreenLeft->setKeepParticlesInLocalSpace(false);
	particleSystemGreenLeft->getEmitter(0)->setEnabled(false);

	particleSystemGreenRight = dataManager->sceneManager->createParticleSystem("greenSmokeRight" + StringConverter::toString(uniqueNumber), "F14/greenSmoke");
	particleSystemGreenRight->setSpeedFactor(4);
	particleSystemGreenRight->setKeepParticlesInLocalSpace(false);
	particleSystemGreenRight->getEmitter(0)->setEnabled(false);

	// Create shared node for 2 fountains
	sceneNodeColorLeft =  sceneNode->createChildSceneNode();
	sceneNodeColorLeft->translate(5, 0.1,-2.2);
	sceneNodeColorLeft->yaw(Radian(-0.2));
	sceneNodeColorLeft->attachObject(particleSystemYellowLeft);
	sceneNodeColorLeft->attachObject(particleSystemRedLeft);
	sceneNodeColorLeft->attachObject(particleSystemBlueLeft);
	sceneNodeColorLeft->attachObject(particleSystemGreenLeft);

	// Create shared node for 2 fountains
	sceneNodeColorRight =  sceneNode->createChildSceneNode();
	sceneNodeColorRight->translate(-5, 0.1,-2.2);
	sceneNodeColorRight->yaw(Radian(0.2));
	sceneNodeColorRight->attachObject(particleSystemYellowRight);
	sceneNodeColorRight->attachObject(particleSystemRedRight);
	sceneNodeColorRight->attachObject(particleSystemBlueRight);
	sceneNodeColorRight->attachObject(particleSystemGreenRight);

	//#############//
	//# EXPLOTION #//
	//#############//
	particleSystemExplotion = dataManager->sceneManager->createParticleSystem("F14Explotion" + StringConverter::toString(uniqueNumber), "F14/Explosion");
	particleSystemExplotion->getEmitter(0)->setEnabled(false);

	// Create shared node for 2 fountains
	sceneNodeExplotion =  sceneNode->createChildSceneNode();
	sceneNodeExplotion->attachObject(particleSystemExplotion);

	//camera Direction
	camera->setPosition(sceneNode->getPosition() + Vector3(0,200,600) );
	camera->lookAt(sceneNode->getPosition());
	
	//#########//
	//# BONES #//
	//#########//
	leftBoneWing = entity->getSkeleton()->getBone("left");
	leftBoneWing->setManuallyControlled(true);
	//leftBoneWing->yaw(Degree(35));

	rightBoneWing = entity->getSkeleton()->getBone("right");
	rightBoneWing ->setManuallyControlled(true);
	//rightBoneWing->yaw(Degree(35));	
	leftPitchElevator = entity->getSkeleton()->getBone("l_ruder");
	leftPitchElevator->setManuallyControlled(true);

	rightPitchElevator = entity->getSkeleton()->getBone("r_ruder");
	rightPitchElevator->setManuallyControlled(true);
	
}

//--------------------------------------------------------------
void F14::activateEmitter(bool value)
{
	particleSystemYellowLeft->getEmitter(0)->setEnabled(value);
	particleSystemYellowRight->getEmitter(0)->setEnabled(value);
	
	particleSystemRedLeft->getEmitter(0)->setEnabled(value);
	particleSystemRedRight->getEmitter(0)->setEnabled(value);

	particleSystemBlueLeft->getEmitter(0)->setEnabled(value);
	particleSystemBlueRight->getEmitter(0)->setEnabled(value);
	
	particleSystemGreenLeft->getEmitter(0)->setEnabled(value);
	particleSystemGreenRight->getEmitter(0)->setEnabled(value);
}

//--------------------------------------------------------------
bool F14::isYellowEmitterEnabled()
{
	if(activeEmitter == F14FIGHTER::TORUS::YELLOW)
		return true;
	else
		return false;
}

//--------------------------------------------------------------
bool F14::isRedEmitterEnabled()
{
	if(activeEmitter == F14FIGHTER::TORUS::RED)
		return true;
	else
		return false;
}

//--------------------------------------------------------------
bool F14::isBlueEmitterEnabled()
{
	if(activeEmitter == F14FIGHTER::TORUS::BLUE)
		return true;
	else
		return false;
}

//--------------------------------------------------------------
bool F14::isGreenEmitterEnabled()
{
	if(activeEmitter == F14FIGHTER::TORUS::GREEN)
		return true;
	else
		return false;
}

//--------------------------------------------------------------
void F14::setYellowEmitterEnable(bool value)
{
	bool statusYellow = isYellowEmitterEnabled();
	activateEmitter(false);
	
	if(statusYellow)
		activeEmitter = F14FIGHTER::TORUS::NOTHING;
	else
		activeEmitter = F14FIGHTER::TORUS::YELLOW;
}

//--------------------------------------------------------------
void F14::setRedEmitterEnable(bool value)
{
	bool statusRed = isRedEmitterEnabled();
	activateEmitter(false);
	
	if(statusRed)
		activeEmitter = F14FIGHTER::TORUS::NOTHING;
	else
		activeEmitter = F14FIGHTER::TORUS::RED;
}

//--------------------------------------------------------------
void F14::setBlueEmitterEnable(bool value)
{
	bool statusBlue = isBlueEmitterEnabled();
	activateEmitter(false);
	
	if(statusBlue)
		activeEmitter = F14FIGHTER::TORUS::NOTHING;
	else
		activeEmitter = F14FIGHTER::TORUS::BLUE;
}

//--------------------------------------------------------------
void F14::setGreenEmitterEnable(bool value)
{
	bool statusGreen = isGreenEmitterEnabled();
	activateEmitter(false);
	
	if(statusGreen)
		activeEmitter = F14FIGHTER::TORUS::NOTHING;
	else
		activeEmitter = F14FIGHTER::TORUS::GREEN;
}

//--------------------------------------------------------------
void F14::letF14Die()
{
	if(alive)
	{
		alive = false;
		dataManager->system->playSound(FMOD_CHANNEL_FREE, dataManager->explotion, false, &dataManager->channelExplotion);	
		//set new Camera Position
		Vector3 cameraPos = camera->getPosition();
		cameraPos.y = 300;
		camera->setPosition(cameraPos);
		dieTime = dataManager->myTimer.getElapsedTime();
	}
}

//--------------------------------------------------------------
void F14::die()
{
	particleSystemExplotion->getEmitter(0)->setEnabled(true);
	sceneNode->setVisible(false);
	sceneNodeExplotion->setVisible(true);
	
	speed = 0;
	boostPower = 0;
	
	Vector3 translateVector = camera->getPosition() + Vector3(-1,0,-1);
	camera->setPosition(translateVector);
	camera->lookAt(sceneNode->getPosition());
	
	if(dataManager->myTimer.getElapsedTime()- dieTime > 3)
	{
		particleSystemExplotion->getEmitter(0)->setEnabled(false);
		f14Destroyed = true;
		dieTime = 0;
	}
}

//--------------------------------------------------------------
float F14::getSpeedProgress()
{
	return std::min((float)impuls.length()/(settingManager.getFloat("maxImpulsNormal")*speedRaiseFactor), 1.0f);
}

//--------------------------------------------------------------
float F14::getBoostProgress()
{
	return std::min((float)boost/maximumBoost, 1.0f);
}

//--------------------------------------------------------------
float F14::getColorProgress()
{
	return std::min((float)color/maximumColor, 1.0f);
}
void F14::raiseMaxSpeed(float percentage)
{
	if(speedRaiseFactor < maximumSpeedRaiseFactor)
		speedRaiseFactor += percentage;	
}
Vector3 F14::getDirection()
{
	Matrix3 matrix;
	sceneNode->getOrientation().ToRotationMatrix(matrix);

	return matrix.GetColumn(2);
}
Vector3 F14::getLeftVector()
{
	Matrix3 matrix;
	sceneNode->getOrientation().ToRotationMatrix(matrix);

	return matrix.GetColumn(0);
}
void F14::shootRocket()
{
	//Rocket* newRocket = new Rocket(sceneNode->getPosition(),getDirection());
	//rockets.push_back(newRocket);
}
void F14::updateRockets(float dt)
{
	for(unsigned int i = 0; i < rockets.size(); i++)
	{
		rockets[i]->updateRocket(dt);
	}
}