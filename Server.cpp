#include "Server.h"
#include "general.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

Server::Server(std::string name) {
    name.copy(this->name, name.length());
};



byte_t* Server::prove(byte_t key[16])
{
	std::ifstream infile(file_path, std::ios::in | std::ios::binary);
    try {
        std::stringstream  file_str_stream;
        char buffer[BUFFER_SIZE]{};
        file_str_stream << infile.rdbuf();
        infile.close();
        //padding zero
        unsigned long long _file_size = std::filesystem::file_size(file_path);
        int padding_length = sizeof(block) - _file_size % sizeof(block);
        file_str_stream << std::setfill((char)0) << std::setw(padding_length) << (char)0;
        //add length
        //for (int i = 0; i < 8; i++) {
        //    file_str_stream << (char) * ((char*)&_file_size + i);
        //}
        std::string file_str = file_str_stream.str();
        return Hash_IP(file_str,key);
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

}
