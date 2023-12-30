
#include "DiskSpaceAnalyzer.h"
#include <windows.h>
#include <locale>
#include <CLI11.hpp>
#include <codecvt>

void analyzeDirectory(const std::string& directoryPath, bool sortBySize, bool sortByDate, bool sortByName) 
{
    DiskSpaceAnalyzer analyzer;
    if (directoryPath.empty()) {
        //std::cout << "default directory" << std::endl;
        std::string currentPath = std::filesystem::current_path().string();
        std::cout << "Current working directory: " << currentPath << std::endl;

        if (sortBySize) {
            std::cout << "Sorting by Size" << std::endl;
            analyzer.analyze(currentPath, SortOption::BY_SIZE);
        }
        else if (sortByDate) {
            std::cout << "Sorting by Date" << std::endl;
            analyzer.analyze(currentPath, SortOption::BY_DATE);
        }
        else if (sortByName) {
            std::cout << "Sorting by Name" << std::endl;
            analyzer.analyze(currentPath, SortOption::BY_NAME);
        }
        else {
            std::cout << "Default sorting" << std::endl;
            analyzer.analyze(currentPath, SortOption::DEFAULT);
        }
    }
    else if (std::filesystem::exists(directoryPath)) {
        std::cout << "Current working directory: " << directoryPath << std::endl;
        if (sortBySize) {
            std::cout << "Sorting by Size" << std::endl;
            analyzer.analyze(directoryPath, SortOption::BY_SIZE);
        }
        else if (sortByDate) {
            std::cout << "Sorting by Date" << std::endl;
            analyzer.analyze(directoryPath, SortOption::BY_DATE);
        }
        else if (sortByName) {
            std::cout << "Sorting by Name" << std::endl;
            analyzer.analyze(directoryPath, SortOption::BY_NAME);
        }
        else {
            std::cout << "Default sorting" << std::endl;
            analyzer.analyze(directoryPath, SortOption::DEFAULT);
        }
    }
    else {
        std::cout << "directory doesn't exists" << std::endl;
    }

}

int main(int argc, char** argv)
{
    std::locale::global(std::locale("en_US.UTF-8")); //check about this 
    SetConsoleOutputCP(CP_UTF8);
    CLI::App app{ "diskwiz - Master Your Disk with DiskWiz." };

    app.add_flag_function("-v,--version", [](std::int64_t count) {
        std::cout << "diskwiz version 1.0" << std::endl;
        std::exit(0);
        }, "Show version information");

    auto analyze = app.add_subcommand("analyze", "Analyze the directory")->description("Analyze the directory.\nIt contains 3 flags:\n  -s  Sort the result by Size\n  -d  Sort the result by Date\n  -n  Sort the result by Name");
    std::string directoryPath;
    bool sortBySize = false;
    bool sortByDate = false;
    bool sortByName = false;

    auto analyze_options = analyze->add_option_group("analyze options");
    analyze_options->add_flag("-s,--size", sortBySize, "Sort the result by Size")->description("Sort the result by Size");
    analyze_options->add_flag("-d,--date", sortByDate, "Sort the result by Date")->description("Sort the result by Date");
    analyze_options->add_flag("-n,--name", sortByName, "Sort the result by Name")->description("Sort the result by Name");
    analyze_options->require_option(0, 1);
    analyze->add_option("default", directoryPath, "Default sorting");

    analyze->callback([&directoryPath, &sortBySize, &sortByDate, &sortByName, &analyze_options]() {
        if (analyze_options->count("-s") > 1 || analyze_options->count("-d") > 1 || analyze_options->count("--size") > 1 || analyze_options->count("--date") > 1 || analyze_options->count("-n") > 1 || analyze_options->count("--name") > 1) {
            std::cout << "Requires at most 1 options be given from [-s, --size, -d,--date, -n, --name]" << std::endl;
            std::cerr << "Use --help for more information." << std::endl;
            std::exit(EXIT_FAILURE);
        }        
        analyzeDirectory(directoryPath, sortBySize, sortByDate, sortByName);
        });

    try {
        CLI11_PARSE(app, argc, argv);
    }
    catch (const CLI::Error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return app.exit(e);
        std::cout << "error in cli";
    }

    return 0;
}


