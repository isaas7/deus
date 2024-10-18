#include <iostream>
#include <filesystem>
#include <random>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <map>
#include <cstdint> // For fixed-width integers

// Macro for stack trace
#define STACK_TRACE std::cerr << "Error at " << __FUNCTION__ << " (Line " << __LINE__ << ")\n"

// Macro for architecture-specific code
#if defined(__arm__) || defined(__aarch64__)
    #define ARCHITECTURE "ARM"
    using int32 = int32_t; // 32-bit integer type
    using int64 = int64_t; // 64-bit integer type
#elif defined(__i386__) || defined(__x86_64__)
    #define ARCHITECTURE "Intel"
    using int32 = int32_t; // 32-bit integer type
    using int64 = int64_t; // 64-bit integer type
#else
    #define ARCHITECTURE "Unknown Architecture"
    using int32 = int32_t; // Fallback to a standard 32-bit type
    using int64 = int64_t; // Fallback to a standard 64-bit type
#endif

namespace fs = std::filesystem;

class FileStructureGenerator {
    private:
        std::map<std::string, std::string> fileConfigs; // Maps filename to content
        std::string rootPath;

        std::string generateRandomName(int length) {
            static const char alphanum[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, sizeof(alphanum) - 2); // -2 to avoid null terminator
            std::string result;
            result.reserve(length);
            for (int32 i = 0; i < length; ++i) { // Use int32 here
                result += alphanum[dis(gen)];
            }
            return result;
        }

        void createDirectory(const fs::path& path) {
            try {
                if (fs::create_directories(path)) {
                    std::cout << "Created directory: " << path << std::endl;
                }
            } catch (const fs::filesystem_error& e) {
                STACK_TRACE;
                std::cerr << "Error creating directory: " << e.what() << std::endl;
            }
        }

        void createFile(const fs::path& path, const std::string& content = "") {
            try {
                std::ofstream file(path);
                if (file.is_open()) {
                    file << content;
                    file.close();
                    std::cout << "Created file: " << path << std::endl;
                } else {
                    STACK_TRACE;
                    std::cerr << "Error opening file: " << path << std::endl;
                }
            } catch (const std::exception& e) {
                STACK_TRACE;
                std::cerr << "Error creating file: " << e.what() << std::endl;
            }
        }

        std::string generateFileContent(const std::string& filename, bool isHeader) {
            std::string content;
            content += "// File: " + filename + "\n";
            content += "// Generated: " + std::string(std::ctime(nullptr));

            if (isHeader) {
                content += "#pragma once\n\n";
                content += "class " + fs::path(filename).stem().string() + " {\n";
                content += "public:\n";
                content += "    // Add your class definition here\n";
                content += "};\n";
            } else {
                content += "// Implementation for " + filename + "\n";
            }

            return content;
        }

    public:
        void setRootPath(const std::string& path) {
            rootPath = path;
        }

        void addFile(const std::string& name, const std::string& content) {
            fileConfigs[name] = content;
        }

        void generate(int numSrcFiles, int numIncFiles, int numTestFiles) {
            // Convert rootPath to std::filesystem::path
            fs::path rootDir = rootPath;

            // Create root directories
            fs::path srcPath = rootDir / "src";
            fs::path incPath = rootDir / "inc";
            fs::path testPath = rootDir / "tests";

            createDirectory(srcPath);
            createDirectory(incPath);
            createDirectory(testPath);

            // Generate source files
            std::vector<std::string> names = {"foo", "bar", "baz", "qux", "quux"};
            for (int32 i = 0; i < numSrcFiles; ++i) { // Use int32 here
                if (i < names.size()) {
                    fs::path filePath = srcPath / (names[i] + ".cpp");
                    createFile(filePath, generateFileContent(names[i], false));
                }
            }

            // Generate header files
            for (int32 i = 0; i < numIncFiles; ++i) { // Use int32 here
                if (i < names.size()) {
                    fs::path filePath = incPath / (names[i] + ".hpp");
                    createFile(filePath, generateFileContent(names[i], true));
                }
            }

            // Generate test files
            for (int32 i = 0; i < numTestFiles; ++i) { // Use int32 here
                if (i < names.size()) {
                    fs::path filePath = testPath / (names[i] + "_test.cpp");
                    createFile(filePath, "// Test for " + names[i] + "\n");
                }
            }
        }

};

int main() {
    FileStructureGenerator generator;

    // Print the architecture
    std::cout << "Architecture: " << ARCHITECTURE << std::endl;

    // Configure root path
    std::string rootPath;
    std::cout << "Enter root path: ";
    std::cin >> rootPath;
    generator.setRootPath(rootPath);

    // Input for number of files
    int32 numSrcFiles, numIncFiles, numTestFiles; // Use int32 for consistency
    std::cout << "Enter number of source files: ";
    std::cin >> numSrcFiles;
    std::cout << "Enter number of header files: ";
    std::cin >> numIncFiles;
    std::cout << "Enter number of test files: ";
    std::cin >> numTestFiles;

    // Generate the structure
    generator.generate(numSrcFiles, numIncFiles, numTestFiles);

    return 0;
}

