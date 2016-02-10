#pragma once

#include <Instanciater.h>
#include <Displayable.h>
#include <SimpleObjectDisplayable.h>
#include <Quaternion.h>

#include <list>
#include <map>

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

using std::list;
using std::map;

using namespace Generator;

class OgreInstanciater :
	public Instanciater
{
public:
	OgreInstanciater(Ogre::ResourceGroupManager& ressourceGroupManager, Ogre::SceneManager* sceneMgr, Ogre::MaterialManager& materialManager);
	~OgreInstanciater(void);

	virtual void UpdateDisplayables(list<Displayable*> toAdd, list<Displayable*> toRemove);

	void Flush(int addCount, int removeCount);

	bool IsFlushCompleted();

private:
	map<Displayable*, Ogre::SceneNode*> _sceneDisplayablesNodes;
	map<string, Ogre::InstanceManager*> _instanceManagers;

	list<Displayable *> _pendingToAddList;
	list<Displayable *> _pendingToRemoveList;

	Ogre::ResourceGroupManager& _ressourceGroupManager;
	Ogre::SceneManager* _sceneMgr;
	Ogre::MaterialManager& _materialManager;

private:
	bool AddDisplayable(Displayable* newDisplayable);
	bool RemoveDisplayable(Displayable* displayableToRemove);

	bool AddSimpleObjectDisplayable(SimpleObjectDisplayable* newSimpleObjectDisplayable);

	Ogre::InstancedEntity* GetInstancedEntity(string meshName, string textureName);

};

