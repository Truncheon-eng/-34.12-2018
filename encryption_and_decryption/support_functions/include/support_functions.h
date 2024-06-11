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

/**
 * @brief функция, которая реализует T-преобразование блока длиной 32 бита(T-преобразование - такое преобразование, которое
 * делит исходный 32-ух битный блок на блоки по 4 бита и меняет их в соответсвии с conversion_table).
 * @param num блок длиной 32 бита, над которым производится T преобразование.
 */
uint32_t applyConversionTable(const uint32_t& num);
/**
 * @brief функция, реализующая G-преобразование блока длиной 32 бита(G-преобразование - преобразование, описанное 
 * в ГОСТ 34.12-2018 и меняющее второй полублок исходного блока длиной 64 бита).
 * @param first_half_bits первые 32 бита, необходимые при G-преобразовании.
 * @param second_half_bits воторые 32 бита, над которыми и производится данное G-преобразование.
 * @param current_key ключ, соотвествующий определённой итерации шифра.
 * return значение получаемое в результате G-преобразования.
 */
uint32_t G_conversion(const uint32_t& first_half_bits, const uint32_t& second_half_bits, const uint32_t& current_key);
/**
 * @brief функция, зашифровывающая или расшифровывающая блок длиной 64 бита.
 * @param original_block блок длиной 64 бита, который расшифровывается или зашифровывается.
 * @param generated_keys вектор, состоящий из ключей, соответствующих каждой итерации алгоритма шифра.
 * @return зашифрованный или расшифрованный 64-х битный блок.
 */
uint64_t encryption_one_block(const uint64_t& original_block, const std::vector<uint32_t>& generated_keys);
/**
 * @brief функция-валидатор, определяющая существование файла по переданному пути и корректность содержащегося в нём ключа.
 * @param PATH_TO_KEY_FILE абсолютный путь к файлу с ключом.
 * @return true - если файл действительно существует и ключ, содержащийся в нём, валиден, false - в противном случае.
 */
bool key_is_valid(const std::string& PATH_TO_KEY_FILE);
/**
 * @brief данная функция создает поток ввода и определяет, возможно ли считывание данных из файла по указанному пути.
 * @param PATH путь к зашифровываемому или расшифровываемому файлу.
 * @return true возвращается тогда, когда открыть файл по пути получилось и считывание возможно, false - в противном случае.
 */
bool path_to_input_file_is_valid(const std::string& PATH);
/**
 * @brief данная функция создает поток вывода и определяет возможность создания файла по указанному пути.
 * @param PATH путь к файлу "вывода".
 * @return true - если создать файл по пути можно, false - в противном случае.
 */
bool path_to_output_file_is_valid(const std::string& PATH);
/**
 * @brief функция, создающая массив 32-битных ключей, соответствующих конкретной итерации алгоритма 
 * зашифрования или расшифрования.
 * @param PATH_TO_KEY_FILE путь к файлу, содержащему ключ.
 * @param mode параметр, определяющий для какого из модов необходимо создавать ключи(моды - "Зашифрование", "Расшифрование")
 * @return вектор, длиной 32, и состоящий из ключей длиной 32 бита.
 */
std::vector<uint32_t> key_gen(const std::string& PATH_TO_KEY_FILE, const bool& mode);
/**
 * @brief функция, представляющая исходный файл в виде вектора, состоящего из блоков длиною 64 бита, а также вектора типа char,
 * представляющего собой остаток, который не сумел вместиться в 64-х битный блок.
 * @param PATH_TO_FILE путь к исходному файлу.
 * @return пара векторов типа uint64_t и char.
 */
std::pair<std::vector<uint64_t>, std::vector<char>> get_data(const std::string& PATH_TO_FILE);
/**
 * @brief функция, записывающая зашифрованный или расшифрованные данные в файл.
 * @param PATH_TO_OUTPUT_FILE путь к выходному файлу.
 * @param encrypted_or_decrypted_blocks блоки длиной 64 бита.
 * @param additional_information байты, не сумевшие вместиться в 64-х битные блоки.
 */
void write_to_file(const std::string& PATH_TO_OUTPUT_FILE, const std::vector<uint64_t>& encrypted_or_decrypted_blocks, 
	const std::vector<char>& additional_information);
/**
 * @brief функция, зашифровывающая или расшифровывающая блоки длиной 64 бита.
 * @param PATH_TO_KEY_FILE путь к файлу с ключом.
 * @param mode мод("Зашифрование", "Расшифрование").
 * @param vector_of_blocks rvalue-ссылка на вектор 64-х битных блоков.
 * @return вектор 64-х битных зашифрованных или расшифрованных блоков.
 */
std::vector<uint64_t> decrypt_or_encrypt(const std::string& PATH_TO_KEY_FILE, const bool& mode, std::vector<uint64_t>&& vector_of_blocks);

#endif
