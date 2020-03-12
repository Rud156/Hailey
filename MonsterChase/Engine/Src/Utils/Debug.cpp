#include "Debug.h"

#include <cstdarg>
#include <filesystem>
#include <fstream>
#include <Windows.h>

namespace Utils
{
	void Debug::LogToFile(char const* const i_stringFormat, ...)
	{
#ifdef _DEBUG

		char stringBuffer[2048];
		va_list argList;
		va_start(argList, i_stringFormat);
		_vsnprintf_s(stringBuffer, sizeof(stringBuffer), i_stringFormat, argList);
		va_end(argList);

		const bool fileExists = std::filesystem::exists(Debug::DebugFilePath);
		std::ofstream outFile;
		if (fileExists)
		{
			outFile.open(Debug::DebugFilePath, std::ios_base::app);
		}
		else
		{
			outFile.open(Debug::DebugFilePath, std::ios_base::out);
		}
		outFile << stringBuffer << "\n";
		outFile.close();

#endif
	}

	void Debug::LogOutputToWindow(char const* const i_stringFormat, ...)
	{
#ifdef _DEBUG

		char stringBuffer[2048];
		va_list argList;
		va_start(argList, i_stringFormat);
		_vsnprintf_s(stringBuffer, sizeof(stringBuffer), i_stringFormat, argList);
		va_end(argList);

		OutputDebugStringA(stringBuffer);

#endif
	}
}
