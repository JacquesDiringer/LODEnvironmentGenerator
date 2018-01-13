#include "stdafx.h"
#include "YCylinderExpression.h"

namespace Math
{
	YCylinderExpression::YCylinderExpression(float radius, float height)
		: _radius(radius), _height(height)
	{
	}


	YCylinderExpression::~YCylinderExpression()
	{
	}

	float YCylinderExpression::Evaluate(Vector3 coordinates)
	{

		// Check first if we meet the height condition for the current coordinates.
		float halfHeight = _height * 0.5f;
		if (coordinates.Y() >= -halfHeight && coordinates.Y() <= halfHeight)
		{
			// Then check if we meet are in the radius.
			// At the center of the cylinder, value will be _radius.
			// It then linerealy decreases to 0 at the border.
			// Stays 0 out of the cylinder.
			return max(_radius - std::sqrt(std::pow(coordinates.X(), 2) + std::pow(coordinates.Z(), 2)), 0);
		}
	}

}