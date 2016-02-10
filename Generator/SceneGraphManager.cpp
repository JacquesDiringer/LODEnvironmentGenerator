#include "stdafx.h"

#include <algorithm>

#include "SceneGraphManager.h"
#include "Displayable.h"


using std::find;

namespace Generator
{
	SceneGraphManager::SceneGraphManager()
	{
		_sceneCurrentItems = list<Item*>();
		_sceneTotalItems = list<Item*>();
		_toAdd = list<Item*>();
		_toRemove = list<Item*>();
	}

	SceneGraphManager::SceneGraphManager(Instanciater* instanciater)
		: _instanciater(instanciater)
	{
		_sceneCurrentItems = list<Item*>();
		_sceneTotalItems = list<Item*>();
		_toAdd = list<Item*>();
		_toRemove = list<Item*>();
	}


	SceneGraphManager::~SceneGraphManager()
	{
	}


	bool SceneGraphManager::QueueAddItem(Item* newItem)
	{
		_toAdd.push_back(newItem);

		return true;
	}


	bool SceneGraphManager::QueueRemoveItem(Item* itemToRemove)
	{
		list<Item*>::iterator findIterator = find(_sceneCurrentItems.begin(), _sceneCurrentItems.end(), itemToRemove);
		if (findIterator != _sceneCurrentItems.end())
		{
			// The item has been found, add it to the items to add list
			_toRemove.push_back(itemToRemove);
			return true;
		}

		// Item was not found in the scene list
		return false;
	}


	void SceneGraphManager::Flush(void)
	{
		list<Displayable*> displayableToRemove = list<Displayable*>();
		list<Displayable*> displayableToAdd = list<Displayable*>();

		for each (Item* itemToRemove in _toRemove)
		{
			// Fill the diplayable remove list, for the instanciater
			Displayable* displayable = itemToRemove->GetDisplayableContent();

			if (displayable != NULL)
			{
				displayableToRemove.push_back(displayable);
			}

			// TODO: do some removing shit
			_sceneCurrentItems.remove(itemToRemove);
			_sceneTotalItems.remove(itemToRemove);
		}
		// Empty the list after it has been used to fill the displayable list and update scene's currents items
		_toRemove.clear();

		for each (Item* newItem in _toAdd)
		{
			// Fill the diplayable add list, for the instanciater
			Displayable* displayable = newItem->GetDisplayableContent();

			if (displayable != NULL)
			{
				displayableToAdd.push_back(displayable);
			}

			// TODO: do some adding shit
			_sceneCurrentItems.push_back(newItem);
			_sceneTotalItems.push_back(newItem);
		}
		// Empty the list after it has been used to fill the displayable list and update scene's currents items
		_toAdd.clear();
		
		_instanciater->UpdateDisplayables(displayableToAdd, displayableToRemove);
	}


	void SceneGraphManager::Update(Vector3 cameraPosition, Vector3 cameraSpeed)
	{
		// The _updateChecked boolean of all items is set to false, it will be set to true at the retracting step for all items having a parent that is retracting
		for each (Item* currentItem in _sceneCurrentItems)
		{
			currentItem->SetUpdateChecked(false);
		}

		// This is the retraction pass, it handles items that need to show less details
		{
			// First, we browse all existing items to fill a list of parents that need to be retracted, and the list of their children who will be removed
			list<Item*>* parentsToRetract = new list<Item*>();
			list<Item*>* childrenToRemove = new list<Item*>();

			for each (Item* item in _sceneCurrentItems)
			{
				// We don't want to check an item that we know has already been checked and is to be removed because it's father is to be retracted
				if (!item->GetUpdateChecked())
				{
					Item* parent = item->GetParent();
					if (parent != NULL)
					{
						if (!parent->NeedExpansion(cameraPosition, cameraSpeed))
						{
							parent->UpdateParentToRetract(cameraPosition, cameraSpeed, parentsToRetract, childrenToRemove);
						}
					}
				}
			}

			// We now know which items have to be (re)created (as retracting parents) and which items have to be removed (as children of a retracting parent)
			// First the children are removed
			for each (Item* childToRemove in *childrenToRemove)
			{
				QueueRemoveItem(childToRemove);
			}

			// The retracted parents will then need to be added to the scene
			for each (Item* parentToAdd in *parentsToRetract)
			{
				QueueAddItem(parentToAdd);
			}
		} // The up pass is now done, items that needed less details have been handled

		// This is the expansion pass, it handles items that need to show more details
		{
			list<Item*>* childrenToAdd = new list<Item*>();
			for each (Item* item in _sceneCurrentItems)
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
						item->UpdateChildrenToAdd(cameraPosition, cameraSpeed, childrenToAdd);
					}
					item->SetUpdateChecked(true);
				}
			}

			// Add the items resulting from the expansions
			for each (Item* itemToAdd in *childrenToAdd)
			{
				QueueAddItem(itemToAdd);
			}
		}
	}
}