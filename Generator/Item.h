#pragma once

#include <vector>
#include <memory>

#include "Displayable.h"
#include "LevelFactory.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "ParametricPlane.h"

using std::vector;
using std::shared_ptr;
using std::weak_ptr;

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Generator
{
	class GENERATOR_API Item : public std::enable_shared_from_this<Item>
	{
	public:
		Item();
		Item(Math::Matrix4 relativeMatrix, shared_ptr<Item> parent, float expansionDistance, const vector<Math::ParametricPlane*>& visibilityPlanes, bool andCondition, shared_ptr<Displayable> displayable, LevelFactory* subLevelFactory);
		~Item();

		void UpdateParentToRetract(const Math::Vector3& cameraPosition, const Math::Vector3& cameraSpeed, vector<shared_ptr<Item>>* parentsToRetract, vector<shared_ptr<Item>>* childrenToRemove);

		// Fills a vector of items to remove, has to be called from a retracting parent, basically recursively finds all the leaves from this parent
		void UpdateChildrenToRemove(vector<shared_ptr<Item>>* childrenToRemove);

		// Fills a vector of items to add, has to be called from an expanding parent
		void UpdateChildrenToAdd(const Math::Vector3& cameraPosition, const Math::Vector3& cameraSpeed, vector<shared_ptr<Item>>* childrenToAdd);

		// True if the cameraPosition vector satisfies the visibilty planes condition.
		bool VisibiltyPlanesSatisfied(const Math::Vector3 & cameraPosition) const;

		// True if the Item need to be expanded (generate children), according to the camera position and speed, bounding boxe, etc...
		bool NeedExpansion(const Math::Vector3& cameraPosition, const Math::Vector3& cameraSpeed) const;

		// Overrides
		inline bool operator == (const Item &b)
		{
			// TODO: fix this
			return _displayableContent == b.GetDisplayableContent();
		}

		// Getters and setters
		shared_ptr<Displayable> GetDisplayableContent(void) const {return _displayableContent;}
		shared_ptr<Item> GetParent() const { return _parent; }
		float GetExpansionDistance() const { return _expansionDistance; }

		bool GetUpdateChecked() const { return _updateChecked; }
		void SetUpdateChecked(bool value) { _updateChecked = value; }

		const Math::Matrix4& GetWorldMatrix() const { return _worldMatrix; }

		// This will set the relative matrix but also update the world matrix using the parent
		const Math::Matrix4& GetRelativeMatrix() const { return _relativeMatrix; }
		void SetRelativeMatrix(Math::Matrix4 relativeMatrix);

		unsigned int GetId() const{ return _id; }

		int GetChildrenCount() const { return _children.size(); }

		void SetId(unsigned int id);

	private:
		// This function updates the list of parametric planes in world space.
		// It needs the Item's _worldMatrix to be up to date, as well as _relavtiveVisibilityPlanes.
		void ComputeWorldParametricPlanes();

	private:
		unsigned int _id;
		float _expansionDistance;
		// A vector of parametric planes that count as an additionnal condition to determine whether the sub level should be expanded or not.
		// These planes will contain parametrization in world space.
		vector<Math::ParametricPlane> _worldVisibilityPlanes;
		// These planes will contain parametrization in space relative to the Item.
		vector<Math::ParametricPlane> _relavtiveVisibilityPlanes;
		// When true all visibility planes have to return true, when false only one visibility plane true is enough.
		// This allows to differentiate when we should be inside a volume or outside of it.
		bool _visibilityPlanesAndCondition;
		shared_ptr<Displayable> _displayableContent;
		shared_ptr<Item> _parent;
		vector<shared_ptr<Item>> _children;
		LevelFactory* _subLevelFactory;
		Math::Matrix4 _worldMatrix;
		Math::Matrix4 _relativeMatrix;
		bool _updateChecked;
	};


}