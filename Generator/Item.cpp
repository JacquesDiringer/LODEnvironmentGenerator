#include "stdafx.h"
#include "Item.h"

#include <exception>

using std::exception;


namespace Generator
{
	Item::Item()
	{
	}

	Item::Item(Math::Matrix4 relativeMatrix, shared_ptr<Item> parent, float expansionDistance, const vector<Math::ParametricPlane*>& visibilityPlanes, bool andCondition, shared_ptr<Displayable> displayable, LevelFactory* subLevelFactory)
		: _parent(parent), _expansionDistance(expansionDistance), _visibilityPlanesAndCondition(andCondition), _displayableContent(displayable), _subLevelFactory(subLevelFactory)
	{
		_children = vector<shared_ptr<Item>>();

		// Create visibility planes with parametrization in space relative to the item. This is equal to the planes in the contructor's arguments.
		_relavtiveVisibilityPlanes = vector<Math::ParametricPlane>();
		_relavtiveVisibilityPlanes.reserve(visibilityPlanes.size());

		for (Math::ParametricPlane* localSpacePlane : visibilityPlanes)
		{
			_relavtiveVisibilityPlanes.push_back(Math::ParametricPlane(*localSpacePlane));
		}

		// Create visibility planes with parametrization in world space, according to the Item's world matrix.
		_worldVisibilityPlanes = vector<Math::ParametricPlane>();
		_worldVisibilityPlanes.reserve(visibilityPlanes.size());

		// Set the relative matrix, which triggers world matrix computation.
		SetRelativeMatrix(relativeMatrix);
		SetId(std::hash<Math::Matrix4>()(_worldMatrix));

		// Validity testing
		if (parent != nullptr)
		{
			if (_expansionDistance >= parent->GetExpansionDistance())
			{
				throw new exception("The created item expansion distance should be strictly inferior to the expansion distance of it's parent");
			}
		}
	}

	Item::~Item()
	{
	}

	void Item::UpdateParentToRetract(const Math::Vector3& cameraPosition, const Math::Vector3& cameraSpeed, vector<shared_ptr<Item>>* parentsToRetract, vector<shared_ptr<Item>>* childrenToRemove)
	{
		if (_parent != nullptr)
		{
			if (_parent->NeedExpansion(cameraPosition, cameraSpeed))
			{
				// In this case, the current Item does not need expansion but his father does
				// Therefore, it is the item we need to retract, we add it on the list
				parentsToRetract->push_back(shared_from_this());

				// Then we recursively browse it's children to register which Items will have to be removed in the childrenToRemove list
				UpdateChildrenToRemove(childrenToRemove);
			}
			else
			{
				// In this case, the parent needs to be retracted also
				// Therefore, recursively go up in the tree
				_parent->UpdateParentToRetract(cameraPosition, cameraSpeed, parentsToRetract, childrenToRemove);
			}
		}
		else
		{
			// In this case, the current Item does not need expansion and does not have a father (root node)
			// Therefore, add it on the list
			parentsToRetract->push_back(shared_from_this());
			UpdateChildrenToRemove(childrenToRemove);
		}
	}


	void Item::UpdateChildrenToRemove(vector<shared_ptr<Item>>* childrenToRemove)
	{
		if (_children.empty())
		{
			// This Item doesn't have any children, therefore is not an extended Item, it exists in the scene and needs to be removed
			childrenToRemove->push_back(shared_from_this());
			_updateChecked = true;
		}
		else
		{
			for each (auto child in _children)
			{
				child->UpdateChildrenToRemove(childrenToRemove);
			}
			// Delete the link to the children since they will be destroyed
			// TODO: remember to also effectively delete the children
			_children.clear();
		}
	}


	void Item::UpdateChildrenToAdd(const Math::Vector3& cameraPosition, const Math::Vector3& cameraSpeed, vector<shared_ptr<Item>>* childrenToAdd)
	{

		if (_subLevelFactory != NULL)
		{

			// If the children have already been calculated, don't do it again.
			if (_children.size() == 0)
			{
				// Fill the children vector with the potential sub levels.
				_subLevelFactory->GenerateLevel(shared_from_this(), 1, Math::Matrix4::Identity(), _worldMatrix, &_children);
			}

			for each (auto child in _children)
			{
				if (child->NeedExpansion(cameraPosition, cameraSpeed))
				{
					// The child needs to be expanded
					// Therefore, we need to add it's children rather than the current child
					child->UpdateChildrenToAdd(cameraPosition, cameraSpeed, childrenToAdd);
				}
				else
				{
					// The child doesn't need to be added
					// Therefore, we need to add only it
					childrenToAdd->push_back(child);
				}
			}
		}
		else
		{
			// If the item has no sub level factory, then it is a leaf, and if we got here it has been chosen to be added
			childrenToAdd->push_back(shared_from_this());
		}
	}

