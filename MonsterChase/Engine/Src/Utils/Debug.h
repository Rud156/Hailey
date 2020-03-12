#pragma once

namespace Utils
{
	class Debug
	{
	private:
		static inline char const* const DebugFilePath = "Debug/Log.txt";

	public:
		static void LogToFile(char const* const i_stringFormat, ...);
		static void LogOutputToWindow(char const* const i_stringFormat, ...);
	};
}
