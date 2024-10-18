#include <iostream>
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

// Templated class Foobar
template <typename T>
class Foobar {
public:
    Foobar(T value) : value_(value) {}
    void print() const {
        std::cout << "Foobar value: " << value_ << std::endl;
    }
    void setRootPath(const std::string& rootPath) {
        rootPath_ = rootPath;
        std::cout << "Root path set to: " << rootPath_ << std::endl;
    }
    void generate(int numSrcFiles, int numIncFiles, int numTestFiles) {
        std::cout << "Generating structure with " << numSrcFiles << " source files, " << numIncFiles << " header files, and " << numTestFiles << " test files." << std::endl;
    }
private:
    T value_;
    std::string rootPath_;
};

// Templated template class Barfoo
template <template <typename> class TemplateClass, typename T>
class Barfoo {
public:
    Barfoo(T value) : instance_(value) {}
    void show() const {
        instance_.print();
    }
private:
    TemplateClass<T> instance_;
};

// Templated template class BarFoobar
// Modified to accept template arguments matching the intended template nesting usage
template <template <typename> class OuterTemplateClass, template <typename> class InnerTemplateClass, typename T>
class BarFoobar {
public:
    BarFoobar(T value) : instance_(value) {}
    void display() const {
        instance_.show();
    }
private:
    OuterTemplateClass<InnerTemplateClass<T>> instance_;
};

// Templated template class FoobarBarfoo
// Modified to accept template arguments matching the intended template nesting usage
template <template <typename> class OuterTemplateClass, template <typename> class MiddleTemplateClass, template <typename> class InnerTemplateClass, typename T>
class FoobarBarfoo {
public:
    FoobarBarfoo(T value) : instance_(value) {}
    void output() const {
        instance_.display();
    }
private:
    OuterTemplateClass<MiddleTemplateClass<InnerTemplateClass<T>>> instance_;
};

bool foo() {
    Foobar<int> generator(0);  // Instantiate with int as the template type

    // Print the architecture
    std::cout << "Architecture: " << ARCHITECTURE << std::endl;

    // Configure root path
    std::string rootPath;
    std::cout << "Enter root path: ";
    std::cin >> rootPath;
    generator.setRootPath(rootPath);

    // Input for number of files
    int numSrcFiles, numIncFiles, numTestFiles;
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
    BarFoobar<Barfoo, Foobar, int> barfoobarInstance(42);
    FoobarBarfoo<Barfoo, Barfoo, Foobar, int> foobarbarfooInstance(42);

    barInstance.show();
    barfoobarInstance.display();
    foobarbarfooInstance.output();

    return true;
}

int main() {
    // Uncomment one of the below lines depending on the desired functionality
    //return foo();
    return foobar();
}

