add_library(support_functions
    decryption_or_encryption_whole_file.cpp
    encryption_one_block.cpp
    G_conversion.cpp
    key_gen.cpp
    table_conversion.cpp
    validation.cpp
)
target_include_directories(support_functions PUBLIC ${CMAKE_SOURCE_DIR}/support_functions/include)
