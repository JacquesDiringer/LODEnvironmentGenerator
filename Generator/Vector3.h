#pragma once

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

#include <iomanip>

namespace Math
{
	class GENERATOR_API Vector3
	{
	public:
		Vector3();
		Vector3(float x, float y, float z);
		~Vector3();

		Vector3& Normalize();
		static float Distance(const Vector3& a, const Vector3& b);
		static Vector3 Add(const Vector3& a, const Vector3& b);
		static float Dot(const Vector3& a, const Vector3& b);
		static Vector3 Cross(const Vector3& left, const Vector3& right);
		float Length() const;
		Vector3 operator+(const Vector3& b) const;
		Vector3 operator-(const Vector3& right) const;
		static Vector3 Multiply(const Vector3& a, const Vector3& b);
		Vector3 operator*(const Vector3& b) const;
		Vector3 operator*(const float multiplier) const;
		bool operator==(const Vector3& other) const;
		bool operator<(const Vector3& other) const; // Necessary operator to be able to put Vector3 in a map structure.


		// Properties
		float X() const { return _x; }
		void X(const float value) { _x = value; }

		float Y() const { return _y; }
		void Y(const float value) { _y = value; }

		float Z() const { return _z; }
		void Z(const float value) { _z = value; }

	private:
		float _x, _y, _z;
	};
}

namespace std
{
	template<>
	struct hash<Math::Vector3>
	{
		size_t operator()(const Math::Vector3& vec) const
		{
			using std::hash;

			return (
				hash<float>()(vec.X())
				^ hash<float>()(vec.Y())
				^ hash<float>()(vec.Z())
				);
		}
	};
}