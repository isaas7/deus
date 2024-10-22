#include <iostream>
#include <tuple>
#include <string>
#include <utility>

// Templated class Foobar
template <typename T>
class Foobar {
public:
    Foobar(T value) : value_(value) {}
    void print() const {
        std::cout << "Foobar value: " << static_cast<typename std::decay<decltype(value_)>::type>(value_) << std::endl;
    }
private:
    T value_;
};

// Parameterized Template Nesting Class
// Accepts a list of template classes and nests them based on the number of nested levels specified
template <typename T, template <typename> class... Templates>
class NestedTemplates;

// Base case: single template class
template <typename T, template <typename> class SingleTemplate>
class NestedTemplates<T, SingleTemplate> {
public:
    NestedTemplates(T value) : instance_(value) {}
    void print() const {
        instance_.print();
    }
private:
    SingleTemplate<T> instance_;
};

// Recursive case: multiple template classes
template <typename T, template <typename> class First, template <typename> class... Rest>
class NestedTemplates<T, First, Rest...> {
public:
    NestedTemplates(T value) : instance_(value) {}
    void print() const {
        instance_.print();
    }
private:
    First<NestedTemplates<T, Rest...>> instance_;
};

bool foobar() {
    // Instantiate nested template classes based on combinations of Foobar and nesting levels
    NestedTemplates<int, Foobar> fooInstance(42);
    NestedTemplates<int, Foobar, Foobar> doubleFooInstance(42);
    NestedTemplates<int, Foobar, Foobar, Foobar> tripleFooInstance(42);

    fooInstance.print();
    doubleFooInstance.print();
    tripleFooInstance.print();

    return true;
}

int main() {
    return foobar();
}

