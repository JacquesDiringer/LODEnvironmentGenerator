#pragma once
#include "Displayable.h"
#include "Matrix4.h"

#include <string>

using std::string;

using namespace Math;

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Generator
{
	class GENERATOR_API SimpleObjectDisplayable :
		public Displayable
	{
	public:
		SimpleObjectDisplayable();
		SimpleObjectDisplayable(string modelName, string textureName);
		~SimpleObjectDisplayable();


		// Getters and setters
		string GetModelName() const;
		string GetTextureName() const;

		// Operators
		bool operator==(const SimpleObjectDisplayable &other) const;

	private:
		string _modelName;
		string _textureName;
	};
}