	bool Item::VisibiltyPlanesSatisfied(const Math::Vector3& cameraPosition) const
	{
		if (_worldVisibilityPlanes.size() > 0)
		{
			// If the point needs to be on the "positive" side of all parametric planes.
			if (_visibilityPlanesAndCondition)
			{
				for each (const Math::ParametricPlane& currentPlane in _worldVisibilityPlanes)
				{
					// If the point is on the "negative" side of one plane we can already return false.
					if (!currentPlane.PointOnNormalSide(cameraPosition))
					{
						return false;
					}
				}

				// If no plane returned false, return true.
				return true;
			}
			// If only one parametric plane is enough.
			else
			{
				for each (const Math::ParametricPlane& currentPlane in _worldVisibilityPlanes)
				{
					// If the point is on the "positive" side of one plane we can already return true.
					if (currentPlane.PointOnNormalSide(cameraPosition))
					{
						return true;
					}
				}

				// If no plane returned true, return false.
				return false;
			}
		}
		else
		{
			// If there is no visibility plane condition, we can return true.
			return true;
		}
	}


	bool Item::NeedExpansion(const Math::Vector3& cameraPosition, const Math::Vector3& cameraSpeed) const
	{
		// Test recursively if the parents needs expansion.
		// If a parent needs to retract, this child needs to retract also.
		// This makes sure that the children inherit the visivility planes of their parents.
		// But also that their expansion distance is always inferior to the one of their parents.
		if (_parent != nullptr && !_parent->NeedExpansion(cameraPosition, cameraSpeed))
		{
			return false;
		}

		float distanceToCamera = Math::Vector3::Distance(_worldMatrix.Position(), cameraPosition);

		// If the item is closer than the limit, it needs expansion
		if (distanceToCamera < _expansionDistance)
		{
			return VisibiltyPlanesSatisfied(cameraPosition);
		}

		return false;
	}


	void Item::SetRelativeMatrix(Math::Matrix4 relativeMatrix)
	{
		_relativeMatrix = relativeMatrix;

		if (_parent != nullptr)
		{
			_worldMatrix = Math::Matrix4::Multiply(_parent->GetWorldMatrix(), relativeMatrix);
		}
		else
		{
			_worldMatrix = Math::Matrix4::Multiply(Math::Matrix4::Identity(), relativeMatrix);
		}
		// Update the displayable content's matrix
		if (_displayableContent != nullptr)
		{
			_displayableContent->SetWorldMatrix(_worldMatrix);
		}

		// The parametric planes need to be recomputed.
		ComputeWorldParametricPlanes();
	}

	void Item::SetId(unsigned int id)
	{
		_id = id;
	}

	void Item::ComputeWorldParametricPlanes()
	{
		_worldVisibilityPlanes.clear();

		for (Math::ParametricPlane localSpacePlane : _relavtiveVisibilityPlanes)
		{
			//Math::Vector3 worldNormal = (_worldMatrix.Rotation() * localSpacePlane->GetNormal()).Position(); // TODO: normalize this ? Result shoud be normalized already.
			Math::Vector3 worldNormal = (_worldMatrix.Rotation() * Math::Matrix4::CreateTranslation(localSpacePlane.GetNormal())).Position(); // TODO: normalize this ? Result shoud be normalized already.
			Math::Vector3 worldPoint = (_worldMatrix * (localSpacePlane.GetNormal() * localSpacePlane.GetD())).Position();

			//float worldD = worldPoint.X() / worldNormal.X();
			// Distance from worldPoint to the plane of normal worldNormal and d = 0. Can be negative.
			float worldD = worldNormal.X() * worldPoint.X() + worldNormal.Y() * worldPoint.Y() + worldNormal.Z() * worldPoint.Z();

			Math::ParametricPlane worldSpacePlane = Math::ParametricPlane(worldNormal, worldD);
			_worldVisibilityPlanes.push_back(worldSpacePlane);
		}
	}
}