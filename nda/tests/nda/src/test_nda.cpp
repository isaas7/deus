#include <iostream>
#include <vector>
#include <stdexcept>
#include <initializer_list>

template <typename T>
class NDArray {
private:
    std::vector<size_t> dimensions;  // Dimensions of the n-dimensional array
    std::vector<T> data;             // Flattened data storage

    // Helper function to calculate index in the flattened array
    size_t calculateIndex(const std::vector<size_t>& indices) const {
        if (indices.size() != dimensions.size()) {
            throw std::out_of_range("Incorrect number of indices.");
        }

        size_t index = 0;
        size_t offset = 1;
        for (int i = dimensions.size() - 1; i >= 0; --i) {
            if (indices[i] >= dimensions[i]) {
                throw std::out_of_range("Index out of range.");
            }
            index += indices[i] * offset;
            offset *= dimensions[i];
        }
        return index;
    }

public:
    // Constructor to initialize the array with given dimensions
    NDArray(const std::initializer_list<size_t>& dims) : dimensions(dims) {
        size_t totalSize = 1;
        for (auto dim : dimensions) {
            totalSize *= dim;
        }
        data.resize(totalSize);
    }

    // Function to set a value at specific indices
    void setValue(const std::vector<size_t>& indices, const T& value) {
        data[calculateIndex(indices)] = value;
    }

    // Function to get a value at specific indices
    T getValue(const std::vector<size_t>& indices) const {
        return data[calculateIndex(indices)];
    }

    // Function to get the size of the n-dimensional array
    size_t size() const {
        return data.size();
    }

    // Function to print the data (for debugging purposes)
    void print() const {
        for (const auto& val : data) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    // Create a 3x3x3 NDArray
    NDArray<int> array({3, 3, 3});

    // Set a value at position (1,1,1)
    array.setValue({1, 1, 1}, 42);

    // Get a value from position (1,1,1)
    std::cout << "Value at (1,1,1): " << array.getValue({1, 1, 1}) << std::endl;

    // Print the entire flattened array
    array.print();

    return 0;
}

