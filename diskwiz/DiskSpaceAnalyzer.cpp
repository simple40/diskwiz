#include "DiskSpaceAnalyzer.h"

void DiskSpaceAnalyzer::analyze(const std::string& directory, SortOption sortOption)
{
	directorySize = traverseDirectory(directory, true);
	sortAndDisplayResults(sortOption);
}

uintmax_t DiskSpaceAnalyzer::traverseDirectory(const std::string& directory, bool isTopLevel)
{
	//std::cout << "here we are" << std::endl;
	if (! (fs::exists(directory) && fs::is_directory(directory))) 
	{
		std::cout << "Error : directory " << directory << " doesn't exists" << std::endl;
		return -1;
	}
	uintmax_t directorySize = 0;
	try 
	{
		//std::wcout << "Traversing directory... " << std::endl<<std::endl;

		for (const auto& entry : fs::directory_iterator(directory))
		{
			if (fs::is_regular_file(entry))
			{
				FileInfo fileInfo;
				fileInfo.path = entry.path();
				fileInfo.size = (fs::file_size(entry.path()));
				fileInfo.fileName = entry.path().filename().string();
				if (isTopLevel )
				{
					files.push_back(fileInfo);
				}
				directorySize += fs::file_size(entry.path());
			}
			else if (fs::is_directory(entry)) {
				uintmax_t subDirectorySize = traverseDirectory(entry.path().string(), false);
				directorySize += subDirectorySize;
				if (!isTopLevel) {
					continue;
				}
				SubDirectoryInfo subDirectoryInfo;
				subDirectoryInfo.path = entry.path();
				subDirectoryInfo.size = subDirectorySize;
				subDirectoryInfo.fileName = entry.path().filename().string();
				subDirectories.push_back(subDirectoryInfo);
			}
		}
		return directorySize;
	}
	catch (const std::system_error& e) {
		std::cerr << "Error while traversing the directory: " << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "default exception";
	}
}

void DiskSpaceAnalyzer::sortAndDisplayResults(SortOption sortOption)
{
	try 
	{
		if (sortOption == SortOption::BY_SIZE || sortOption == SortOption::DEFAULT) {
			std::sort(files.begin(), files.end(), [](const FileInfo& a, const FileInfo& b)
				{
					return a.size > b.size;
				});
			std::sort(subDirectories.begin(), subDirectories.end(), [](const SubDirectoryInfo& a, const SubDirectoryInfo& b)
				{
					return a.size > b.size;
				});
		}

		else if (sortOption == SortOption::BY_DATE ) {
			std::sort(files.begin(), files.end(), [](const FileInfo& a, const FileInfo& b)
				{
					std::filesystem::file_time_type timeA = std::filesystem::last_write_time(a.path);
					std::filesystem::file_time_type timeB = std::filesystem::last_write_time(b.path);
					return timeA > timeB;
				});
			std::sort(subDirectories.begin(), subDirectories.end(), [](const SubDirectoryInfo& a, const SubDirectoryInfo& b)
				{
					std::filesystem::file_time_type timeA = std::filesystem::last_write_time(a.path);
					std::filesystem::file_time_type timeB = std::filesystem::last_write_time(b.path);
					return timeA > timeB;
				});
		}
		else if (sortOption == SortOption::BY_NAME) {
			std::sort(files.begin(), files.end(), [](const FileInfo& a, const FileInfo& b)
				{
					return std::lexicographical_compare(a.fileName.begin(), a.fileName.end(),
						b.fileName.begin(), b.fileName.end(),
						[](char c1, char c2) {
							return std::tolower(static_cast<unsigned char>(c1)) < std::tolower(static_cast<unsigned char>(c2));
						});
				});
			std::sort(subDirectories.begin(), subDirectories.end(), [](const SubDirectoryInfo& a, const SubDirectoryInfo& b)
				{
					return std::lexicographical_compare(a.fileName.begin(), a.fileName.end(),
						b.fileName.begin(), b.fileName.end(),
						[](char c1, char c2) {
							return std::tolower(static_cast<unsigned char>(c1)) < std::tolower(static_cast<unsigned char>(c2));
						});
				});
		}

		//std::cout << ANSI_BOLD;

		std::cout << "Directory Size: " << formatFileSize(directorySize) << std::endl << std::endl;
		std::cout << "Files: " << std::endl << std::endl;

		//std::cout << ANSI_RESET;
		
		//these ansi code escapes can be later used to make the cli cross platform
		for (const auto& fileInfo : files)
		{
			//std::string colorCode = color_Code(fileInfo.size);
			ColorAttribute color = color_code(fileInfo.size);

			//std::cout << colorCode;
			text_format(TextAttribute::DEFAULT, color);
			std::cout << "  +-------------------+\n";
			std::cout << "  Name: " << std::setw(15) << std::left << fileInfo.fileName << std::endl;
			//std::cout << ANSI_BOLD;
			text_format(TextAttribute::BOLD, color);
			std::cout << "  Size: " << std::setw(15) << std::left << formatFileSize(fileInfo.size) << std::endl;
			//std::cout << ANSI_RESET;
			std::cout << "  +-------------------+\n"<<std::endl;
			//std::cout << ANSI_COLOR_RESET;
			text_format(TextAttribute::RESET, ColorAttribute::RESET);

		}
		//std::cout << ANSI_BOLD;
		std::cout << "Subdirectories: " << std::endl << std::endl;
		//std::cout << ANSI_RESET;
		for (const auto& subDirectoryInfo : subDirectories)
		{
			//std::string colorCode = color_Code(subDirectoryInfo.size);
			ColorAttribute color = color_code(subDirectoryInfo.size);

			//std::cout << colorCode;
			text_format(TextAttribute::DEFAULT, color);
			std::cout << "  +-------------------+\n";
			std::cout << "  Name: " << std::setw(15) << std::left << subDirectoryInfo.fileName << std::endl;
			text_format(TextAttribute::BOLD, color);
			std::cout << "  Size: " << std::setw(15) << std::left << formatFileSize(subDirectoryInfo.size) << std::endl;
			std::cout << "  +-------------------+\n" << std::endl;
			//std::cout << ANSI_COLOR_RESET;
			text_format(TextAttribute::RESET, ColorAttribute::RESET);
		}
	}
	catch (const std::system_error& e) {
		std::cerr << "Error while sorting and displaying the results: " << e.what() << std::endl;
	}
	
}

