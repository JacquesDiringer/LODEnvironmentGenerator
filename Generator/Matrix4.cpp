#include "stdafx.h"
#include "Matrix4.h"

#define M_PI 3.14159265358979323846
#include <cmath>

namespace Math
{
	Matrix4::Matrix4()
	{
		_m00 = 1; _m01 = 0; _m02 = 0; _m03 = 0;
		_m10 = 0; _m11 = 1; _m12 = 0; _m13 = 0;
		_m20 = 0; _m21 = 0; _m22 = 1; _m23 = 0;
		_m30 = 0; _m31 = 0; _m32 = 0; _m33 = 1;
	}

	Matrix4::Matrix4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
	{
		_m00 = m00; _m01 = m01; _m02 = m02; _m03 = m03;
		_m10 = m10; _m11 = m11; _m12 = m12; _m13 = m13;
		_m20 = m20; _m21 = m21; _m22 = m22; _m23 = m23;
		_m30 = m30; _m31 = m31; _m32 = m32; _m33 = m33;
	}

	Matrix4::~Matrix4()
	{
	}

	Matrix4 Matrix4::Identity()
	{
		return Matrix4();
	}

	Vector3 Matrix4::Position()
	{
		return Vector3(_m03, _m13, _m23);
	}

	Matrix4 Matrix4::Multiply(Matrix4 a, Matrix4 b)
	{
		float m00 = a._m00*b._m00 + a._m01*b._m10 + a._m02*b._m20 + a._m03*b._m30;
		float m01 = a._m00*b._m01 + a._m01*b._m11 + a._m02*b._m21 + a._m03*b._m31;
		float m02 = a._m00*b._m02 + a._m01*b._m12 + a._m02*b._m22 + a._m03*b._m32;
		float m03 = a._m00*b._m03 + a._m01*b._m13 + a._m02*b._m23 + a._m03*b._m33;

		float m10 = a._m10*b._m00 + a._m11*b._m10 + a._m12*b._m20 + a._m13*b._m30;
		float m11 = a._m10*b._m01 + a._m11*b._m11 + a._m12*b._m21 + a._m13*b._m31;
		float m12 = a._m10*b._m02 + a._m11*b._m12 + a._m12*b._m22 + a._m13*b._m32;
		float m13 = a._m10*b._m03 + a._m11*b._m13 + a._m12*b._m23 + a._m13*b._m33;

		float m20 = a._m20*b._m00 + a._m21*b._m10 + a._m22*b._m20 + a._m23*b._m30;
		float m21 = a._m20*b._m01 + a._m21*b._m11 + a._m22*b._m21 + a._m23*b._m31;
		float m22 = a._m20*b._m02 + a._m21*b._m12 + a._m22*b._m22 + a._m23*b._m32;
		float m23 = a._m20*b._m03 + a._m21*b._m13 + a._m22*b._m23 + a._m23*b._m33;

		float m30 = a._m30*b._m00 + a._m31*b._m10 + a._m32*b._m20 + a._m33*b._m30;
		float m31 = a._m30*b._m01 + a._m31*b._m11 + a._m32*b._m21 + a._m33*b._m31;
		float m32 = a._m30*b._m02 + a._m31*b._m12 + a._m32*b._m22 + a._m33*b._m32;
		float m33 = a._m30*b._m03 + a._m31*b._m13 + a._m32*b._m23 + a._m33*b._m33;

		return Matrix4(	m00, m01, m02, m03,
						m10, m11, m12, m13,
						m20, m21, m22, m23,
						m30, m31, m32, m33);
	}

	Matrix4 Matrix4::CreateTranslation(Vector3 translation)
	{
		return Matrix4(translation);
	}

	Matrix4 Matrix4::CreateRotationY(float angle)
	{
		float rad = angle * M_PI / 180.0f;
		float cosinus = cos(rad);
		float sinus = sin(rad);

		return Matrix4(	cosinus,	0,	 sinus,	0,
						0,			1,	0,		0,
						-sinus,		0,	cosinus,0,
						0,			0,	0,		1);
	}

	Matrix4::Matrix4(Vector3 position)
	{
		_m00 = 1; _m01 = 0; _m02 = 0; _m03 = position.X();
		_m10 = 0; _m11 = 1; _m12 = 0; _m13 = position.Y();
		_m20 = 0; _m21 = 0; _m22 = 1; _m23 = position.Z();
		_m30 = 0; _m31 = 0; _m32 = 0; _m33 = 1;

	}

	Quaternion Matrix4::ComputeQuaternion()
	{
		float x, y, z, w;

		float tr = _m00 + _m11 + _m22;

		if (tr > 0)
		{
			float S = sqrt(tr + 1.0f) * 2; // S=4*qw 
			w = 0.25f * S;
			x = (_m21 - _m12) / S;
			y = (_m02 - _m20) / S;
			z = (_m10 - _m01) / S;
		}
		else if ((_m00 > _m11)&(_m00 > _m22)) {
			float S = sqrt(1.0f + _m00 - _m11 - _m22) * 2; // S=4*qx 
			w = (_m21 - _m12) / S;
			x = 0.25f * S;
			y = (_m01 + _m10) / S;
			z = (_m02 + _m20) / S;
		}
		else if (_m11 > _m22) {
			float S = sqrt(1.0f + _m11 - _m00 - _m22) * 2; // S=4*qy
			w = (_m02 - _m20) / S;
			x = (_m01 + _m10) / S;
			y = 0.25f * S;
			z = (_m12 + _m21) / S;
		}
		else {
			float S = sqrt(1.0f + _m22 - _m00 - _m11) * 2; // S=4*qz
			w = (_m10 - _m01) / S;
			x = (_m02 + _m20) / S;
			y = (_m12 + _m21) / S;
			z = 0.25f * S;
		}

		return Quaternion(x, y, z, w);
	}

	bool Matrix4::operator== (Matrix4 const &other) const
	{
		return (
			_m00 == other._m00 &&
			_m01 == other._m01 &&
			_m02 == other._m02 &&
			_m03 == other._m03 &&

			_m10 == other._m10 &&
			_m11 == other._m11 &&
			_m12 == other._m12 &&
			_m13 == other._m13 &&

			_m20 == other._m20 &&
			_m21 == other._m21 &&
			_m22 == other._m22 &&
			_m23 == other._m23 &&

			_m30 == other._m30 &&
			_m31 == other._m31 &&
			_m32 == other._m32 &&
			_m33 == other._m33
			);
	}
}