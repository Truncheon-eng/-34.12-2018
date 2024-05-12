#include "support_functions.h"

std::vector<uint32_t> key_gen(const std::string& PATH_TO_KEY_FILE, const bool& mode) {
	std::ifstream key_file{PATH_TO_KEY_FILE}; // предполагается, что после проверки в repeated_action Я знаю, что файл PATH_TO_KEY_FILE можно открыть
	std::string key;
	std::getline(key_file, key); //считывание самой первой строки в файле с ключом
	key_file.close();
	if(key.size() < 64) { // дополнение ключа до 64 знаков
		key = std::string(64 - key.size(), '0') + key;
	}
	std::vector<uint32_t> genereted_keys;
	std::vector<uint32_t> template_keys; // вектор, который будет состоять из последовательных ключей длиной 32 бита, то есть K_1, K_2, K_3, K_4, K_5, K_6, K_7, K_8
	for(int i{0}; i < 8; i++) { // создание такого вектора
		uint32_t current_iteration_key;
		current_iteration_key = std::stoul(key.substr(i*8, 8), nullptr, 16); // stoul необходим для преобразования строки в которой записано число, а substr - для получения подстроки
		template_keys.push_back(current_iteration_key);
	}
	for(int i{0}; i < 3; i++) std::copy(template_keys.begin(), template_keys.end(), std::back_inserter(genereted_keys)); // создание первых 24 ключей
	std::copy(template_keys.rbegin(), template_keys.rend(), std::back_inserter(genereted_keys)); // дополнение ключами на последние 8 итераций, то есть K_8, K_7, K_6, K_5, K_4, K_3, K_2, K_1
	if(mode) {
		std::reverse(genereted_keys.begin(), genereted_keys.end()); // создание ключей для расшифрования
	}
	return genereted_keys;
}