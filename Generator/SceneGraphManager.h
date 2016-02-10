#pragma once

#include <list>

#include "Item.h"
#include "Instanciater.h"
#include "Vector3.h"

using std::list;

using namespace Math;

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Generator
{
	class GENERATOR_API SceneGraphManager
	{
	public:
		SceneGraphManager();
		SceneGraphManager(Instanciater* instanciater);
		~SceneGraphManager();

		bool QueueAddItem(Item* newItem);
		bool QueueRemoveItem(Item* itemToRemove);

		// Gathers the Displayables content and sends them to the instanciater
		void Flush(void);

		// Browses the items and sees which need to be upped (go back to the parent level) or downed (create the children of the item)
		void Update(Vector3 cameraPosition, Vector3 cameraSpeed);

	private:
		list<Item*> _sceneCurrentItems;
		list<Item*> _sceneTotalItems;

		list<Item*> _toAdd;
		list<Item*> _toRemove;

		Instanciater* _instanciater;
	};


}