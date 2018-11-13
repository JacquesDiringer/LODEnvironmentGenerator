#pragma once

#include "Vector3.h"
#include "Quaternion.h"

#include <iomanip>

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Math
{
	/// This class describes 4x4 translation, rotation, scale matrices
	class GENERATOR_API Matrix4
	{
	public:
		Matrix4();
		Matrix4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);
		Matrix4(const Vector3& position);
		~Matrix4();

		static Matrix4 Identity();
		static Matrix4 Multiply(const Matrix4& a, const Matrix4& b);
		Matrix4 operator* (const Matrix4& b) const;
		size_t GetHash() const;
		static Vector3 Multiply(const Matrix4& a, const Vector3& position);

		static Matrix4 CreateTranslation(const Vector3& translation);
		static Matrix4 CreateRotationY(float angle); // angle in degrees

		// Interface
		Vector3 Position() const;
		Quaternion ComputeQuaternion();
		Matrix4 Rotation() const;

		// Operators
		bool operator== (const Matrix4 &other) const;


	private:
		float _m00, _m01, _m02, _m03;
		float _m10, _m11, _m12, _m13;
		float _m20, _m21, _m22, _m23;
		float _m30, _m31, _m32, _m33;

		friend class Matrix4;
	};
}

namespace std
{
	template<>
	struct hash<Math::Matrix4>
	{
		size_t operator()(const Math::Matrix4& mat) const
		{
			using std::hash;

			return mat.GetHash();
		}
	};
}