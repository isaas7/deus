#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <memory>  // For std::unique_ptr

// Custom Vector class
template <typename T>
class Vector {
private:
    std::unique_ptr<T[]> data;  // Pointer to the data using unique_ptr for automatic cleanup
    size_t capacity;            // Capacity of the vector
    size_t currentSize;         // Current number of elements

    // Function to resize the vector when capacity is reached
    void resize() {
        capacity *= 2;
        std::unique_ptr<T[]> newData = std::make_unique<T[]>(capacity);
        for (size_t i = 0; i < currentSize; ++i) {
            newData[i] = std::move(data[i]);  // Move the data to the new array
        }
        data = std::move(newData);
    }

public:
    // Constructor
    Vector() : capacity(4), currentSize(0) {
        data = std::make_unique<T[]>(capacity);
    }

    // Add an element to the vector
    void push_back(const T& value) {
        if (currentSize == capacity) {
            resize();
        }
        data[currentSize++] = value;
    }

    // Get the number of elements in the vector
    size_t size() const {
        return currentSize;
    }

    // Access element by index
    T& operator[](size_t index) {
        if (index >= currentSize) {
            throw std::out_of_range("Index out of range.");
        }
        return data[index];
    }

    // Access element by index (const version)
    const T& operator[](size_t index) const {
        if (index >= currentSize) {
            throw std::out_of_range("Index out of range.");
        }
        return data[index];
    }
};

// NDArray Class
template <typename T>
class NDArray {
private:
    Vector<size_t> dimensions;  // Dimensions of the n-dimensional array
    Vector<T> data;             // Flattened data storage

    // Helper function to calculate index in the flattened array
    size_t calculateIndex(const Vector<size_t>& indices) const {
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
    // Default constructor
    NDArray() = default;

    // Constructor to initialize the array with given dimensions
    NDArray(const std::initializer_list<size_t>& dims) {
        for (auto dim : dims) {
            dimensions.push_back(dim);
        }

        size_t totalSize = 1;
        for (size_t i = 0; i < dimensions.size(); ++i) {
            totalSize *= dimensions[i];
        }
        for (size_t i = 0; i < totalSize; ++i) {
            data.push_back(T());  // Initialize all elements to default value of T
        }
    }

    // Function to set a value at specific indices
    void setValue(const Vector<size_t>& indices, const T& value) {
        data[calculateIndex(indices)] = value;
    }

    // Function to get a value at specific indices
    T getValue(const Vector<size_t>& indices) const {
        return data[calculateIndex(indices)];
    }

    // Function to get the size of the n-dimensional array
    size_t size() const {
        return data.size();
    }

    // Function to print the data (for debugging purposes)
    void print() const {
        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

// NDArrayManager Class
template <typename T>
class NDArrayManager {
private:
    Vector<NDArray<T>> arrays;

public:
    // Constructor to initialize x NDArray instances with given dimensions
    NDArrayManager(size_t x, const std::initializer_list<size_t>& dims) {
        for (size_t i = 0; i < x; ++i) {
            arrays.push_back(NDArray<T>(dims));
        }
    }

    // Access individual NDArray by index
    NDArray<T>& getArray(size_t index) {
        if (index >= arrays.size()) {
            throw std::out_of_range("Index out of range for array manager.");
        }
        return arrays[index];
    }

    // Print all arrays (for debugging purposes)
    void printAll() const {
        for (size_t i = 0; i < arrays.size(); ++i) {
            std::cout << "Array " << i + 1 << ": ";
            arrays[i].print();
        }
    }
};

// Main function
int main() {
    size_t x = 3;  // Number of NDArray instances you want to create

    // Define dimensions for each NDArray instance (3x3x3 in this case)
    std::initializer_list<size_t> dims = {3, 3, 3};

    // Create an NDArrayManager with x NDArrays
    NDArrayManager<int> manager(x, dims);

    // Set and get values for demonstration
    for (size_t i = 0; i < x; ++i) {
        // Create indices vector
        Vector<size_t> indices;
        indices.push_back(1);
        indices.push_back(1);
        indices.push_back(1);

        // Set a value in each NDArray
        manager.getArray(i).setValue(indices, static_cast<int>(i + 1) * 10);

        // Print value from each NDArray
        std::cout << "Value at (1,1,1) in NDArray " << i + 1 << ": " 
                  << manager.getArray(i).getValue(indices) << std::endl;
    }

    // Print all arrays
    manager.printAll();

    return 0;
}
