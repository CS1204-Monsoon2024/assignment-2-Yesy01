#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <openssl/sha.h>  // For SHA-256 (ensure OpenSSL is installed)

// Hash functions defined earlier
int simpleModuloHash(int x) {
    return x % 50;
}

int linearCongruentialHash(int x, int a, int b, int p) {
    return ((a * x + b) % p) % 50;
}

int sha256Hash(int x) {
    std::string input = std::to_string(x);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)input.c_str(), input.size(), hash);
    
    int hashValue = 0;
    // Combine the first 4 bytes of the SHA-256 hash into an integer
    for (int i = 0; i < 4; ++i) {
        hashValue = (hashValue << 8) + hash[i];
    }
    return hashValue % 50;
}

// Function to read the CSV file and extract the 'Number of employees' column (9th column)
std::vector<int> readCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<int> employeeCounts;
    
    // Skip the header line
    std::getline(file, line);
    
    // Read each line of the CSV
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        int employeeCount = 0;
        int columnIndex = 0;
        
        // Extract the relevant field (9th column for 'Number of employees')
        while (std::getline(ss, field, ',')) {
            if (columnIndex == 8) {  // If it's the 9th column (index 8)
                try {
                    employeeCount = std::stoi(field);  // Convert to integer
                } catch (const std::invalid_argument& e) {
                    // std::cerr << "Invalid number in 'Number of employees' column: " << field << std::endl;
                    continue;
                }
            }
            columnIndex++;
        }
        employeeCounts.push_back(employeeCount);
    }
    return employeeCounts;
}

int main() {
    // Load the dataset from CSV
    std::vector<int> employeeCounts = readCSV("organizations-1000.csv");

    // Random values for the linear congruential hash function
    int a = 12345, b = 67890;
    int p = 100003; // A large prime number

    // Apply the hash functions to each employee count
    std::cout << "Hash values:\n";
    for (int count : employeeCounts) {
        int hash1 = simpleModuloHash(count);
        int hash2 = linearCongruentialHash(count, a, b, p);
        int hash3 = sha256Hash(count);

        std::cout << "Employees: " << count
                  << " | Simple Modulo Hash: " << hash1
                  << " | Linear Congruential Hash: " << hash2
                  << " | SHA-256 Hash: " << hash3 << std::endl;
    }

    return 0;
}
