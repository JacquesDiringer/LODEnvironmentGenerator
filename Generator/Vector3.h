#pragma once

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif


namespace Math
{
	class GENERATOR_API Vector3
	{
	public:
		Vector3();
		Vector3(float x, float y, float z);
		~Vector3();

		static float Distance(const Vector3 a, const Vector3 b);
		static Vector3 Add(const Vector3 a, const Vector3 b);
		float Length() const;
		Vector3 operator+(const Vector3 b);
		static Vector3 Multiply(const Vector3 a, const Vector3 b);
		Vector3 operator*(const Vector3 b);
		Vector3 operator*(const float multiplier);
		bool operator==(const Vector3 other);
		bool operator<(const Vector3 other) const; // Necessary operator to be able to but Vector3 in a map structure.


		// Properties
		float X() const { return _x; }
		void X(float value) { _x = value; }

		float Y() const { return _y; }
		void Y(float value) { _y = value; }

		float Z() const { return _z; }
		void Z(float value) { _z = value; }

	private:
		float _x, _y, _z;
	};
}