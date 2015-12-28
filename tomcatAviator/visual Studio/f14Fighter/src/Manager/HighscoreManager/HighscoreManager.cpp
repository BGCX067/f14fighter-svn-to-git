#include "HighscoreManager.h"

//---------------------------------------------------------------------------
HighscoreManager::HighscoreManager(void)
: configFile(0)
{
}

//---------------------------------------------------------------------------
HighscoreManager::HighscoreManager(std::string path)
{
	loadFile(path);
}

//---------------------------------------------------------------------------
HighscoreManager::~HighscoreManager(void)
{

	floatMap.clear();
	nameMap.clear();
}

//---------------------------------------------------------------------------
void HighscoreManager::loadFile(std::string path)
{
	
	configFile = new ConfigFile();
    configFile->load(path);

    // Go through all sections & settings in the file
    ConfigFile::SectionIterator configFileIterator = configFile->getSectionIterator();

	std::string sectionName, keyName, valueName;
    while (configFileIterator.hasMoreElements())
    {
        sectionName = configFileIterator.peekNextKey();
        
		ConfigFile::SettingsMultiMap *settings = configFileIterator.getNext();
        ConfigFile::SettingsMultiMap::iterator i;
        
		for (i = settings->begin(); i != settings->end(); ++i)
        {
			//PARSE DIFERENT SECTIONS
			if(sectionName == "highscore")
				parseFloat(i->first, i->second);		

        }	
    }
	std::cout << "ConfigFile \"" << path << "\" loaded" << std::endl;
}

//---------------------------------------------------------------------------
float HighscoreManager::getFloatEntry(unsigned int index)
{
	if(index > floatMap.size())
		return -1;
	
	int currentIndex = 0;

	for(std::map<float, std::string>::iterator i = floatMap.begin(); i != floatMap.end(); i++)
	{
		if(currentIndex == index)
			return (*i).first;
		currentIndex++;
	
	}
	return -1;
}

std::string	HighscoreManager::getStringEntry(unsigned int index)
{
	if(index > floatMap.size())
		return "";
	
	int currentIndex = 0;

	for(std::map<float, std::string>::iterator i = floatMap.begin(); i != floatMap.end(); i++)
	{
		
		if(currentIndex == index)
			return (*i).second;
		currentIndex++;
	}
	return "";
}

//---------------------------------------------------------------------------
void HighscoreManager::parseFloat(std::string key, std::string value)
{
	std::stringstream sstr;
 
	float floatValue;
	sstr << value;
	sstr >> floatValue; 

	nameMap[key] = floatValue;
	floatMap[floatValue] = key;
}




void HighscoreManager::writeErrorToConsole(std::string key)
{
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "~~~~~~~~~~~ERROR(HighscoreManager) ~ \"" << key << "\" not found"<< std::endl; 
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

void HighscoreManager::writeHighscoreToConfigFile(std::string path)
{
	std::ofstream file(path.c_str());
	file << "[highscore]\n";

	for(std::map<float, std::string>::iterator i = floatMap.begin(); i!=floatMap.end(); i++)
		file << (*i).second << "=" << (*i).first<< "\n";
	
	file.close();
	
}
void HighscoreManager::insertHighscore(std::string name, float value)
{
	nameMap[name] = value;
	floatMap[value] = name;
}
int	HighscoreManager::getNumberOfHighscoreEntries()
{
	return (int)floatMap.size();
}