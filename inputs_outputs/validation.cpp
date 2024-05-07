#include <iostream>
#include <fstream>
#include <string>
#include <set>

std::set<char> possible_symbols_in_keys = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

bool key_is_valid(const std::string& key) {
	bool valid{1};
	if(key.size() == 0) {
		valid = 0;
		std::cout << "Enter the key!" << std::endl;
	} else if(key.size() > 16) {
		valid = 0;
		std::cout << "The length of key must be less or equal 16!" << std::endl;
	} else {
		for(int i{0}; i < key.size(); i++) {
			if(possible_symbols_in_keys.find(key[i]) == possible_symbols_in_keys.end()) {
				valid = 0;
				std::cout << "The key characters must match the 16 number system!" << std::endl;
				break;
			}
		}
	}
	return valid;
}

bool path_to_way_is_valid(const std::string& PATH) {
	std::ifstream file{PATH};
	std::cout << "Status of file: " << static_cast<bool>(file) << std::endl;
	return static_cast<bool>(file);
}


void repeated_action(bool (*function)(const std::string& parameter), std::string& changing_value, std::string printing_message) {
	bool flag{0};
	while(!flag) {
		std::cout << printing_message << " ";
		std::cin >> changing_value;
		flag = function(changing_value);
	}
}


int main() {
	short mode;
	std::cout << "Enter 0 for encryption and 1 for decryption:" << " ";
	std::cin >> mode;
	if(mode == 0) {
		std::cout << "Encryption" << std::endl;
		std::string PATH_TO_FILE;
		repeated_action(path_to_way_is_valid, PATH_TO_FILE, "Enter valid path to file:");
		std::string key;
		repeated_action(key_is_valid, key, "Enter key to encrypt:");
	} else if(mode == 1) {
		std::cout << "Decryption" << std::endl;
		std::string PATH_TO_FILE;
		repeated_action(path_to_way_is_valid, PATH_TO_FILE, "Enter path to file:");
		std::string key;
		repeated_action(key_is_valid, key, "Enter key to encrypt:");
	} else {
		std::cout << "You must enter either 0 or 1" << std::endl;
	}
	return 0;
}