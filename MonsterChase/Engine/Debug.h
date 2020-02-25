#pragma once

namespace Utils
{
	class Debug
	{
	private:
		static char const* const DebugFilePath;

	public:
		static void LogToFile(char const* const i_stringFormat, ...);
		static void LogOutputToWindow(char const* const i_stringFormat, ...);
	};
}
