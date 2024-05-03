#ifndef SUPPORT_FUNCTIONS_H
#define SUPPORT_FUNCTIONS_H

#include <cstdint>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

uint32_t applyConversionTable(uint32_t block_32_bits);
uint32_t G_conversion(const uint32_t& first_half_bits, const uint32_t& second_half_bits, const uint32_t current_key);
std::vector<uint32_t> key_gen(std::string PATH_TO_FILE);

#endif
