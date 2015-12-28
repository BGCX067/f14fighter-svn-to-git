#ifndef _HIGHSCORE_MANAGER_H_
#define _HIGHSCORE_MANAGER_H_

#include <sstream> 

#include "Ogre.h"

using namespace Ogre;

class HighscoreManager
{
public:
	HighscoreManager(void);
	HighscoreManager(std::string path);
	~HighscoreManager(void);
	void									loadFile(std::string path);

	float									getFloatEntry(unsigned int index); 
	std::string								getStringEntry(unsigned int index); 

	int										getNumberOfHighscoreEntries();
	void									writeHighscoreToConfigFile(std::string path);
	void									insertHighscore(std::string name, float value);

private:
	void									parseFloat(std::string key, std::string value); 

	void									writeErrorToConsole(std::string key);

	ConfigFile*								configFile;
	std::map<std::string, float>			nameMap;
	std::map<float, std::string>			floatMap;
};

#endif