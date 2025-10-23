#pragma once
template<typename Key, typename Value, typename Hash>
class HashTable {
private:
    struct Node {
        Key key;
        Value value;
        Node* next;

        Node(const Key& k, const Value& v) : key(k), value(v), next(nullptr) {}
    };

    Node** table;
    int capacity;
    int size;
    Hash hashFunction;

    int getIndex(const Key& key) const {
        return hashFunction(key) % capacity;
    }

    void resize() {
        int oldCapacity = capacity;
        Node** oldTable = table;

        capacity *= 2;
        table = new Node * [capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
        size = 0;

        // Rehash tất cả các node
        for (int i = 0; i < oldCapacity; i++) {
            Node* current = oldTable[i];
            while (current) {
                insert(current->key, current->value);
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] oldTable;
    }

public:
    HashTable(int initialCapacity = 16) : capacity(initialCapacity), size(0) {
        table = new Node * [capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        clear();
        delete[] table;
    }

    void insert(const Key& key, const Value& value) {
        if (size >= capacity * 0.75) {
            resize();
        }

        int index = getIndex(key);
        Node* current = table[index];

        // Kiểm tra key đã tồn tại chưa
        while (current) {
            if (current->key == key) {
				current->value = value; //nếu trùng key thì cập nhật giá trị value của key đó
                return;
            }
            current = current->next;
        }

        // Thêm mới
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        size++;
    }

    bool find(const Key& key, Value& result) const {
        int index = getIndex(key);
        Node* current = table[index];

        while (current) {
            if (current->key == key) {
                result = current->value;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool contains(const Key& key) const {
        int index = getIndex(key);
        Node* current = table[index];

        while (current) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    Value& operator[](const Key& key) {
        int index = getIndex(key);
        Node* current = table[index];

        while (current) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }

        // Nếu không tìm thấy, tạo mới
        Node* newNode = new Node(key, Value());
        newNode->next = table[index];
        table[index] = newNode;
        size++;
        return newNode->value;
    }

    void clear() {
        for (int i = 0; i < capacity; i++) {
            Node* current = table[i];
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            table[i] = nullptr;
        }
        size = 0;
    }

    int getSize() const {
        return size;
    }

     Iterator support (đơn giản)
    class Iterator {
    private:
        HashTable* ht;
        int bucketIndex;
        Node* current;

        void advance() {
            if (current && current->next) {
                current = current->next;
                return;
            }

            bucketIndex++;
            while (bucketIndex < ht->capacity) {
                if (ht->table[bucketIndex]) {
                    current = ht->table[bucketIndex];
                    return;
                }
                bucketIndex++;
            }
            current = nullptr;
        }

    public:
        Iterator(HashTable* h, int bucket, Node* node)
            : ht(h), bucketIndex(bucket), current(node) {
        }

        Iterator& operator++() {
            advance();
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        Node* operator->() { return current; }
        Node& operator*() { return *current; }
    };

    Iterator begin() {
        for (int i = 0; i < capacity; i++) {
            if (table[i]) {
                return Iterator(this, i, table[i]);
            }
        }
        return end();
    }

    Iterator end() {
        return Iterator(this, capacity, nullptr);
    }
};

