#ifndef CameraSpring_H
#define CameraSpring_H
/// CameraSpring Class
/** This calculates the position of the camera. */

#include <Ogre.h>

class CameraSpring
{	
public:

	Ogre::Vector3 mCameraPos; ///<Cameras Position

	Ogre::Vector3 mDesiredPosition;///<Position we want to be at, idealy somewhere behind the player e.g.(0,50,-100);

	Ogre::Vector3 mVelocity;///<Cameras Velocity

	Ogre::Vector3 mAcceleration;///<Cameras Acceleration

	Ogre::Vector3 mDampenedVelocity;///<Cameras Velocity after dampening

	Ogre::Vector3 mStretch;///<Amount Camera Strecthed

	Ogre::Vector3 mForce;///<Force applied to the camera
	

	float mStiffness;///<Spring Stiffness

	float mDampening;///<Spring Dampening

	float mMass;///<Spring Mass



	CameraSpring();///<Default Constructor

	void initCameraSpring(Ogre::Vector3 camPos,Ogre::Vector3 offsetPos);///<Sets up a camera spring

	Ogre::Vector3 updateCameraSpring(Ogre::Vector3 camPos,Ogre::Vector3 offsetPos);///<Updates the camera position


	float getMass(){return mMass;}///<Inline get Mass function

	float getDampening(){return mDampening;}///<Inline get Dampening function

	float getStiffness(){return mStiffness;}///<Inline get Stiffness function

	void setMass(float mass){mMass = mass;}///<Inline set Mass function

	void setDampening(float dampening){mDampening = dampening;}///<Inline set Dampening function

	void setStiffness(float stiffness){mStiffness = stiffness;}///<Inline set Stiffness function

	

private:


};
#endif