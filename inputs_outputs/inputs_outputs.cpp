#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint> // Для uint64_t

int main() {
    // Открываем файл в бинарном режиме
    std::ifstream input_file{"photo_2023-06-04_12-40-40.jpg", std::ios::binary}; // Замените "example_file" на ваш файл
    if (!input_file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    // Вектор для хранения 64-битных блоков
    std::vector<uint64_t> vector_of_blocks;
    uint64_t block;

    // Читаем файл поблочно (64-битные блоки)
    while (input_file.read(reinterpret_cast<char*>(&block), sizeof(block))) {
        vector_of_blocks.push_back(block);
    }

    // Если чтение закончилось раньше, чем ожидалось, проверьте, достигнут ли конец файла
    if (input_file.eof()) {
        std::cout << "End of file reached\n";
    } else if (input_file.fail()) {
        std::cerr << "An error occurred while reading the file\n";
    }

    // Выводим прочитанные блоки в шестнадцатеричном формате
    for (const auto& val : vector_of_blocks) {
        std::cout << std::hex << val << std::endl;
    }

    input_file.close(); // Закрываем файл
    return 0;
}
