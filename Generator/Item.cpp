#include "stdafx.h"
#include "Item.h"

#include <exception>

using std::exception;


namespace Generator
{
	Item::Item()
	{
	}

	Item::Item(Matrix4 relativeMatrix, Item* parent, float expansionDistance, Displayable* displayable, LevelFactory* subLevelFactory)
		: _parent(parent), _expansionDistance(expansionDistance), _displayableContent(displayable), _subLevelFactory(subLevelFactory)
	{
		_children = list<Item*>();

		SetRelativeMatrix(relativeMatrix);
		Vector3 position = _worldMatrix.Position();
		SetId(position.X() + position.Y() + position.Z());

		// Validity testing
		if (parent != NULL)
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

	void Item::UpdateParentToRetract(Vector3 cameraPosition, Vector3 cameraSpeed, list<Item*>* parentsToRetract, list<Item*>* childrenToRemove)
	{
		bool addToList = false;
		bool needExpansion = NeedExpansion(cameraPosition, cameraSpeed);

		if (_parent != NULL)
		{
			if (_parent->NeedExpansion(cameraPosition, cameraSpeed))
			{
				// In this case, the current Item does not need expansion but his father does
				// Therefore, it is the item we need to retract, we add it on the list
				parentsToRetract->push_back(this);

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
			parentsToRetract->push_back(this);
			UpdateChildrenToRemove(childrenToRemove);
		}
	}


	void Item::UpdateChildrenToRemove(list<Item*>* childrenToRemove)
	{
		if (_children.empty())
		{
			// This Item doesn't have any children, therefore is not an extended Item, it exists in the scene and needs to be removed
			childrenToRemove->push_back(this);
			_updateChecked = true;
		}
		else
		{
			for each (Item* child in _children)
			{
				child->UpdateChildrenToRemove(childrenToRemove);
			}
			// Delete the link to the children since they will be destroyed
			// TODO: remember to also effectively delete the children
			_children.clear();
		}
	}


	void Item::UpdateChildrenToAdd(Vector3 cameraPosition, Vector3 cameraSpeed, list<Item*>* childrenToAdd)
	{

		if (_subLevelFactory != NULL)
		{
			_children = _subLevelFactory->GenerateLevel(this, 1, &Matrix4::Identity(), &_worldMatrix);

			for each (Item* child in _children)
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
			childrenToAdd->push_back(this);
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

		if (_parent != NULL)
		{
			_worldMatrix = Matrix4::Multiply(_parent->GetWorldMatrix(), relativeMatrix);
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

	void Item::SetId(int id)
	{

		if (_parent != NULL)
		{
			// TODO: find a better way to generate unique Ids
			_id = _parent->GetId() * (_parent->GetChildrenCount() + 1) + id;
		}
		else
		{
			_id = id;
		}
	}
}