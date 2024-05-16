#ifndef SUPPORT_FUNCTIONS_H
#define SUPPORT_FUNCTIONS_H

#include <cstdint>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include <cmath>
#include <algorithm>
#include <utility>

uint64_t encryption_one_block(const uint64_t& original_block, const std::vector<uint32_t>& generated_keys);
uint32_t G_conversion(const uint32_t& first_half_bits, const uint32_t& second_half_bits, const uint32_t& current_key);
std::vector<uint32_t> key_gen(const std::string& PATH_TO_KEY_FILE, const bool& mode);
uint32_t applyConversionTable(const uint32_t& num);
bool key_is_valid(const std::string& PATH_TO_KEY_FILE);
bool path_to_input_file_is_valid(const std::string& PATH);
bool path_to_output_file_is_valid(const std::string& PATH);
void repeat_while(bool (*function)(const std::string& parameter), std::string& changing_value, std::string printing_message);
std::pair<std::vector<uint64_t>, std::vector<char>> get_data(const std::string& PATH_TO_FILE);
std::vector<uint64_t> decrypt_or_encrypt(const std::string& PATH_TO_KEY_FILE, const bool& mode, std::vector<uint64_t>&& vector_of_blocks);
void write_to_file(const std::string& PATH_TO_OUTPUT_FILE, std::vector<uint64_t>&& encrypted_or_decrypted_blocks, 
	const std::vector<char>& additional_information);

#endif
