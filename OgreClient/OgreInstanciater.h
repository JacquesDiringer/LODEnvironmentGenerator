#pragma once

#include <Instanciater.h>
#include <Displayable.h>
#include <SimpleObjectDisplayable.h>
#include <Quaternion.h>

#include <vector>
#include <unordered_map>

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <memory>

using std::vector;
using std::unordered_map;
using std::shared_ptr;

using namespace Generator;

class OgreInstanciater :
	public Instanciater
{
public:
	OgreInstanciater(Ogre::ResourceGroupManager& ressourceGroupManager, Ogre::SceneManager* sceneMgr, Ogre::MaterialManager& materialManager);
	~OgreInstanciater(void);

	virtual void UpdateDisplayables(const vector<shared_ptr<Displayable>>& toAdd, const vector<shared_ptr<Displayable>>& toRemove);

	void Flush(int addCount, int removeCount);

	bool IsFlushCompleted();

private:
	unordered_map<shared_ptr<Displayable>, Ogre::SceneNode*> _sceneDisplayablesNodes;
	unordered_map<string, Ogre::InstanceManager*> _instanceManagers;

	vector<shared_ptr<Displayable>> _pendingToAddList;
	vector<shared_ptr<Displayable>> _pendingToRemoveList;

	Ogre::ResourceGroupManager& _ressourceGroupManager;
	Ogre::SceneManager* _sceneMgr;
	Ogre::MaterialManager& _materialManager;

private:
	bool AddDisplayable(shared_ptr<Displayable> newDisplayable);
	bool RemoveDisplayable(shared_ptr<Displayable> displayableToRemove);

	bool AddSimpleObjectDisplayable(shared_ptr<SimpleObjectDisplayable> newSimpleObjectDisplayable);

	Ogre::InstancedEntity* GetInstancedEntity(string meshName, string textureName);

};

