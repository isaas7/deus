#include "../inc/foo.hpp"
#include "../inc/foobar.hpp"

bool foo() {
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
    return true;
}

bool foobar() {

    Foobar<int> fooInstance(42);
    Barfoo<Foobar, int> barInstance(42);

    barInstance.show();

    return true;
}

int main() {
    return foobar();
}
