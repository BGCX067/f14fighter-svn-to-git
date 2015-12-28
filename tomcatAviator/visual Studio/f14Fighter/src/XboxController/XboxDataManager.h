#ifndef XBOX_DATA_MANAGER_H_
#define XBOX_DATA_MANAGER_H_

#include "MyController.h"
class XboxDataManager
{

public:	
	static XboxDataManager*				getDataManagerAsSingleton(); // returns a pointer to a DataManager. DataManager is implemented as Singleton
	MyController							controller[4];

private:
	XboxDataManager(void);
	~XboxDataManager(void);

	static XboxDataManager*				_instance;
};
#endif