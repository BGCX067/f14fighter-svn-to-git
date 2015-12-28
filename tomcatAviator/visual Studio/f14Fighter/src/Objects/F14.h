 #ifndef _F14_H_
#define _F14_H_

#include "Ogre.h"
#include "../Defines.h"
#include "../Manager/SettingManager/SettingManager.h"
#include "F14Controlls.h"
#include "Rocket.h"
using namespace Ogre;

class DataManager;
class F14
{
	public:
		F14(int xboxController, Vector3 startPosition, Camera* camera, std::string material, Vector3 lookingDirection);//lookingDirection ignores y koordinate cause of pitching and rolling the scenenode
		~F14();
		static int			f14Number;
		int					uniqueNumber;
		void				moveF14(float dt);
		
		float				getSpeedProgress();
		float				getBoostProgress();
		float				getColorProgress();
		
		void				lockPitch(bool lock);
		void				lockGravity(bool lock);
		void				lockRoll(bool lock);
		
		bool				isRollLocked;
		bool				isPitchLocked;
		//Forward Backward
		void				raiseMaxSpeed(float percentage);		//Forward
		void				addSpeed(float addValue);		//Forward
		void				removeSpeed(float removeValue); //Backward
	
		void				addBoost(float addValue);		
		void				removeBoost(float removeValue); 

		void				addColor(float addValue);		
		void				removeColor(float removeValue); 

		void				shootRocket();
		void				rollLeft(Radian value, bool rollFast = false);
		void				rollRight(Radian value, bool rollFast = false);
		void				rollToCenter(Radian value);

		void				pitchUp(Radian value);
		void				pitchDown(Radian value);
		void				pitchToCenter(Radian value);
		
		void				yawLeft(Radian value);
		void				yawRight(Radian value);
		void				yawToCenter(Radian value);
		void				letF14Die();

		bool				isYellowEmitterEnabled();
		bool				isRedEmitterEnabled();
		bool				isBlueEmitterEnabled();
		bool				isGreenEmitterEnabled();

		void				setYellowEmitterEnable(bool value);
		void				setRedEmitterEnable(bool value);
		void				setBlueEmitterEnable(bool value);
		void				setGreenEmitterEnable(bool value);
		void				activateEmitter(bool value);
		
		void				activateBoost(bool value);

		void				handleBoost(float  dt);
		void				handlePhysics(float dt);
		void				handleWingControll(float dt);
		void				handleMovement(float dt);			//pitch, yaw, roll, translate of scenenode
		void				handleColor(float dt);				//enable emitter of activated color and check if there is color available
		void				handleCondensTrail(float dt);		//calculate if condenstrail is shown, and set emitter true or false
		void				handleAfterBurner(float dt);		//translate the afterburner in Z Axis acording to the speed of f14
		void				handleCamera(float dt);
		void				autoCoordination(float dt);
		float				dieTime;
		bool				alive;
		bool				f14Destroyed;

		//Vector3			direction;
		float				speed;
		float				boostPower;
		bool				boostActivated;
		Radian				rotX, rotXOld, rotY, rotZ, rotZOld;
		Radian				translateLeftRight;
		Vector3				getDirection();
		Vector3				getLeftVector();
		Quaternion			quat1;
		Quaternion			quat2; 
		
		int					activeEmitter;

		Entity*				entity;
		SceneNode*			sceneNode;
		Vector3				translationVector;
		//Physic
		Vector3				impuls;
		float				mass;
		Vector3				airResistance;
		Vector3				gravitation;
		Vector3				attitude;

		Bone*				leftBoneWing;
		Bone*				rightBoneWing;
		Bone*				leftPitchElevator;
		Bone*				rightPitchElevator;

private:
		void				createF14(Vector3 startPosition, std::string material, Vector3 lookingDirection);//lookingDirection ignores y koordinate cause of pitching and rolling the scenenode
		void				die();
	
		DataManager*		dataManager;

		SceneNode*			cameraNode;
		SceneNode*			sceneNodeAfterBurnerLeft;
		SceneNode*			sceneNodeAfterBurnerRight;
		SceneNode*			sceneNodeCondensationTrailLeft;
		SceneNode*			sceneNodeCondensationTrailRight;
		SceneNode*			sceneNodeColorLeft;
		SceneNode*			sceneNodeColorRight;
		SceneNode*			sceneNodeExplotion;

		ParticleSystem*		particleSystemAfterBurnerLeft;
		ParticleSystem*		particleSystemAfterBurnerRight;
		ParticleSystem*		particleSystemCondensationTrailLeft;
		ParticleSystem*		particleSystemCondensationTrailRight;

		ParticleSystem*		particleSystemYellowLeft;
		ParticleSystem*		particleSystemYellowRight;

		ParticleSystem*		particleSystemRedLeft;
		ParticleSystem*		particleSystemRedRight;

		ParticleSystem*		particleSystemBlueLeft;
		ParticleSystem*		particleSystemBlueRight;

		ParticleSystem*		particleSystemGreenLeft;
		ParticleSystem*		particleSystemGreenRight;
		ParticleSystem*		particleSystemExplotion;
		SettingManager		settingManager;
public:			
		Camera*				camera;

		float				boost;
		float				color;
		
		float				speedRaiseFactor;
		float				maximumSpeedRaiseFactor;
		float				maximumSpeed;
		float				maximumBoost;
		float				maximumColor;
		int					currentPhase;

		F14Controlls*		f14Controlls;
		std::vector<Rocket*> rockets;	
		void				updateRockets(float dt);
};

#endif 