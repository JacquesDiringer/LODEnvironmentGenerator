#include "stdafx.h"
#include "OgreInstanciater.h"
#include "OgreInstancedEntity.h"

#include <iostream>


OgreInstanciater::OgreInstanciater(Ogre::ResourceGroupManager& ressourceGroupManager, Ogre::SceneManager* sceneMgr, Ogre::MaterialManager& materialManager)
	: _ressourceGroupManager(ressourceGroupManager), _sceneMgr(sceneMgr), _materialManager(materialManager)
{
	_sceneDisplayablesNodes = unordered_map<shared_ptr<Displayable>, Ogre::SceneNode*>();
	_instanceManagers = unordered_map<string, Ogre::InstanceManager*>();

	_pendingToAddList = vector<shared_ptr<Displayable>>();
	_pendingToRemoveList = vector<shared_ptr<Displayable>>();
}


OgreInstanciater::~OgreInstanciater()
{
}

//void OgreInstanciater::UpdateDisplayables(list<Displayable*> toAdd, list<Displayable*> toRemove)
//{
//	if (!toRemove.empty() || !toAdd.empty())
//	{
//		//std::cout << "Begin update" << std::endl;
//	}
//
//	// Old elements are removed
//	for each (Displayable* diplayableElement in toRemove)
//	{
//		RemoveDisplayable(diplayableElement);
//	}
//
//	// New elements are added
//	for each (Displayable* diplayableElement in toAdd)
//	{
//		AddDisplayable(diplayableElement);
//	}
//
//	if (!toRemove.empty() || !toAdd.empty())
//	{
//		//std::cout << "End update" << std::endl << std::endl;
//	}
//}

void OgreInstanciater::UpdateDisplayables(vector<shared_ptr<Displayable>> toAdd, vector<shared_ptr<Displayable>> toRemove)
{
	// Pending items optimization
	//{
	//	// First check if some unecessary add and remove oprations can be skipped

	//	// Since a list can't be modified while browsed, we will first just take note of the index of pairs to remove
	//	list<Displayable*> invalidatedDisplayables = list<Displayable*>();

	//	if (!_pendingToRemoveList.empty())
	//	{
	//		for each (Displayable* toAddDisplayable in toAdd)
	//		{
	//			for each (Displayable* pendingToRemoveDisplayable in _pendingToRemoveList)
	//			{
	//				// If a Displayable to add is the same than a pending Displayable that was to remove, then remove them from woth lists
	//				if (toAddDisplayable == pendingToRemoveDisplayable)
	//				{
	//					invalidatedDisplayables.push_back(pendingToRemoveDisplayable);
	//				}
	//				// If the references didn't match, try comparing the values
	//				else
	//				{
	//					SimpleObjectDisplayable* displayableA = (SimpleObjectDisplayable*)toAddDisplayable;
	//					SimpleObjectDisplayable* displayableB = (SimpleObjectDisplayable*)pendingToRemoveDisplayable;

	//					if (displayableA != NULL && displayableB != NULL && (*displayableA) == (*displayableB))
	//					{
	//						invalidatedDisplayables.push_back(pendingToRemoveDisplayable);
	//					}
	//				}
	//			}
	//		}
	//	}

	//	// Now use the collected indexes to remove the useless items from both lists
	//	for each (Displayable* displayableToRemove in invalidatedDisplayables)
	//	{
	//		toAdd.remove(displayableToRemove);
	//		_pendingToRemoveList.remove(displayableToRemove);
	//	}



	//	// Dot the same thing for the two other lists, toRemove and _pendingToAddList
	//	invalidatedDisplayables.clear();

	//	// If displayables to remove where on the add list previously, remove them from both lists

	//	if (!_pendingToAddList.empty())
	//	{
	//		for each (Displayable* toRemoveDisplayable in toRemove)
	//		{
	//			for each (Displayable* pendingToAddDisplayable in _pendingToAddList)
	//			{
	//				// If a Displayable to add is the same than a pending Displayable that was to remove, then remove them from woth lists
	//				if (toRemoveDisplayable == pendingToAddDisplayable)
	//				{
	//					invalidatedDisplayables.push_back(pendingToAddDisplayable);
	//				}
	//				// If the references didn't match, try comparing the values
	//				else
	//				{
	//					SimpleObjectDisplayable* displayableA = (SimpleObjectDisplayable*)toRemoveDisplayable;
	//					SimpleObjectDisplayable* displayableB = (SimpleObjectDisplayable*)pendingToAddDisplayable;

	//					if (displayableA != NULL && displayableB != NULL && (*displayableA) == (*displayableB))
	//					{
	//						invalidatedDisplayables.push_back(pendingToAddDisplayable);
	//					}
	//				}
	//			}
	//		}
	//	}

	//	// Now use the collected indexes to remove the useless items from both lists
	//	for each (Displayable* displayableToRemove in invalidatedDisplayables)
	//	{
	//		toRemove.remove(displayableToRemove);
	//		_pendingToRemoveList.remove(displayableToRemove);
	//	}

	//}


	// Now that useless occurences have been eliminated, just add the elements to the pending lists


	int iteratorId = 0;
	for each (shared_ptr<Displayable> currentDisplayable in toAdd)
	{
		++iteratorId;
		_pendingToAddList.push_back(currentDisplayable);
	}

	iteratorId = 0;
	for each (shared_ptr<Displayable> currentDisplayable in toRemove)
	{
		++iteratorId;
		_pendingToRemoveList.push_back(currentDisplayable);
	}
}

