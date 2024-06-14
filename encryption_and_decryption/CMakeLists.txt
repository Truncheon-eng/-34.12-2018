cmake_minimum_required(VERSION 3.20)
project(magma)
set(wxBUILD_SHARED OFF)
add_subdirectory(wxWidgets-3.2.5)
add_subdirectory(support_functions)
add_subdirectory(googletest)
include_directories(support_functions/include classes)
add_executable(main 
	main.cpp 
	classes_sources/MainFrame.cpp
	classes_sources/RealMsgBox.cpp
)
target_link_libraries(main support_functions)
target_link_libraries(main wx::net wx::core wx::base)
add_executable(tests_for_prj 
	test_sources/tests_for_prj.cpp
	classes/MockMsgBox.h
	classes_sources/MainFrame.cpp)
target_link_libraries(tests_for_prj  wx::net wx::core wx::base)
target_link_libraries(tests_for_prj  support_functions)
target_link_libraries(tests_for_prj gtest_main gmock_main)
enable_testing()
add_test(NAME tests_for_prj COMMAND tests_for_prj --force--colors -d)