std::string DiskSpaceAnalyzer::formatFileSize(std::uintmax_t size)
{
	// Constants for different units
	constexpr std::uintmax_t KB = 1024;
	constexpr std::uintmax_t MB = KB * 1024;
	constexpr std::uintmax_t GB = MB * 1024;
	constexpr std::uintmax_t TB = GB * 1024;

	// Variables to store the unit and converted file size
	std::string unit;
	double fileSize = static_cast<double>(size);

	// Determine the appropriate unit based on the file size
	if (size < KB) {
		unit = "B";
	}
	else if (size < MB) {
		fileSize /= KB;
		unit = "KB";
	}
	else if (size < GB) {
		fileSize /= MB;
		unit = "MB";
	}
	else if (size < TB) {
		fileSize /= GB;
		unit = "GB";
	}
	else {
		fileSize /= TB;
		unit = "TB";
	}

	// Create a string stream for formatting
	std::ostringstream oss;

	// Format the file size with fixed precision and append the unit
	oss << std::fixed << std::setprecision(2) << fileSize << " " << unit;

	// Convert the formatted result to a string and return
	return oss.str();
}

std::string DiskSpaceAnalyzer::color_Code(std::uintmax_t size)
{
	double fileSize = static_cast<double>(size);
	//gives ansi color code according to size
	std::string colorCode = (fileSize / directorySize < 0.1) ? ANSI_COLOR_GREEN : ((fileSize / directorySize < 0.25) ? ANSI_COLOR_YELLOW : ANSI_COLOR_RED);
	return colorCode;
}

ColorAttribute DiskSpaceAnalyzer::color_code(std::uintmax_t size)
{
	double fileSize = static_cast<double>(size);
	ColorAttribute color = (fileSize / directorySize < 0.1) ? ColorAttribute::COLOR_GREEN : ((fileSize / directorySize < 0.25) ? ColorAttribute::COLOR_YELLOW : ColorAttribute::COLOR_RED);
	return color;
}

void DiskSpaceAnalyzer::text_format(TextAttribute textAttribute, ColorAttribute colorAttribute)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (textAttribute == TextAttribute::BOLD) {
		if (colorAttribute == ColorAttribute::COLOR_RED) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
		else if (colorAttribute == ColorAttribute::COLOR_YELLOW) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else if (colorAttribute == ColorAttribute::COLOR_GREEN) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
	}
	else if (colorAttribute == ColorAttribute::COLOR_RED) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	}
	else if (colorAttribute == ColorAttribute::COLOR_YELLOW) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	}
	else if (colorAttribute == ColorAttribute::COLOR_GREEN) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	}
	else if (textAttribute == TextAttribute::RESET) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
}