void OgreInstanciater::Flush(int addCount, int removeCount)
{
	vector<shared_ptr<Displayable>>::iterator displayableIterator;

	// Old elements are removed
	if (!_pendingToRemoveList.empty())
	{
		int toRemoveSize = _pendingToRemoveList.size();
		displayableIterator = _pendingToRemoveList.end();

		for (int removeIndex = 0; removeIndex < removeCount && removeIndex < toRemoveSize; ++removeIndex)
		{
			--displayableIterator;
			RemoveDisplayable(*displayableIterator);
		}

		int numberOfItemsToRemove = std::min(removeCount, (int)_pendingToRemoveList.size());
		for (int removeIndex = 0; removeIndex < numberOfItemsToRemove; ++removeIndex)
		{
			_pendingToRemoveList.pop_back();
		}
	}


	// New elements are added
	if (!_pendingToAddList.empty())
	{
		int toAddSize = _pendingToAddList.size();
		displayableIterator = _pendingToAddList.end();

		for (int addIndex = 0; addIndex < addCount && addIndex < toAddSize; ++addIndex)
		{
			--displayableIterator;
			AddDisplayable(*displayableIterator);
		}

		int numberOfItemsToRemove = std::min(removeCount, (int)_pendingToAddList.size());
		for (int addIndex = 0; addIndex < numberOfItemsToRemove; ++addIndex)
		{
			_pendingToAddList.pop_back();
		}
	}
}

bool OgreInstanciater::IsFlushCompleted()
{
	return _pendingToAddList.size() == 0 && _pendingToRemoveList.size() == 0;
}


bool OgreInstanciater::AddDisplayable(shared_ptr<Displayable> newDisplayable)
{
	shared_ptr<SimpleObjectDisplayable> simpleObject = std::dynamic_pointer_cast<SimpleObjectDisplayable>(newDisplayable);

	if (simpleObject != nullptr)
	{
		return AddSimpleObjectDisplayable(simpleObject);
	}
	return false;
}

bool OgreInstanciater::RemoveDisplayable(shared_ptr<Displayable> displayableToRemove)
{
	auto findIterator = _sceneDisplayablesNodes.find(displayableToRemove);

	if (findIterator == _sceneDisplayablesNodes.end())
	{
		shared_ptr<SimpleObjectDisplayable> simpleObject = std::dynamic_pointer_cast<SimpleObjectDisplayable>(displayableToRemove);
		if (simpleObject != nullptr)
		{
			std::cout << "The displayable to remove could not be found, modelName : " << simpleObject->GetModelName() << std::endl;
		}
		else
		{
			std::cout << "The displayable to remove could not be found, modelName : " << std::endl;
		}
		return false;
	}

	Ogre::SceneNode* nodeToRemove = findIterator->second;

	// TODO: make sure that the node AND the entity are deleted correctly
	nodeToRemove->removeAndDestroyAllChildren();
	_sceneMgr->destroySceneNode(nodeToRemove);

	// Remove the element from the Displayable SceneNode map
	_sceneDisplayablesNodes.erase(findIterator);

	//std::cout << "Removed : " << ((SimpleObjectDisplayable*)displayableToRemove)->GetTextureName() << std::endl;

	return true;
}

