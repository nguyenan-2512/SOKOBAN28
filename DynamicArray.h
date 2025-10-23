#pragma once
template<typename T>
class DynamicArray {
private:
    T* data;
    int capacity;
    int size;

    void resize() {
        this->capacity = (this->capacity == 0) ? 1 : this->capacity * 2;
        T* newData = new T[this->capacity];
        for (int i = 0; i < this->size; i++) {
            newData[i] = this->data[i];
        }
        delete[] this->data;
        this->data = newData;
    }

public:
    DynamicArray() : data(nullptr), capacity(0), size(0) {}

    ~DynamicArray() {
        delete[] this->data;
    }

    // Copy constructor
    DynamicArray(const DynamicArray& other)
        : capacity(other.capacity), size(other.size) {
        this->data = new T[this->capacity];
        for (int i = 0; i < this->size; i++) {
            this->data[i] = other.data[i];
        }
    }

    // Assignment operator
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] this->data;
            this->capacity = other.capacity;
            this->size = other.size;
            this->data = new T[this->capacity];
            for (int i = 0; i < this->size; i++) {
                this->data[i] = other.data[i];
            }
        }
        return *this;
    }

    void push_back(const T& value) {
        if (this->size >= this->capacity) {
            this->resize();
        }
        this->data[this->size++] = value;
    }

    T& operator[](int index) {
        return this->data[index];
    }

    const T& operator[](int index) const {
        return this->data[index];
    }

    int getSize() const {
        return this->size;
    }

    bool empty() const {
        return this->size == 0;
    }

    void clear() {
        this->size = 0;
    }

    // Iterator support (cơ bản)
    T* begin() { return this->data; }
    T* end() { return this->data + this->size; }
    const T* begin() const { return this->data; }
    const T* end() const { return this->data + this->size; }
};
