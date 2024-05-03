#include "support_functions.h"

std::vector<uint32_t> key_gen(std::string PATH_TO_FILE) {
	std::ifstream key_file{PATH_TO_FILE};
	if(!key_file.is_open()) {
		std::cerr << "Unable to open this file." << std::endl;
		return std::vector<uint32_t> {}; // необходимо понять что именно возвращать
	}
	std::string key;
	key_file >> key;
	key_file.close();
	std::vector<uint32_t> genereted_keys;
	std::vector<uint32_t> template_keys;
	for(int i{0}; i < 8; i++) {
		uint32_t current_iteration_key;
		current_iteration_key = std::stoul(key.substr(i*8, 8), nullptr, 16); // stoul необходим для преобразования строки в которой записано число, а substr - для получения подстроки
		template_keys.push_back(current_iteration_key);
	}
	for(int i{0}; i < 3; i++) std::copy(template_keys.begin(), template_keys.end(), std::back_inserter(genereted_keys));
	std::copy(template_keys.rbegin(), template_keys.rend(), std::back_inserter(genereted_keys));
	return genereted_keys;
}
