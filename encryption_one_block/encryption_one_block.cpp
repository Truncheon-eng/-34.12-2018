#include "support_functions.h"

uint64_t encryption_one_block(const uint64_t& original_block, const std::vector<uint32_t>& generated_keys) {
	uint32_t first_32_bits = static_cast<uint32_t>(original_block >> 32);
	uint32_t second_32_bits = static_cast<uint32_t>(original_block & 0x00000000FFFFFFFF);
	uint64_t result;
	for(int i{0}; i < 31; i++) {
		uint32_t G_converted_32_bits;
		G_converted_32_bits = G_conversion(first_32_bits, second_32_bits, generated_keys[i]);
		first_32_bits = second_32_bits;
		second_32_bits = G_converted_32_bits;
	}
	first_32_bits = G_conversion(first_32_bits, second_32_bits, generated_keys[31]);
	result = (static_cast<uint64_t>(first_32_bits) << 32) + (static_cast<uint64_t>(second_32_bits));
	return result;
}

int main() {
	std::vector<uint32_t> keys = key_gen("C:\\C\\project_magma\\encryption_one_block\\keys\\key.txt");
	uint64_t one_block{0xfedcba9876543210};
	one_block = encryption_one_block(one_block, keys);
	std::cout << "Final answer: " << std::hex << one_block << std::endl;
	return 0;
}