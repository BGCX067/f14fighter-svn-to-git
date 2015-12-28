#include "CollisionHandler.h"

//*****************************************
//					3D
//*****************************************

bool CollisionHandler::checkBottomCollision(Ogre::AxisAlignedBox box1,  Ogre::AxisAlignedBox box2) 
{
	
	if(checkLower(box1, box2) && checkXAxis(box1, box2) && checkZAxis(box1, box2)) 
		return true;		
	else
		return false;
	
}

//*****************************************
//					2D
//*****************************************

bool CollisionHandler::checkXAxis(Ogre::AxisAlignedBox box1, Ogre::AxisAlignedBox box2) 
{
	if(checkRighter(box1, box2) && checkLefter(box1, box2))
		return true;
	else
		return false;
	
}

bool CollisionHandler::checkYAxis(Ogre::AxisAlignedBox box1, Ogre::AxisAlignedBox box2) 
{
	if(checkHigher(box1, box2) && checkLower(box1, box2)) 
		return true;
	else
		return false;
	
}

bool CollisionHandler::checkZAxis(Ogre::AxisAlignedBox box1, Ogre::AxisAlignedBox box2) 
{
	if(checkNearer(box1, box2) && checkFarer(box1, box2)) 
		return true;
	else 
		return false;
	
}

//*****************************************
//					1D
//*****************************************

bool CollisionHandler::checkRighter( Ogre::AxisAlignedBox box1,  Ogre::AxisAlignedBox box2) 
{
	if(box1.getCorner(Ogre::AxisAlignedBox::NEAR_RIGHT_BOTTOM).x > box2.getCorner(Ogre::AxisAlignedBox::NEAR_LEFT_BOTTOM).x) {
		return true;
	} else {
		return false;
	}
}

bool CollisionHandler::checkLefter( Ogre::AxisAlignedBox box1,  Ogre::AxisAlignedBox box2) 
{
	if(box1.getCorner(Ogre::AxisAlignedBox::NEAR_LEFT_BOTTOM).x < box2.getCorner(Ogre::AxisAlignedBox::NEAR_RIGHT_BOTTOM).x) {
		return true;
	} else {
		return false;
	}
}

bool CollisionHandler::checkHigher(Ogre::AxisAlignedBox box1, Ogre::AxisAlignedBox box2) 
{
	if(box1.getCorner(Ogre::AxisAlignedBox::NEAR_LEFT_TOP).y > box2.getCorner(Ogre::AxisAlignedBox::NEAR_LEFT_BOTTOM).y)
		return true;
	else
		return false;

}

bool CollisionHandler::checkLower(Ogre::AxisAlignedBox box1, Ogre::AxisAlignedBox box2) 
{
	if(box1.getCorner(Ogre::AxisAlignedBox::NEAR_LEFT_BOTTOM).y < box2.getCorner(Ogre::AxisAlignedBox::NEAR_LEFT_TOP).y) 
		return true;
	else 
		return false;
}

bool CollisionHandler::checkNearer( Ogre::AxisAlignedBox box1,  Ogre::AxisAlignedBox box2)
{
	if(box1.getCorner( Ogre::AxisAlignedBox::NEAR_LEFT_BOTTOM).z > box2.getCorner( Ogre::AxisAlignedBox::FAR_LEFT_BOTTOM).z) {
		return true;
	} else {
		return false;
	}
}

bool CollisionHandler::checkFarer( Ogre::AxisAlignedBox box1,  Ogre::AxisAlignedBox box2)
{
	if(box1.getCorner( Ogre::AxisAlignedBox::FAR_LEFT_BOTTOM).z < box2.getCorner( Ogre::AxisAlignedBox::NEAR_LEFT_BOTTOM).z)
		return true;
	else 
		return false;
}