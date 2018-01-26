#include "stdafx.h"
#include "SimpleObjectDisplayable.h"


namespace Generator
{
	SimpleObjectDisplayable::SimpleObjectDisplayable(const SimpleObjectDisplayable * successor)
		: _successor(successor)
	{
		_worldMatrix = Matrix4::Identity();
	}

	SimpleObjectDisplayable::SimpleObjectDisplayable(string modelName, string textureName)
		: _successor(nullptr), _modelName(modelName), _textureName(textureName)
	{
		_worldMatrix = Matrix4::Identity();
	}


	SimpleObjectDisplayable::~SimpleObjectDisplayable()
	{
	}

	const string& SimpleObjectDisplayable::GetModelName() const
	{
		return _successor != nullptr ? _successor->GetModelName() : _modelName;
	}

	const string& SimpleObjectDisplayable::GetTextureName() const
	{
		return _successor != nullptr ? _successor->GetTextureName() : _textureName;
	}

	bool SimpleObjectDisplayable::operator==(SimpleObjectDisplayable const &other) const
	{
		return (
		this->GetModelName() == other.GetModelName() &&
		this->GetTextureName() == other.GetTextureName() &&
		this->GetWorldMatrix() == other.GetWorldMatrix()
		);
	}

}