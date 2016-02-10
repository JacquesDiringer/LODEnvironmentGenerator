// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GENERATOR_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// GENERATOR_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

// This class is exported from the Generator.dll
class GENERATOR_API CGenerator {
public:
	CGenerator(void);
	// TODO: add your methods here.
};

extern GENERATOR_API int nGenerator;

GENERATOR_API int fnGenerator(void);
