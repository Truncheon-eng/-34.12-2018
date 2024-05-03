#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

int main() {
    std::ifstream input_file{"file.txt", std::ios::binary}; // Открываем файл в бинарном режиме
    if (!input_file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }
    std::vector<uint64_t> vector_of_blocks;

    uint64_t block;

    while (input_file.read(reinterpret_cast<char*>(&block), sizeof(block))) {
        vector_of_blocks.push_back(block);
    }

    input_file.close(); // Закрываем файл
    return 0;
}
