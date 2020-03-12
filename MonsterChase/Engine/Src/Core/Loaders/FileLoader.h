#pragma once
#include <string>

namespace Core::Loaders
{
	class FileLoader
	{
	public:
#ifdef NDEBUG
		static inline const char* const Assets = "./Assets";
#else
		static inline const char* const Assets = SOLUTION_DIR;
#endif

		static std::string LoadFileAsString(std::string_view i_filePath);
		static void WriteToFile(std::string_view i_filePath, const char* const i_fileData);
		static bool FileExists(std::string_view i_filePath);
	};
}
