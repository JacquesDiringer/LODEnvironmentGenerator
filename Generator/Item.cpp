#include "stdafx.h"
#include "Item.h"

#include <exception>

using std::exception;


namespace Generator
{
	Item::Item()
	{
	}

	Item::Item(Matrix4 relativeMatrix, weak_ptr<Item> parent, float expansionDistance, Displayable* displayable, LevelFactory* subLevelFactory)
		: _parent(parent), _expansionDistance(expansionDistance), _displayableContent(displayable), _subLevelFactory(subLevelFactory)
	{
		_children = vector<shared_ptr<Item>>();

		SetRelativeMatrix(relativeMatrix);
		Vector3 position = _worldMatrix.Position();
		SetId(std::hash<Matrix4>()(_worldMatrix));

		shared_ptr<Item> sharedParent = parent.lock();

		// Validity testing
		if (sharedParent != nullptr)
		{
			if (_expansionDistance >= sharedParent->GetExpansionDistance())
			{
				throw new exception("The created item expansion distance should be strictly inferior to the expansion distance of it's parent");
			}
		}
	}


	Item::~Item()
	{
	}

	void Item::UpdateParentToRetract(Vector3 cameraPosition, Vector3 cameraSpeed, vector<shared_ptr<Item>>* parentsToRetract, vector<shared_ptr<Item>>* childrenToRemove)
	{
		bool addToList = false;
		bool needExpansion = NeedExpansion(cameraPosition, cameraSpeed);

		// Get a shared pointer to the parent.
		shared_ptr<Item> sharedParent = _parent.lock();

		if (sharedParent != nullptr)
		{
			if (sharedParent->NeedExpansion(cameraPosition, cameraSpeed))
			{
				// In this case, the current Item does not need expansion but his father does
				// Therefore, it is the item we need to retract, we add it on the list
				parentsToRetract->push_back(shared_ptr<Item>(this));

				// Then we recursively browse it's children to register which Items will have to be removed in the childrenToRemove list
				UpdateChildrenToRemove(childrenToRemove);
			}
			else
			{
				// In this case, the parent needs to be retracted also
				// Therefore, recursively go up in the tree
				sharedParent->UpdateParentToRetract(cameraPosition, cameraSpeed, parentsToRetract, childrenToRemove);
			}
		}
		else
		{
			// In this case, the current Item does not need expansion and does not have a father (root node)
			// Therefore, add it on the list
			parentsToRetract->push_back(shared_ptr<Item>(this));
			UpdateChildrenToRemove(childrenToRemove);
		}
	}


	void Item::UpdateChildrenToRemove(vector<shared_ptr<Item>>* childrenToRemove)
	{
		if (_children.empty())
		{
			// This Item doesn't have any children, therefore is not an extended Item, it exists in the scene and needs to be removed
			childrenToRemove->push_back(shared_ptr<Item>(this));
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


	void Item::UpdateChildrenToAdd(Vector3 cameraPosition, Vector3 cameraSpeed, vector<shared_ptr<Item>>* childrenToAdd)
	{

		if (_subLevelFactory != NULL)
		{

			// If the children have already been calculated, don't do it again.
			if (_children.size() == 0)
			{
				// Fill the children vector with the potential sub levels.
				_subLevelFactory->GenerateLevel(shared_from_this(), 1, &Matrix4::Identity(), &_worldMatrix, &_children);
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


	bool Item::NeedExpansion(Vector3 cameraPosition, Vector3 cameraSpeed)
	{
		float distanceToCamera = Vector3::Distance(_worldMatrix.Position(), cameraPosition);

		// If the item is closer than the limit, it needs expansion
		return distanceToCamera < _expansionDistance;
	}


	void Item::SetRelativeMatrix(Matrix4 relativeMatrix)
	{
		_relativeMatrix = relativeMatrix;

		// Get a shared pointer to the parent.
		shared_ptr<Item> sharedParent = _parent.lock();

		if (sharedParent != nullptr)
		{
			_worldMatrix = Matrix4::Multiply(sharedParent->GetWorldMatrix(), relativeMatrix);
		}
		else
		{
			_worldMatrix = Matrix4::Multiply(Matrix4::Identity(), relativeMatrix);
		}
		// Update the displayable content's matrix
		if (_displayableContent != NULL)
		{
			_displayableContent->SetWorldMatrix(_worldMatrix);
		}
	}

	void Item::SetId(unsigned int id)
	{
		_id = id;
	}
}