#include "FileLoader.h"

#include <fstream>
#include <filesystem>

// Define static data here to create instance...
std::mutex Core::Loaders::FileLoader::FileMutex;

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
		FileMutex.lock(); // Only lock the file when writing to it. Reading can be async...

		std::ofstream outFile;
		outFile.open(i_filePath, std::ios_base::out);
		outFile << i_fileData;
		outFile.close();

		FileMutex.unlock();
	}

	bool FileLoader::FileExists(std::string_view i_filePath)
	{
		return std::filesystem::exists(i_filePath);
	}
}
