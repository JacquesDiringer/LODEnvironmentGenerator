#ifndef __OgreClient_h_
#define __OgreClient_h_

#include "BaseApplication.h"

#include "SceneGraphManager.h"

#include "OgreInstanciater.h"

#include <string>

#include <thread>


using std::string;

class OgreClient : public BaseApplication
{
public:
	OgreClient(void);
	virtual ~OgreClient(void);

protected:
	virtual void createScene(void);

	virtual bool frameStarted(const Ogre::FrameEvent& evt);

private:
	//Generator::CGenerator * _testGenerator;
	Generator::SceneGraphManager _sceneManager;
	OgreInstanciater* _ogreInstanciater;
	Ogre::Vector3 _lastCameraPosition;

	std::thread _proceduralGeneratorThread;
	bool _threadInitialized;

	float _timeSinceLastUpdate;

private:
	//void RefreshGenerator();

};
#endif