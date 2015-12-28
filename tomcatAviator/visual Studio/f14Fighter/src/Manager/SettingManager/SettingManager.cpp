#include "SettingManager.h"

//---------------------------------------------------------------------------
SettingManager::SettingManager(void)
: configFile(0), tempVector(Vector3(0,0,0))
{
}

//---------------------------------------------------------------------------
SettingManager::SettingManager(std::string path)
{
	loadFile(path);
}

//---------------------------------------------------------------------------
SettingManager::~SettingManager(void)
{

	floatMap.clear();
	intMap.clear();
	stringMap.clear();
	vector3Map.clear();
}

//---------------------------------------------------------------------------
void SettingManager::loadFile(std::string path)
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
			if(sectionName == "float")
				parseFloat(i->first, i->second);		
			else if(sectionName == "int")
				parseInt(i->first, i->second);
            else if(sectionName == "Vector3")
				parseVector3(i->first, i->second);
			else if(sectionName == "string")
				parseString(i->first, i->second);
        }	
    }
	std::cout << "ConfigFile \"" << path << "\" loaded" << std::endl;
}
//---------------------------------------------------------------------------
float SettingManager::getFloat(std::string key)
{
	//std::cout << &floatMap.find(key);
	
	for(std::map<std::string, float>::iterator i = floatMap.begin(); i != floatMap.end(); i++)
	{
		if((*i).first == key)
		{
			return (*i).second;
		}
	}
	writeErrorToConsole(key);
	return -1.0;
}

//---------------------------------------------------------------------------
int SettingManager::getInt(std::string key)
{
	for(std::map<std::string, int>::iterator i = intMap.begin(); i != intMap.end(); i++)
	{
		if((*i).first == key)
		{
			return (*i).second;
		}
	}
	writeErrorToConsole(key);
	return -1;
}

//---------------------------------------------------------------------------
std::string SettingManager::getString(std::string key)
{
	for(std::map<std::string, std::string>::iterator i = stringMap.begin(); i != stringMap.end(); i++)
	{
		if((*i).first == key)
		{
			return (*i).second;
		}
	}
	writeErrorToConsole(key);
	return "";
}

//---------------------------------------------------------------------------
Vector3 SettingManager::getVector3(std::string key)
{	
	for(std::map<std::string, Vector3>::iterator i = vector3Map.begin(); i != vector3Map.end(); i++)
	{
		if((*i).first == key)
		{
			return (*i).second;
		}
	}
	writeErrorToConsole(key);
	return Vector3(0,0,0);
}


//---------------------------------------------------------------------------
void SettingManager::parseFloat(std::string key, std::string value)
{
	std::stringstream sstr;
 
	float floatValue;
	sstr << value;
	sstr >> floatValue; 

	floatMap[key] = floatValue;
}

//---------------------------------------------------------------------------
void SettingManager::parseInt(std::string key, std::string value)
{
	std::stringstream sstr;
 
	int intValue;
	sstr << value;
	sstr >> intValue; 

	intMap[key] = intValue;
}

//---------------------------------------------------------------------------
void SettingManager::parseString(std::string key, std::string value)
{

	stringMap[key] = value;
}

//---------------------------------------------------------------------------
void SettingManager::parseVector3(std::string key, std::string value)
{
	int pos = (int)key.find(".");
	
	//grab substrings
	std::string newKey = key.substr(0,pos);
	std::string vectorDimension = key.substr(pos+1,key.size());
	
	std::stringstream sstr;
 
	float floatValue;
	sstr << value;
	sstr >> floatValue; 

	if(vectorDimension == "x")
		tempVector.x = floatValue;
	if(vectorDimension == "y")
		tempVector.y = floatValue;
	if(vectorDimension == "z")
	{
		tempVector.z = floatValue;
		vector3Map[newKey] = tempVector;
		tempVector = Vector3(0,0,0);
	}
	
}
void SettingManager::writeErrorToConsole(std::string key)
{
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "~~~~~~~~~~~ERROR(SettingManager) ~ \"" << key << "\" not found"<< std::endl; 
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}