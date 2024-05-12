#include "support_functions.h"

void decrypt_or_encrypt_whole_file(const std::string& PATH_TO_FILE, const std::string& PATH_TO_KEY_FILE, const bool& mode, const std::string& PATH_TO_OUTPUT_FILE) {
	std::ifstream ifile{PATH_TO_FILE, std::ios::binary};
	ifile.seekg(0, std::ios::end);
	size_t bytes_len = static_cast<size_t>(ifile.tellg()); // нахождение длины "в байтах"
	ifile.seekg(0);
	std::vector<uint64_t> vector_of_blocks;
	for(size_t i{0}; i < std::floor(bytes_len / 8); i++) { // считывание блоков длиной по 64 бита, (благодаря этому не получится ifile.eof() == true и можно будет записать байты, не вошедшие в блоки по 32 бита, в буфер)
		uint64_t buffer;
		ifile.read(reinterpret_cast<char*>(&buffer), sizeof(uint64_t));
		vector_of_blocks.push_back(buffer);
	}
	std::vector<char> additional_information; // считывание буфера(после чтения последнего блока может получиться так, что ifile.tellg != bytes_len)
	char buffer;
	while(ifile.read(&buffer, sizeof(char))) {
		additional_information.push_back(buffer);
	}
	ifile.close();
	std::vector<uint32_t> keys = key_gen(PATH_TO_KEY_FILE, mode); // создание ключа для каждой из итераций
	for(size_t i{0}; i < vector_of_blocks.size(); i++) { // создание массива, состоящего из зашифрованных блоков
		vector_of_blocks[i] = encryption_one_block(vector_of_blocks[i], keys);
	}
	std::ofstream ofile{PATH_TO_OUTPUT_FILE, std::ios::binary}; // начало записи в файл по пути PATH_TO_OUTPUT_FILE
	ofile.write(reinterpret_cast<const char*>(vector_of_blocks.data()), vector_of_blocks.size() * sizeof(uint64_t));
	ofile.write(reinterpret_cast<const char*>(additional_information.data()), additional_information.size() * sizeof(char));
	ofile.close();
}

int main() {
	bool mode;
	std::cout << "Enter 0 for encryption and 1 for decryption: ";
	std::cin >> mode;
	if(mode == 0 && !std::cin.fail()) {
		std::cout << "Encryption" << std::endl;
		std::string PATH_TO_FILE;
		repeated_action(path_to_file_is_valid, PATH_TO_FILE, "Enter valid path to input file: "); // проверка файла на открытие
		std::string PATH_TO_KEY_FILE;
		repeated_action(key_is_valid, PATH_TO_KEY_FILE, "Enter correct key file to encrypt: "); // проверка файла с ключем на открытие, а также просто проверка ключа
		std::string PATH_TO_OUTPUT_FILE;
		std::cout << "Enter valid path to output file:" << std::endl;
		std::cin >> PATH_TO_OUTPUT_FILE;
		decrypt_or_encrypt_whole_file(PATH_TO_FILE, PATH_TO_KEY_FILE, mode, PATH_TO_OUTPUT_FILE); // передача введённых параметров в функцию, которая зашифровывает или расшифровывает, в зависимости от переменной mode
	} else if(mode == 1 && !std::cin.fail()) {
		std::cout << "Decryption" << std::endl;
		std::string PATH_TO_FILE;
		repeated_action(path_to_file_is_valid, PATH_TO_FILE, "Enter valid path to input file:");
		std::string PATH_TO_KEY_FILE;
		repeated_action(key_is_valid, PATH_TO_KEY_FILE, "Enter correct key file to decrypt: ");
		std::string PATH_TO_OUTPUT_FILE;
		std::cout << "Enter valid path to output file:" << std::endl;
		std::cin >> PATH_TO_OUTPUT_FILE;
		decrypt_or_encrypt_whole_file(PATH_TO_FILE, PATH_TO_KEY_FILE, mode, PATH_TO_OUTPUT_FILE);
	} else {
		std::cout << "You must enter either 0 or 1" << std::endl;
	}
	return 0;
}