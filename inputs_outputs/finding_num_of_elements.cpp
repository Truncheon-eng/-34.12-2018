#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdint>

int main() {
	std::ifstream ifile{"new_file.txt", std::ios::binary};
	ifile.seekg(0, std::ios::end);
	size_t bytes_len = static_cast<size_t>(ifile.tellg());
	ifile.seekg(0);
	std::vector<uint64_t> vector_of_blocks;
	for(size_t i{0}; i < std::floor(bytes_len / 8); i++) {
		uint64_t buffer;
		ifile.read(reinterpret_cast<char*>(&buffer), sizeof(uint64_t));
		vector_of_blocks.push_back(buffer);
	}
	std::cout << "Position: " << ifile.tellg() << std::endl;
	std::vector<char> additional_information;
	char buffer;
	while(ifile.read(&buffer, sizeof(char))) {
		additional_information.push_back(buffer);
	}
	std::ofstream ofile{"new_file1.txt", std::ios::binary};
	ofile.write(reinterpret_cast<const char*>(vector_of_blocks.data()), vector_of_blocks.size() * sizeof(uint64_t));
	ofile.write(reinterpret_cast<const char*>(additional_information.data()), additional_information.size() * sizeof(char));
	return 0;
}