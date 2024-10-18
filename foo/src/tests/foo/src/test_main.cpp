#include "../inc/foo.hpp"

int main() {
    Foo<int32> generator;  // Instantiate with int32 as the template type

    // Print the architecture
    std::cout << "Architecture: " << ARCHITECTURE << std::endl;

    // Configure root path
    std::string rootPath;
    std::cout << "Enter root path: ";
    std::cin >> rootPath;
    generator.setRootPath(rootPath);

    // Input for number of files
    int32 numSrcFiles, numIncFiles, numTestFiles;
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
