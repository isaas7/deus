#include <iostream>

// Templated class Foobar
template <typename T>
class Foobar {
public:
    Foobar(T value) : value_(value) {}
    void print() const {
        std::cout << "Foobar value: " << value_ << std::endl;
    }
private:
    T value_;
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

