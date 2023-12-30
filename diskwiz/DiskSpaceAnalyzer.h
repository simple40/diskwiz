#pragma once

#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
//#include <iomanip>
#include <sstream>
#include <Windows.h>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_BOLD		   "\x1b[1m"
#define ANSI_RESET		   "\x1b[0m"
#define ANSI_BLINKING	   "\x1b[5m"

enum class SortOption {
	BY_SIZE,
	BY_DATE,
	BY_NAME,
	DEFAULT
};

enum class ColorAttribute {
	COLOR_RED,
	COLOR_GREEN,
	COLOR_YELLOW,
	RESET
};

enum class TextAttribute {
	BOLD,
	RESET,
	DEFAULT
};

namespace fs = std::filesystem;

class DiskSpaceAnalyzer {
public : 
	void analyze(const std::string& directory, SortOption sortOption);
	uintmax_t traverseDirectory(const std::string& directory, bool isTopLevel);
	void sortAndDisplayResults(SortOption sortOption);

private:
	uintmax_t directorySize;
	struct FileInfo {
		fs::path path;
		uintmax_t size;
		std::string fileName;
	};
	struct SubDirectoryInfo {
		fs::path path;
		uintmax_t size;
		std::string fileName;
	};
	std::vector<FileInfo> files;
	std::vector<SubDirectoryInfo> subDirectories;
	std::string formatFileSize(std::uintmax_t size);
	std::string color_Code(std::uintmax_t size);
	ColorAttribute color_code(std::uintmax_t size);
	void text_format(TextAttribute textAttribute, ColorAttribute colorAttribute);
};