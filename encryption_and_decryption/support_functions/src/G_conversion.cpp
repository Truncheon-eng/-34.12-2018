#include "support_functions.h"

uint32_t g_conversion(const uint32_t& half_of_block, const uint32_t& current_key) {
	uint32_t changing_bits{half_of_block};
	changing_bits += current_key; // сложение по модулю 2^32
	changing_bits = applyConversionTable(changing_bits); // применение T преобразования
	changing_bits = ((changing_bits & 0xFFE00000) >> 21) + (changing_bits << 11); // циклический сдвиг на 11 разрядов
	return changing_bits;
}

uint32_t G_conversion(const uint32_t& first_half_bits, const uint32_t& second_half_bits, const uint32_t& current_key) {
	uint32_t changing_second_32_bits{g_conversion(second_half_bits, current_key)}; // применение g преобразования
	changing_second_32_bits = changing_second_32_bits ^ first_half_bits; // xor с левой частью
	return changing_second_32_bits;
}