#pragma once

#include <vector>
#include <unordered_set>
#include <atomic>

#include "Item.h"
#include "Instanciater.h"
#include "Vector3.h"

using std::vector;
using std::unordered_set;

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

		bool QueueAddItem(shared_ptr<Item> newItem);
		bool QueueRemoveItem(shared_ptr<Item> itemToRemove);

		// Gathers the Displayables content and sends them to the instanciater
		void Flush(void);

		// Browses the items and sees which need to be upped (go back to the parent level) or downed (create the children of the item)
		void Update(const Math::Vector3& cameraPosition, const Math::Vector3& cameraSpeed);

		// Returns false if the SceneGraphManager is currently updating the scene.
		bool IsUpdateFinished() const { return _updateFinished; }

	private:
		unordered_set<shared_ptr<Item>> _sceneCurrentItems;

		vector<shared_ptr<Item>> _toAdd;
		vector<shared_ptr<Item>> _toRemove;

		Instanciater* _instanciater;

		// For multi-threading purposes, the scene graph manager signals if it is currently computing the new scene.
		//std::atomic_bool _updateFinished{ true };
		bool _updateFinished = true;
	};


}