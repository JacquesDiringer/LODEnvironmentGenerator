#include "stdafx.h"

#include <algorithm>

#include "SceneGraphManager.h"
#include "Displayable.h"

using std::find;

namespace Generator
{
	SceneGraphManager::SceneGraphManager()
	{
		_sceneCurrentItems = unordered_set<shared_ptr<Item>>();
		_toAdd = vector<shared_ptr<Item>>();
		_toRemove = vector<shared_ptr<Item>>();
	}

	SceneGraphManager::SceneGraphManager(Instanciater* instanciater)
		: _instanciater(instanciater)
	{
		_sceneCurrentItems = unordered_set<shared_ptr<Item>>();
		_toAdd = vector<shared_ptr<Item>>();
		_toRemove = vector<shared_ptr<Item>>();
	}


	SceneGraphManager::~SceneGraphManager()
	{
	}


	bool SceneGraphManager::QueueAddItem(shared_ptr<Item> newItem)
	{
		_toAdd.push_back(newItem);

		return true;
	}


	bool SceneGraphManager::QueueRemoveItem(shared_ptr<Item> itemToRemove)
	{
		unordered_set<shared_ptr<Item>>::iterator findIterator = _sceneCurrentItems.find(itemToRemove);
		if (findIterator != _sceneCurrentItems.end())
		{
			// The item has been found, add it to the items to add vector
			_toRemove.push_back(itemToRemove);
			return true;
		}

		// Item was not found in the scene vector
		return false;
	}


	void SceneGraphManager::Flush(void)
	{
		vector<Displayable*> displayableToRemove = vector<Displayable*>();
		vector<Displayable*> displayableToAdd = vector<Displayable*>();

		for each(shared_ptr<Item> itemToRemoveIt in _toRemove)
		{
			// Fill the diplayable remove vector, for the instanciater
			Displayable* displayable = itemToRemoveIt->GetDisplayableContent();

			if (displayable != NULL)
			{
				displayableToRemove.push_back(displayable);
			}

			// TODO: do some removing shit
			_sceneCurrentItems.erase(itemToRemoveIt);
		}
		// Empty the vector after it has been used to fill the displayable vector and update scene's currents items
		_toRemove.clear();

		for each (shared_ptr<Item> newItem in _toAdd)
		{
			// Fill the diplayable add vector, for the instanciater
			Displayable* displayable = newItem->GetDisplayableContent();

			if (displayable != NULL)
			{
				displayableToAdd.push_back(displayable);
			}

			// TODO: do some adding shit
			_sceneCurrentItems.insert(newItem);
		}
		// Empty the vector after it has been used to fill the displayable vector and update scene's currents items
		_toAdd.clear();
		
		_instanciater->UpdateDisplayables(displayableToAdd, displayableToRemove);
	}


	void SceneGraphManager::Update(const Vector3& cameraPosition, const Vector3& cameraSpeed)
	{
		// The _updateChecked boolean of all items is set to false, it will be set to true at the retracting step for all items having a parent that is retracting
		for each (shared_ptr<Item> currentItem in _sceneCurrentItems)
		{
			currentItem->SetUpdateChecked(false);
		}

		// This is the retraction pass, it handles items that need to show less details
		{
			// First, we browse all existing items to fill a vector of parents that need to be retracted, and the vector of their children who will be removed
			vector<shared_ptr<Item>> parentsToRetract = vector<shared_ptr<Item>>();
			vector<shared_ptr<Item>> childrenToRemove = vector<shared_ptr<Item>>();

			for each (shared_ptr<Item> item in _sceneCurrentItems)
			{
				// We don't want to check an item that we know has already been checked and is to be removed because it's father is to be retracted
				if (!item->GetUpdateChecked())
				{
					shared_ptr<Item> parent = item->GetParent().lock();
					if (parent != nullptr)
					{
						if (!parent->NeedExpansion(cameraPosition, cameraSpeed))
						{
							parent->UpdateParentToRetract(cameraPosition, cameraSpeed, &parentsToRetract, &childrenToRemove);
						}
					}
				}
			}

			// We now know which items have to be (re)created (as retracting parents) and which items have to be removed (as children of a retracting parent)
			// First the children are removed
			for each (shared_ptr<Item> childToRemove in childrenToRemove)
			{
				QueueRemoveItem(childToRemove);
			}

			// The retracted parents will then need to be added to the scene
			for each (shared_ptr<Item> parentToAdd in parentsToRetract)
			{
				QueueAddItem(parentToAdd);
			}
		} // The up pass is now done, items that needed less details have been handled

		// This is the expansion pass, it handles items that need to show more details
		{
			vector<shared_ptr<Item>> childrenToAdd = vector<shared_ptr<Item>>();
			for each (shared_ptr<Item> item in _sceneCurrentItems)
			{
				// We don't want to check an item that we know has already been checked and is to be removed because it's father is to be retracted
				if (!item->GetUpdateChecked())
				{
					// TODO: add a test to check if the item is expandable (has a sub level factory), for optimization purposes
					if (item->NeedExpansion(cameraPosition, cameraSpeed))
					{
						// The item needs to be expanded
						// Therefore, remove it from the scene
						QueueRemoveItem(item);

						// And add it's direct or indirect children to the scene
						// We first need to find them recursively
						item->UpdateChildrenToAdd(cameraPosition, cameraSpeed, &childrenToAdd);
					}
					item->SetUpdateChecked(true);
				}
			}

			// Add the items resulting from the expansions
			for each (shared_ptr<Item> itemToAdd in childrenToAdd)
			{
				QueueAddItem(itemToAdd);
			}
		}
	}
}