#include "CameraSpring.h"

using namespace Ogre;

///CameraSpring()
/** Camera Spring Constructor.
*/
CameraSpring::CameraSpring(){

	mStiffness = 4;

	mDampening = 6;

	mMass = 50;

} // end Constructor

///initCameraSpring()
/** Sets up the Camera Spring.
*/
void CameraSpring::initCameraSpring(Vector3 camPos, Vector3 offsetPos)
{
	mCameraPos = camPos;

	mDesiredPosition = offsetPos;
}

///updateCameraSpring()
/** Updates the Camera Position.
*/
Vector3 CameraSpring::updateCameraSpring(Vector3 camPos, Vector3 offsetPos)
{
	//Set the desired position, e.g. somewhere behind and above the camera
	mDesiredPosition = offsetPos;

	//Set the cameras current position
	mCameraPos = camPos;
    
	//Get the stretch by subtracting desired position from current position and multiply by stiffness
    mStretch.x = (mCameraPos.x - mDesiredPosition.x) * -mStiffness;
    mStretch.y = (mCameraPos.y - mDesiredPosition.y) * -mStiffness;
    mStretch.z = (mCameraPos.z - mDesiredPosition.z) * -mStiffness;
    
	//Get the dampened velocity by multiplying velocity by dampening
	mDampenedVelocity.x = mVelocity.x * mDampening;
	mDampenedVelocity.y = mVelocity.y * mDampening;
	mDampenedVelocity.z = mVelocity.z * mDampening;

	//Force is the stretch minus the dampened velocity
	mForce = mStretch - mDampenedVelocity;

	//Get the acceleration based on F=MA(A = F/M)
	mAcceleration.x = mForce.x * (1 / mMass);
	mAcceleration.y = mForce.y * (1 / mMass);
	mAcceleration.z = mForce.z * (1 / mMass);

	//Add the acceleration to the velocity
	
	mVelocity +=mAcceleration;
	
	//Add velocity to old camera position
	mCameraPos = mCameraPos + mVelocity;

	//Return new camera position
	return mCameraPos;
}
