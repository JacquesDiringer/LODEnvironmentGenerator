#pragma once

#include <vector>

#include "Displayable.h"
#include "LevelFactory.h"
#include "Vector3.h"
#include "Matrix4.h"

using std::vector;
using namespace Math;


#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Generator
{
	class GENERATOR_API Item
	{
	public:
		Item();
		Item(Matrix4 relativeMatrix, Item* parent, float expansionDistance, Displayable* displayable, LevelFactory* subLevelFactory);
		~Item();

		void UpdateParentToRetract(Vector3 cameraPosition, Vector3 cameraSpeed, vector<Item*>* parentsToRetract, vector<Item*>* childrenToRemove);

		// Fills a vector of items to remove, has to be called from a retracting parent, basically recursively finds all the leaves from this parent
		void UpdateChildrenToRemove(vector<Item*>* childrenToRemove);

		// Fills a vector of items to add, has to be called from an expanding parent
		void UpdateChildrenToAdd(Vector3 cameraPosition, Vector3 cameraSpeed, vector<Item*>* childrenToAdd);

		// True if the Item need to be expanded (generate children), according to the camera position and speed, bounding boxe, etc...
		bool NeedExpansion(Vector3 cameraPosition, Vector3 cameraSpeed);

		// Overrides
		inline bool operator == (const Item &b)
		{
			// TODO: fix this
			return _displayableContent == b.GetDisplayableContent();
		}

		// Getters and setters
		Displayable* GetDisplayableContent(void) const {return _displayableContent;}
		Item* GetParent() const { return _parent; }
		float GetExpansionDistance() const { return _expansionDistance; }

		bool GetUpdateChecked() const { return _updateChecked; }
		void SetUpdateChecked(bool value) { _updateChecked = value; }

		const Matrix4& GetWorldMatrix() const { return _worldMatrix; }

		// This will set the relative matrix but also update the world matrix using the parent
		const Matrix4& GetRelativeMatrix() const { return _relativeMatrix; }
		void SetRelativeMatrix(Matrix4 relativeMatrix);

		unsigned int GetId() const{ return _id; }

		int GetChildrenCount() const { return _children.size(); }

		void SetId(unsigned int id);

	private:
		unsigned int _id;
		float _expansionDistance;
		Displayable* _displayableContent;
		Item* _parent;
		vector<Item*> _children;
		LevelFactory* _subLevelFactory;
		Matrix4 _worldMatrix;
		Matrix4 _relativeMatrix;
		bool _updateChecked;
	};


}