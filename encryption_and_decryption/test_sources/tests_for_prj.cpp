#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest/doctest.h"
#include "MainFrame.h"
#include "MockMsgBox.h"
#include "support_functions.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <wx/wx.h>

TEST_CASE("Checking applyConversionTable") {
    REQUIRE(applyConversionTable(1) ==
            408406884); // просто 00000000000000000000000000000001
    REQUIRE(applyConversionTable(572662306) ==
            3807716646); // в бинарной форме: 00100010001000100010001000100010
    CHECK(applyConversionTable(0xfdb97531) == 0x2a196f34);
    CHECK(applyConversionTable(0x2a196f34) == 0xebd9f03a);
    CHECK(applyConversionTable(0xebd9f03a) == 0xb039bb3d);
    CHECK(applyConversionTable(0xb039bb3d) == 0x68695433);
}

TEST_CASE("Checking key_gen function") {
    std::vector<uint32_t> res_1 = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
                                   0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
                                   0, 1, 1, 0, 0, 0, 0, 0, 0, 0};
    CHECK(key_gen("../test_folder/valid_keys/key1.txt", 0) == res_1);
    std::reverse(res_1.begin(), res_1.end());
    CHECK(key_gen("../test_folder/valid_keys/key1.txt", 1) == res_1);
    std::vector<uint32_t> res_2 = {
        0, 0, 0, 0, 0, 0, 0, 43775, 0,     0, 0, 0, 0, 0, 0, 43775,
        0, 0, 0, 0, 0, 0, 0, 43775, 43775, 0, 0, 0, 0, 0, 0, 0};
    CHECK(key_gen("../test_folder/valid_keys/key2.txt", 0) == res_2);
    std::reverse(res_2.begin(), res_2.end());
    CHECK(key_gen("../test_folder/valid_keys/key2.txt", 1) == res_2);
    std::vector<uint32_t> res_3 = {
        2882395596, 3148519816, 2003195204, 857870592,  4042388211, 4109760247,
        4177132283, 4244500771, 2882395596, 3148519816, 2003195204, 857870592,
        4042388211, 4109760247, 4177132283, 4244500771, 2882395596, 3148519816,
        2003195204, 857870592,  4042388211, 4109760247, 4177132283, 4244500771,
        4244500771, 4177132283, 4109760247, 4042388211, 857870592,  2003195204,
        3148519816, 2882395596};
    CHECK(key_gen("../test_folder/valid_keys/key3.txt", 0) == res_3);
    std::reverse(res_3.begin(), res_3.end());
    CHECK(key_gen("../test_folder/valid_keys/key3.txt", 1) == res_3);
}

TEST_CASE("Checking key_is_valid function") {
    CHECK(key_is_valid("../test_folder/invalid_keys/unexistant_key_file.txt") ==
          0); // такого файла не сущ-ет
    CHECK(key_is_valid("../test_folder/invalid_keys/invalid_key_1.txt") == 0);
    CHECK(key_is_valid("../test_folder/invalid_keys/invalid_key_2.txt") == 0);
    CHECK(key_is_valid("../test_folder/invalid_keys/invalid_key_3.txt") == 0);
    CHECK(key_is_valid("../test_folder/valid_keys/key3.txt") == 1);
}

TEST_CASE("Checking path_to_input_file_is_valid function") {
    CHECK(path_to_input_file_is_valid(
              "../test_folder/input_files/input_file_1.txt") == 1);
    CHECK(path_to_input_file_is_valid(
              "../test_folder/input_files/unexistant_file") == 0);
}

TEST_CASE("Checking path_to_output_file_is_valid function") {
    CHECK(path_to_output_file_is_valid("../test_folder/output_files") ==
          0); // попытка создать файла с названием идентичным названию папки
    CHECK(path_to_output_file_is_valid(
              "../test_folder/output_files/new_file.txt") ==
          1); // просто создание внутри папки test_folder папки
}

TEST_CASE("Checking get_data function") {
    std::pair<std::vector<uint64_t>, std::vector<char>> supposed_res_1 = {
        std::vector<uint64_t>{}, std::vector<char>{}};
    std::pair<std::vector<uint64_t>, std::vector<char>> res_1 =
        get_data("../test_folder/input_files/input_file_1.txt"); // пустой файл
    REQUIRE(res_1 == supposed_res_1);
    std::pair<std::vector<uint64_t>, std::vector<char>> supposed_res_2 = {
        std::vector<uint64_t>{}, std::vector<char>{0x68, 0x65}};
    std::pair<std::vector<uint64_t>, std::vector<char>> res_2 =
        get_data("../test_folder/input_files/input_file_2.txt"); // файл с двумя
                                                                 // символами
    CHECK(res_2 == supposed_res_2);
    std::pair<std::vector<uint64_t>, std::vector<char>> supposed_res_3 = {
        std::vector<uint64_t>{0x412747484A4C683B},
        std::vector<char>{0x4A, 0x45, 0x52, 0x47, 0x48}};
    std::pair<std::vector<uint64_t>, std::vector<char>> res_3 =
        get_data("../test_folder/input_files/input_file_3.txt");
    CHECK(res_3 == supposed_res_3);
}

