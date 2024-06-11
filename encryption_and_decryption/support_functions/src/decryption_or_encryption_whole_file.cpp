#include "support_functions.h"

std::pair<std::vector<uint64_t>, std::vector<char>> get_data(const std::string& PATH_TO_FILE) {
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
	return {vector_of_blocks, additional_information};	
}

std::vector<uint64_t> decrypt_or_encrypt(const std::string& PATH_TO_KEY_FILE, const bool& mode, std::vector<uint64_t>&& vector_of_blocks) {
	std::vector<uint64_t> encrypted_or_decrypted_blocks = vector_of_blocks;
	std::vector<uint32_t> keys = key_gen(PATH_TO_KEY_FILE, mode); // создание ключа для каждой из итераций
	for(size_t i{0}; i < encrypted_or_decrypted_blocks.size(); i++) { // создание массива, состоящего из зашифрованных блоков
		encrypted_or_decrypted_blocks[i] = encryption_one_block(encrypted_or_decrypted_blocks[i], keys);
	}
	return encrypted_or_decrypted_blocks;
}

void write_to_file(const std::string& PATH_TO_OUTPUT_FILE, const std::vector<uint64_t>& encrypted_or_decrypted_blocks, 
	const std::vector<char>& additional_information) {
	std::ofstream ofile{PATH_TO_OUTPUT_FILE, std::ios::binary}; // начало записи в файл по пути PATH_TO_OUTPUT_FILE
	ofile.write(reinterpret_cast<const char*>(encrypted_or_decrypted_blocks.data()), encrypted_or_decrypted_blocks.size() * sizeof(uint64_t));
	ofile.write(reinterpret_cast<const char*>(additional_information.data()), additional_information.size() * sizeof(char));
	ofile.close();
}