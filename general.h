#pragma once
#include <iostream>
#include <string>

constexpr auto BLOCK_SIZE = 8;
constexpr auto BUFFER_SIZE = 128;
constexpr auto KEY_SIZE = 16;
constexpr auto file_path = "data1.txt";
typedef unsigned long long block;
typedef unsigned char byte_t;

byte_t* rc4init(byte_t* key, int key_length);

byte_t* rc4decrypt(byte_t* box, byte_t* data, int data_length);

byte_t* rc4seq(byte_t* box, int data_length);

byte_t* Hash_IP(std::string file_str, byte_t* key);

byte_t* Hash_DU(std::string file_str, byte_t* key);