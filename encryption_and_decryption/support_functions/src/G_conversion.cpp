#include "support_functions.h"

uint32_t G_conversion(const uint32_t& first_half_bits, const uint32_t& second_half_bits, const uint32_t& current_key) {
	uint32_t changing_second_32_bits{second_half_bits};
	changing_second_32_bits = changing_second_32_bits + current_key; // сложение по модулю 2^32
	changing_second_32_bits = applyConversionTable(changing_second_32_bits); // применение T преобразования
	changing_second_32_bits = ((changing_second_32_bits & 0xFFE00000) >> 21) + (changing_second_32_bits << 11); // циклический сдвиг на 11 разрядов
	changing_second_32_bits = changing_second_32_bits ^ first_half_bits; // xor с левой частью
	return changing_second_32_bits;
}