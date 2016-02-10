#include "stdafx.h"
#include "Quaternion.h"


namespace Math
{
	Quaternion::Quaternion()
	{
	}


	Quaternion::~Quaternion()
	{
	}

	Quaternion::Quaternion(float x, float y, float z, float w)
		: _x(x), _y(y), _z(z), _w(w)
	{
		// Void
	}
}