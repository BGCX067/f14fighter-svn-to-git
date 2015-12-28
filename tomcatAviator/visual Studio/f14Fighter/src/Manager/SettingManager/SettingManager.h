#ifndef _SETTING_MANAGER_H_
#define _SETTING_MANAGER_H_

#include <sstream> 

#include "Ogre.h"

using namespace Ogre;

class SettingManager
{
public:
	SettingManager(void);
	SettingManager(std::string path);
	~SettingManager(void);
	void									loadFile(std::string path);

	float									getFloat(std::string key); 
	int										getInt(std::string key);
	std::string								getString(std::string key); 
	Vector3									getVector3(std::string key); 
	
private:
	void									parseFloat(std::string key, std::string value); 
	void									parseInt(std::string key, std::string value); 
	void									parseString(std::string key, std::string value); 
	void									parseVector3(std::string key, std::string value); 

	void									writeErrorToConsole(std::string key);
	ConfigFile*								configFile;
	std::map<std::string, float>			floatMap;
	std::map<std::string, int>				intMap;
	std::map<std::string, std::string>		stringMap;
	std::map<std::string, Vector3>			vector3Map;
	
	Vector3									tempVector;

};

#endif