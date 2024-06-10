#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "support_functions.h"

TEST_CASE("Checking applyConversionTable") {
	REQUIRE(applyConversionTable(1) == 408406884); // просто 00000000000000000000000000000001
	REQUIRE(applyConversionTable(572662306) == 3807716646); // в бинарной форм: 00100010001000100010001000100010
	CHECK(applyConversionTable(987569639) == 3677653257);
	CHECK(applyConversionTable(875678098) == 3597611494);
}

TEST_CASE("Checking key_gen function") {
	std::vector<uint32_t> res_1 = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0};
	CHECK(key_gen("../test_folder/valid_keys/key1.txt", 0) == res_1);
	std::reverse(res_1.begin(), res_1.end());
	CHECK(key_gen("../test_folder/valid_keys/key1.txt", 1) == res_1);
	std::vector<uint32_t> res_2 = {0, 0, 0, 0, 0, 0, 0, 43775, 0, 0, 0, 0, 0, 0, 0, 43775, 0, 0, 0, 0, 0, 0, 0, 43775, 43775, 0, 0, 0, 0, 0, 0, 0};
	CHECK(key_gen("../test_folder/valid_keys/key2.txt", 0) == res_2);
	std::reverse(res_2.begin(), res_2.end());
	CHECK(key_gen("../test_folder/valid_keys/key2.txt", 1) == res_2);
	std::vector<uint32_t> res_3 = {2882395596, 3148519816, 2003195204, 857870592, 4042388211, 4109760247, 4177132283, 
		4244500771, 2882395596, 3148519816, 2003195204, 857870592, 4042388211, 4109760247, 4177132283, 4244500771, 2882395596, 
		3148519816, 2003195204, 857870592, 4042388211, 4109760247, 4177132283, 4244500771, 4244500771, 4177132283, 4109760247, 
		4042388211, 857870592, 2003195204, 3148519816, 2882395596};
	CHECK(key_gen("../test_folder/valid_keys/key3.txt", 0) == res_3);
	std::reverse(res_3.begin(), res_3.end());
	CHECK(key_gen("../test_folder/valid_keys/key3.txt", 1) == res_3);
}

TEST_CASE("Checking key_is_valid function") {
	CHECK(key_is_valid("../test_folder/invalid_keys/unexistant_key_file.txt") == 0); // такого файла не сущ-ет
	CHECK(key_is_valid("../test_folder/invalid_keys/invalid_key_1.txt") == 0);
	CHECK(key_is_valid("../test_folder/invalid_keys/invalid_key_2.txt") == 0);
	CHECK(key_is_valid("../test_folder/invalid_keys/invalid_key_3.txt") == 0);
	CHECK(key_is_valid("../test_folder/valid_keys/key3.txt") == 1);
}

TEST_CASE("Checking path_to_input_file_is_valid function") {
	CHECK(path_to_input_file_is_valid("../test_folder/input_files/input_file_1.txt") == 1);
	CHECK(path_to_input_file_is_valid("../test_folder/input_files/unexistant_file") == 0);
}

TEST_CASE("Checking path_to_output_file_is_valid function") {
	CHECK(path_to_output_file_is_valid("../test_folder/output_files") == 0); // попытка создать файла с названием идентичным названию папки
	CHECK(path_to_output_file_is_valid("../test_folder/output_files/new_file.txt") == 1); // просто создание внутри папки test_folder папки
}

TEST_CASE("Checking get_data function") {
	std::pair<std::vector<uint64_t>, std::vector<char>> supposed_res_1 = {std::vector<uint64_t>{}, std::vector<char>{}};
	std::pair<std::vector<uint64_t>, std::vector<char>> res_1 = get_data("../test_folder/input_files/input_file_1.txt"); // пустой файл
	REQUIRE(res_1.first == supposed_res_1.first);
	REQUIRE(res_1.second == supposed_res_1.second);
	std::pair<std::vector<uint64_t>, std::vector<char>> supposed_res_2 = {std::vector<uint64_t>{}, std::vector<char>{0x68, 0x65}};
	std::pair<std::vector<uint64_t>, std::vector<char>> res_2 = get_data("../test_folder/input_files/input_file_2.txt"); // файл с двумя символами
	CHECK(res_2.first == supposed_res_2.first);
	CHECK(res_2.second == supposed_res_2.second);
	std::pair<std::vector<uint64_t>, std::vector<char>> supposed_res_3 = {std::vector<uint64_t>{0x412747484A4C683B}, std::vector<char>{0x4A, 0x45, 0x52, 0x47, 0x48}};
	std::pair<std::vector<uint64_t>, std::vector<char>> res_3 = get_data("../test_folder/input_files/input_file_3.txt");
	CHECK(res_3.first == supposed_res_3.first);
	CHECK(res_3.second == supposed_res_3.second);
}