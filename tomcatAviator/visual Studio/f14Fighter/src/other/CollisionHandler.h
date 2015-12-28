#ifndef COLLISIONHANDLER_H_
#define COLLISIONHANDLER_H_

#include "Ogre.h"

class CollisionHandler {
public:
	// 3d
	static bool checkBottomCollision(Ogre::AxisAlignedBox box1, Ogre::AxisAlignedBox box2);
	
	// 2d
	static bool checkXAxis(Ogre::AxisAlignedBox box1, Ogre::AxisAlignedBox box2);
	static bool checkYAxis(Ogre::AxisAlignedBox box1, Ogre::AxisAlignedBox box2);
	static bool checkZAxis(Ogre::AxisAlignedBox box1, Ogre::AxisAlignedBox box2);
	
	// 1d
	static bool checkRighter(Ogre::AxisAlignedBox box1, Ogre::AxisAlignedBox box2);
	static bool checkLefter(Ogre::AxisAlignedBox box1, Ogre::AxisAlignedBox box2);
	static bool checkHigher(Ogre::AxisAlignedBox box1, Ogre::AxisAlignedBox box2);
	static bool checkLower(Ogre::AxisAlignedBox box1, Ogre::AxisAlignedBox box2);
	static bool checkNearer(Ogre::AxisAlignedBox box1, Ogre::AxisAlignedBox box2);
	static bool checkFarer(Ogre::AxisAlignedBox box1, Ogre::AxisAlignedBox box2);
	
private:
	
}; 

#endif /*COLLISIONHANDLER_H_*/