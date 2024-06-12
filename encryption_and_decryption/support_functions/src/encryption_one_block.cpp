#include "support_functions.h"

uint64_t encryption_one_block(const uint64_t &original_block,
                              const std::vector<uint32_t> &generated_keys) {
    uint32_t first_32_bits = static_cast<uint32_t>(original_block >> 32);
    uint32_t second_32_bits =
        static_cast<uint32_t>(original_block & 0x00000000FFFFFFFF);
    uint64_t result;
    for (int i{0}; i < 31; i++) {
        uint32_t G_converted_32_bits;
        G_converted_32_bits =
            G_conversion(first_32_bits, second_32_bits,
                         generated_keys[i]); // применение G преобразования
        first_32_bits = second_32_bits;
        second_32_bits = G_converted_32_bits;
    }
    first_32_bits = G_conversion(
        first_32_bits, second_32_bits,
        generated_keys[31]); // самая последняя итерация(то есть 32ая)
    result = (static_cast<uint64_t>(first_32_bits) << 32) +
             (static_cast<uint64_t>(second_32_bits)); // результирующий блок
    return result;
}