bool OgreInstanciater::AddSimpleObjectDisplayable(shared_ptr<SimpleObjectDisplayable> newSimpleObjectDisplayable)
{
	// Non instanciated version

	Ogre::String lNameOfTheMesh = newSimpleObjectDisplayable->GetModelName();
	Ogre::String lNameOfTheTexture = newSimpleObjectDisplayable->GetTextureName();

	Ogre::SceneNode* lRootSceneNode = _sceneMgr->getRootSceneNode();

	// Mesh entity loading
	Ogre::Entity* lEntity = _sceneMgr->createEntity(lNameOfTheMesh);
	// Now I attach it to a scenenode, so that it becomes present in the scene.
	Ogre::SceneNode* lNode = lRootSceneNode->createChildSceneNode();
	lNode->attachObject(lEntity);

	Quaternion entityQuaternion = newSimpleObjectDisplayable->GetWorldMatrix().ComputeQuaternion();
	Ogre::Quaternion ogreQuat = Ogre::Quaternion(entityQuaternion.GetW(), entityQuaternion.GetX(), entityQuaternion.GetY(), entityQuaternion.GetZ());
	lNode->rotate(ogreQuat);
	Vector3 entityPosition = newSimpleObjectDisplayable->GetWorldMatrix().Position();
	lNode->translate(entityPosition.X(), entityPosition.Y(), entityPosition.Z());

	// Material
	lEntity->setMaterialName(lNameOfTheTexture);

	// Remember the associated ogre node, to be able to remove it later
	_sceneDisplayablesNodes.insert(std::pair<shared_ptr<Displayable>, Ogre::SceneNode*>(newSimpleObjectDisplayable, lNode));

	//std::cout << "Added : " << newSimpleObjectDisplayable->GetTextureName() << std::endl;

	return true;




	/// instanced version ///


	//Ogre::String lNameOfTheMesh = newSimpleObjectDisplayable->GetModelName();
	//Ogre::String lNameOfTheTexture = newSimpleObjectDisplayable->GetTextureName();

	//Ogre::SceneNode* lRootSceneNode = _sceneMgr->getRootSceneNode();

	//Ogre::InstancedEntity* lEntity = GetInstancedEntity(lNameOfTheMesh, lNameOfTheTexture);
	//// Now I attach it to a scenenode, so that it becomes present in the scene.
	//Ogre::SceneNode* lNode = lRootSceneNode->createChildSceneNode();
	//lNode->attachObject(lEntity);

	//Quaternion entityQuaternion = newSimpleObjectDisplayable->GetWorldMatrix().ComputeQuaternion();
	//Ogre::Quaternion ogreQuat = Ogre::Quaternion(entityQuaternion.GetW(), entityQuaternion.GetX(), entityQuaternion.GetY(), entityQuaternion.GetZ());
	//lNode->rotate(ogreQuat);
	//Vector3 entityPosition = newSimpleObjectDisplayable->GetWorldMatrix().Position();
	//lNode->translate(entityPosition.X(), entityPosition.Y(), entityPosition.Z());

	////// Remember the associated ogre node, to be able to remove it later
	//_sceneDisplayablesNodes.insert(std::pair<Displayable*, Ogre::SceneNode*>(newSimpleObjectDisplayable, lNode));

	////std::cout << "Added : " << newSimpleObjectDisplayable->GetTextureName() << std::endl;

	//Ogre::Vector3 entityPositionOgre = lEntity->getPosition();
	//lEntity->setPosition(Ogre::Vector3(entityPosition.X(), entityPosition.Y(), entityPosition.Z()));
	//lEntity->setOrientation(ogreQuat);

	//entityPositionOgre = lEntity->getPosition();

	//lEntity->updateTransforms();

	//return true;
}

Ogre::InstancedEntity* OgreInstanciater::GetInstancedEntity(string meshName, string textureName)
{
	string managerName = meshName + textureName;
	Ogre::InstanceManager* instanceManager;

	auto findIterator = _instanceManagers.find(managerName);

	if (findIterator != _instanceManagers.end())
	{
		instanceManager = findIterator->second;
	}
	else
	{
		// This mesh has not been previously instanciated, we need to create a new InstanceManager


		// TODO: figure flags out
		// TODO: experiment with the different InstancingTechnique, play with the different parameters
		instanceManager = _sceneMgr->createInstanceManager(managerName, meshName, "Meshes", Ogre::InstanceManager::InstancingTechnique::HWInstancingBasic, 2000);
		_instanceManagers.insert(std::pair<string, Ogre::InstanceManager*>(managerName, instanceManager));
	}

	Ogre::InstancedEntity* result = instanceManager->createInstancedEntity(textureName);
	return result;
}