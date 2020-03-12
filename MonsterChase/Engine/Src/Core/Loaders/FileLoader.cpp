#include "FileLoader.h"

#include <fstream>
#include <filesystem>

namespace Core::Loaders
{
	// Don't use very large files with this
	std::string FileLoader::LoadFileAsString(std::string_view i_filePath)
	{
		std::ifstream file(i_filePath, std::ios_base::in);
		std::string fileData(
			(std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>()
		);

		return fileData;
	}

	void FileLoader::WriteToFile(std::string_view i_filePath, const char* const i_fileData)
	{
		std::ofstream outFile;
		outFile.open(i_filePath, std::ios_base::out);
		outFile << i_fileData;
		outFile.close();
	}

	bool FileLoader::FileExists(std::string_view i_filePath)
	{
		return std::filesystem::exists(i_filePath);
	}
}
