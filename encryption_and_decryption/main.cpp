#include "support_functions.h"

// TODO: добавить валидатор

int main() {
	bool mode;
	std::cout << "Enter 0 for encryption and 1 for decryption: ";
	std::cin >> mode;
	if(mode == 0 && !std::cin.fail()) {
		std::cout << "Encryption" << std::endl;
		std::string PATH_TO_FILE;
		repeat_while(path_to_input_file_is_valid, PATH_TO_FILE, "Enter valid path to input file: "); // проверка файла на открытие
		std::string PATH_TO_KEY_FILE;
		repeat_while(key_is_valid, PATH_TO_KEY_FILE, "Enter correct key file to encrypt: "); // проверка файла с ключем на открытие, а также просто проверка ключа
		std::string PATH_TO_OUTPUT_FILE;
		repeat_while(path_to_output_file_is_valid, PATH_TO_OUTPUT_FILE, "Enter valid path to output file: ");
		std::pair<std::vector<uint64_t>, std::vector<char>> data_vectors = get_data(PATH_TO_FILE);
		write_to_file(PATH_TO_OUTPUT_FILE, decrypt_or_encrypt(PATH_TO_KEY_FILE, mode, std::move(data_vectors.first)), data_vectors.second);
	} else if(mode == 1 && !std::cin.fail()) {
		std::cout << "Decryption" << std::endl;
		std::string PATH_TO_FILE;
		repeat_while(path_to_input_file_is_valid, PATH_TO_FILE, "Enter valid path to input file:");
		std::string PATH_TO_KEY_FILE;
		repeat_while(key_is_valid, PATH_TO_KEY_FILE, "Enter correct key file to decrypt: ");
		std::string PATH_TO_OUTPUT_FILE;
		repeat_while(path_to_output_file_is_valid, PATH_TO_OUTPUT_FILE, "Enter valid path to output file: ");
		std::pair<std::vector<uint64_t>, std::vector<char>> data_vectors = get_data(PATH_TO_FILE);
		write_to_file(PATH_TO_OUTPUT_FILE, decrypt_or_encrypt(PATH_TO_KEY_FILE, mode, std::move(data_vectors.first)), data_vectors.second);
	} else {
		std::cout << "You must enter either 0 or 1" << std::endl;
	}
	return 0;
}