#include "stdafx.h"
#include "SimpleObjectDisplayable.h"


namespace Generator
{
	SimpleObjectDisplayable::SimpleObjectDisplayable()
	{
		_worldMatrix = Matrix4::Identity();
	}


	SimpleObjectDisplayable::SimpleObjectDisplayable(string modelName, string textureName)
		: _modelName(modelName), _textureName(textureName)
	{
		_worldMatrix = Matrix4::Identity();
	}


	SimpleObjectDisplayable::~SimpleObjectDisplayable()
	{
	}

	string SimpleObjectDisplayable::GetModelName() const
	{
		return _modelName;
	}

	string SimpleObjectDisplayable::GetTextureName() const
	{
		return _textureName;
	}

	bool SimpleObjectDisplayable::operator==(SimpleObjectDisplayable const &other) const
	{
		return (
		_modelName == other.GetModelName() &&
		_textureName == other.GetTextureName() &&
		_worldMatrix == other.GetWorldMatrix()
		);
	}

}