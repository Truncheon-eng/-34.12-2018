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

uint64_t encryption_one_block(const uint64_t& original_block, const std::vector<uint32_t>& generated_keys);
uint32_t G_conversion(const uint32_t& first_half_bits, const uint32_t& second_half_bits, const uint32_t& current_key);
std::vector<uint32_t> key_gen(const std::string& PATH_TO_KEY_FILE, const bool& mode);
uint32_t applyConversionTable(const uint32_t& num);
bool key_is_valid(const std::string& PATH_TO_KEY_FILE);
bool path_to_file_is_valid(const std::string& PATH);
void repeated_action(bool (*function)(const std::string& parameter), std::string& changing_value, std::string printing_message);

#endif
