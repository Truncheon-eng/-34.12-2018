#include "support_functions.h"

uint32_t G_conversion(const uint32_t& first_half_bits, const uint32_t& second_half_bits, const uint32_t current_key) {
	uint32_t changing_second_32_bits{second_half_bits};
	changing_second_32_bits = changing_second_32_bits + current_key;
	changing_second_32_bits = applyConversionTable(changing_second_32_bits);
	changing_second_32_bits = changing_second_32_bits << 11;
	changing_second_32_bits = changing_second_32_bits ^ first_half_bits;
	return changing_second_32_bits;
}