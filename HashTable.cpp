#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;  // Hash table to store values
    int currentSize;         // Current number of elements
    int capacity;            // Current capacity of the hash table
    float loadFactorThreshold = 0.8; // Load factor threshold for resizing

    // Helper function to check if a number is prime
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    // Helper function to find the next prime number greater than or equal to n
    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    // Hash function: h(k) = k mod m
    int hashFunction(int key) {
        return key % capacity;
    }

    // Resize and rehash the table
    void resizeTable() {
        int newCapacity = nextPrime(capacity * 2); // Resize to next prime number
        std::vector<int> oldTable = table; // Keep the old table

        // Initialize a new table with new capacity
        table.assign(newCapacity, -1); // -1 indicates empty slots
        currentSize = 0; // Reset current size
        capacity = newCapacity; // Update capacity

        // Rehash all elements from the old table
        for (int key : oldTable) {
            if (key != -1) {
                insert(key); // Reinsert elements into the new table
            }
        }
    }

public:
    // Constructor to initialize the hash table with the initial size
    HashTable(int size = 7) {
        capacity = nextPrime(size); // Ensure initial size is prime
        table.assign(capacity, -1); // Initialize all slots to -1 (empty)
        currentSize = 0;
    }

    // Insert a key into the hash table
    void insert(int key) {
        if (currentSize >= capacity * loadFactorThreshold) {
            resizeTable(); // Resize if load factor exceeds threshold
        }

        int index = hashFunction(key);
        int i = 0;

        // Quadratic probing: h(k) + i^2 mod m
        while (i < (capacity + 1) / 2) {
            int newIndex = (index + i * i) % capacity;

            if (table[newIndex] == -1) { // Empty slot found
                table[newIndex] = key;
                currentSize++;
                return;
            } else if (table[newIndex] == key) {
                std::cout << "Duplicate key insertion is not allowed" << std::endl;
                return;
            }

            i++;
        }

        // If probing exceeds max allowed probes
        std::cout << "Max probing limit reached!" << std::endl;
    }

    // Remove a key from the hash table
    void remove(int key) {
        int index = hashFunction(key);
        int i = 0;

        while (i < (capacity + 1) / 2) {
            int newIndex = (index + i * i) % capacity;

            if (table[newIndex] == key) {
                table[newIndex] = -1; // Mark slot as empty
                currentSize--;
                return;
            } else if (table[newIndex] == -1) { // If an empty slot is found, stop searching
                std::cout << "Element not found" << std::endl;
                return;
            }

            i++;
        }

        std::cout << "Element not found" << std::endl;
    }

    // Search for a key in the hash table and return its index
    int search(int key) {
        int index = hashFunction(key);
        int i = 0;

        while (i < (capacity + 1) / 2) {
            int newIndex = (index + i * i) % capacity;

            if (table[newIndex] == key) {
                return newIndex; // Key found
            } else if (table[newIndex] == -1) { // Stop if an empty slot is found
                return -1;
            }

            i++;
        }

        return -1; // Key not found
    }

    // Print the current state of the hash table
    void printTable() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] == -1) {
                std::cout << "- ";
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};
