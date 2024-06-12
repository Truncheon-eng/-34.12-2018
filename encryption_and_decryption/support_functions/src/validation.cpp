#include "support_functions.h"

std::set<char> possible_symbols_in_keys = {'0', '1', '2', '3', '4', '5',
                                           '6', '7', '8', '9', 'a', 'b',
                                           'c', 'd', 'e', 'f'};

bool key_is_valid(const std::string &PATH_TO_KEY_FILE) {
    bool valid{1};
    std::ifstream key_file{PATH_TO_KEY_FILE};
    if (key_file
            .is_open()) { // проверка на то открывается ли ключевой файл или нет
        std::string key;
        std::getline(key_file, key);
        if (key.size() == 0) {
            valid = 0;
        } else if (key.size() > 64) {
            valid = 0;
        } else {
            for (int i{0}; i < key.size(); i++) {
                if (possible_symbols_in_keys.find(key[i]) ==
                    possible_symbols_in_keys.end()) {
                    valid = 0;
                    break;
                }
            }
        }
    } else {
        valid = 0;
    }
    key_file.close();
    return valid;
}

bool path_to_input_file_is_valid(
    const std::string &PATH) { // проверка открывается ли файл или нет
    std::ifstream file{PATH};
    bool status = file.is_open();
    file.close();
    return status;
}

bool path_to_output_file_is_valid(const std::string &PATH) {
    std::ofstream file{PATH, std::ios::app};
    bool status = file.is_open();
    file.close();
    std::remove(PATH.c_str()); // c_str - возвращает указатель на const* char[],
                               // который и принимает std::remove
    return status;
}
