#include <iostream>
#include <fstream>
#include <ostream>
#include <cstdint>

bool read_file(const std::string& s, uint8_t * buffer, long long bf_size) {
   std::ifstream file(s, std::ios::binary | std::ios::ate); 
   if(!file) {
      std::cout << "Can't open file " << s << std::endl;
      return false;
   }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg); 

    long long fileSize = static_cast<long long>(file.tellg());
    if(fileSize > bf_size) {
	std::cout << "File is too large!" << std::endl;
	return false;
    }
    if (file.read((char *)buffer, size)) {
	std::cout << "Have read" << size << " bytes from" << s <<std::endl;
    } else {
	std::cerr << "read fail.\n";
	return false;
    }
    return true;
       
}