TEST_CASE("Checking write_to_file function") {
    std::string path_to_file{
        "../test_folder/output_files/write_to_file_check.txt"};
    std::vector<uint64_t> data{};
    std::vector<char> added_data{};
    write_to_file(path_to_file, data, added_data);
    REQUIRE(
        get_data("../test_folder/output_files/write_to_file_check.txt").first ==
        data);
    REQUIRE(get_data("../test_folder/output_files/write_to_file_check.txt")
                .second == added_data);
    std::remove(path_to_file.c_str());
    data = {0x1101232134567890, 0x9876543219876543};
    added_data = {0x64, 0x35};
    write_to_file(path_to_file, data, added_data);
    CHECK(
        get_data("../test_folder/output_files/write_to_file_check.txt").first ==
        data);
    CHECK(get_data("../test_folder/output_files/write_to_file_check.txt")
              .second == added_data);
    std::remove(path_to_file.c_str());
}

TEST_CASE("Checking g_conversion function") {
    REQUIRE(g_conversion(0, 1) == 0xbe5b20c2);
    CHECK(g_conversion(0xfedcba98, 0x87654321) == 0xfdcbc20c);
    CHECK(g_conversion(0x87654321, 0xfdcbc20c) == 0x7e791a4b);
    CHECK(g_conversion(0xfdcbc20c, 0x7e791a4b) == 0xc76549ec);
}

TEST_CASE("Checking G_conversion function") {
    REQUIRE(G_conversion(0, 1, 0) == 0xbe5b20c2);
    CHECK(G_conversion(0xfedcba98, 0x76543210, 0xffeeddcc) ==
          0x28da3b14); // значения после G преобразования взяты с самого ГОСТ
    CHECK(G_conversion(0x76543210, 0x28da3b14, 0xbbaa9988) ==
          0xb14337a5); // значения после G преобразования взяты с самого ГОСТ
    CHECK(G_conversion(0x28da3b14, 0xb14337a5, 0x77665544) ==
          0x633a7c68); // значения после G преобразования взяты с самого ГОСТ
}

TEST_CASE("Checking OnHelpButtonClicked method") {
    MockMsgBox msg;
    MainFrame mainframe{&msg};
    wxCommandEvent evt(wxEVT_BUTTON, wxID_ANY);
    std::string filePath = "../helpinfo/helpinfo.txt";
    std::string info;
    std::ifstream input_(filePath);
    std::string line;
    while (std::getline(input_, line)) {
        info += line + "\n";
    }
    input_.close();
    wxString wxInfo(info.c_str(), wxConvUTF8);
    wxString help("Справка", wxConvUTF8);
    EXPECT_CALL(msg, Show(wxInfo, help, wxOK | wxICON_INFORMATION, &mainframe))
        .Times(1);
    mainframe.OnHelpButtonClicked(evt);
}

TEST_CASE("Checking encryption_one_block function") {
    std::vector<uint32_t> keys(32, 1);
    REQUIRE(encryption_one_block(1, keys) == 0x6a00da39a610c094);
    std::vector<uint32_t> keys_encryption =
        key_gen("../test_folder/valid_keys/key4.txt", 0);
    std::vector<uint32_t> keys_decryption =
        key_gen("../test_folder/valid_keys/key4.txt", 1);
    REQUIRE(encryption_one_block(0xfedcba9876543210, keys_encryption) ==
            0x4ee901e5c2d8ca3d); // пример из ГОСТа
    CHECK(encryption_one_block(0x4ee901e5c2d8ca3d, keys_decryption) ==
          0xfedcba9876543210); // пример из ГОСТа
    CHECK(encryption_one_block(0xaabbccddeeff1122, keys_encryption) ==
          0xca23d3b53fd48686);
    CHECK(encryption_one_block(0xca23d3b53fd48686, keys_decryption) ==
          0xaabbccddeeff1122);
}

TEST_CASE("Checking decrypt_or_encrypt function") {
    std::vector<uint64_t> vector_of_blocks{0xfedcba9876543210,
                                           0xaabbccddeeff1122};
    std::vector<uint64_t> vector_of_blocks_after_encryption{0x4ee901e5c2d8ca3d,
                                                            0xca23d3b53fd48686};
    REQUIRE(decrypt_or_encrypt("../test_folder/valid_keys/key4.txt", 0,
                               std::move(vector_of_blocks)) ==
            vector_of_blocks_after_encryption);
    REQUIRE(decrypt_or_encrypt("../test_folder/valid_keys/key4.txt", 1,
                               std::move(vector_of_blocks_after_encryption)) ==
            vector_of_blocks);
    vector_of_blocks = {0x1234567891234567, 0xabcdabcdabcdabcd};
    vector_of_blocks_after_encryption = {0xeb660840e8dba4ca,
                                         0x4c7e07c5ec1df9c4};
    CHECK(decrypt_or_encrypt("../test_folder/valid_keys/key1.txt", 0,
                             std::move(vector_of_blocks)) ==
          vector_of_blocks_after_encryption);
    CHECK(decrypt_or_encrypt("../test_folder/valid_keys/key1.txt", 1,
                             std::move(vector_of_blocks_after_encryption)) ==
          vector_of_blocks);
}