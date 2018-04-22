#pragma once

#include "Matrix4.h"

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Generator
{
	class GENERATOR_API Displayable
	{
	public:
		virtual ~Displayable();

		Math::Matrix4 GetWorldMatrix() const { return _worldMatrix; }
		void SetWorldMatrix(Math::Matrix4 value) { _worldMatrix = value; }

		inline bool operator==(const Displayable& right) { return this->GetWorldMatrix() == right.GetWorldMatrix(); }
		inline bool operator==(const Displayable* right) { return this->GetWorldMatrix() == right->GetWorldMatrix(); }


	protected:
		Math::Matrix4 _worldMatrix;
	};
}
