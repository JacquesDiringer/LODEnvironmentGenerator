#include "stdafx.h"
#include "AABExpression.h"


namespace Math
{
	AABExpression::AABExpression()
	{
	}

	AABExpression::AABExpression(Vector3 boxOrigin, Vector3 boxDimensions, bool centered)
		: _boxOrigin(boxOrigin), _boxDimensions(boxDimensions), _centered(centered)
	{
		// Void
	}

	AABExpression::~AABExpression()
	{
	}

	float AABExpression::Evaluate(Vector3 coordinates)
	{
		bool result = true;

		if (_centered)
		{
			result &= coordinates.X() > _boxOrigin.X() - 0.5f * _boxDimensions.X();
			result &= coordinates.X() < _boxOrigin.X() + 0.5f * _boxDimensions.X();

			result &= coordinates.Y() > _boxOrigin.Y() - 0.5f * _boxDimensions.Y();
			result &= coordinates.Y() < _boxOrigin.Y() + 0.5f * _boxDimensions.Y();

			result &= coordinates.Z() > _boxOrigin.Z() - 0.5f * _boxDimensions.Z();
			result &= coordinates.Z() < _boxOrigin.Z() + 0.5f * _boxDimensions.Z();
		}
		else
		{
			result &= coordinates.X() > _boxOrigin.X();
			result &= coordinates.X() < _boxOrigin.X() + _boxDimensions.X();

			result &= coordinates.Y() > _boxOrigin.Y();
			result &= coordinates.Y() < _boxOrigin.Y() + _boxDimensions.Y();

			result &= coordinates.Z() > _boxOrigin.Z();
			result &= coordinates.Z() < _boxOrigin.Z() + _boxDimensions.Z();
		}

		return result ? 1 : 0;
	}
}