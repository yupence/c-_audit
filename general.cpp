#include "general.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>


///****************************************************************************
/// @key          :                                                                 
/// @key_length   :                                                                 
/// @box          :                                                                 
/// @brief        : return rc4 inital box with key                                                                 
///****************************************************************************
byte_t* rc4init(byte_t* key, int key_length)
{
    byte_t* box = (byte_t*)malloc(256);
    byte_t k[256] = { 0 };
    for (int i = 0; i < 256; i++) {
        box[i] = (byte_t)i;
        k[i] = key[i % key_length];
    }
    int j = 0;
    byte_t temp = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + box[i] + k[i]) % 256;
        temp = box[i];
        box[i] = box[j];
        box[j] = temp;
    }
    return box;
}

byte_t* rc4decrypt(byte_t* box, byte_t* data, int data_length) {
    int i = 0, j = 0;
    byte_t temp = 0;
    byte_t* ciphertext = (byte_t*)malloc(sizeof(byte_t) * data_length);
    if (ciphertext != NULL) {
        for (int k = 0; k < data_length; k++) {
            i = (i + 1) % 256;
            j = (j + box[i]) % 256;
            temp = box[i];
            box[i] = box[j];
            box[j] = temp;
            *(ciphertext + k) = data[k] ^ box[(box[i] + box[j]) % 256];
        }
    }
    return ciphertext;
}


///****************************************************************************                 
/// @brief   :                                                                 
///****************************************************************************
byte_t* rc4seq(byte_t* box, int data_length) {
    int i = 0, j = 0;
    byte_t temp = 0;
    byte_t* stream = (byte_t*)malloc(sizeof(byte_t) * data_length);
    if (stream != NULL) {
        for (int k = 0; k < data_length; k++) {
            i = (i + 1) % 256;
            j = (j + box[i]) % 256;
            temp = box[i];
            box[i] = box[j];
            box[j] = temp;
            *(stream + k) = box[(box[i] + box[j]) % 256];
        }
    }
    return stream;
}





///****************************************************************************                 
/// @brief   :                                                                 
///****************************************************************************
byte_t* rc4stream(byte_t* &box, byte_t* key, int key_length) {
    if (box == NULL) {
        box = rc4init(key, key_length);
    }
    return rc4seq(box, BUFFER_SIZE);
}

block multiply_sum(block* a, block* b, int length) {
    block sum = 0;
    for (int i = 0; i < length; i = i + 1) {
        sum = sum + a[i] * b[i];
    }
    return sum;
}

///****************************************************************************                 
/// @brief   :return inner product of stream                                                               
///****************************************************************************
byte_t* Hash_IP(std::string file_str, byte_t* key) {
        unsigned long long* p = (unsigned long long*) & file_str[0];
        int count = 0;
        long long unsigned sum = 0;
        block* key_list = NULL;
        byte_t* box = NULL;
        int key_list_size = BUFFER_SIZE / BLOCK_SIZE;
        size_t str_length = file_str.length();
        int last_num = str_length % BUFFER_SIZE / BLOCK_SIZE;
        size_t num = str_length / BUFFER_SIZE;
        while (true) {
            key_list = (block*)rc4stream(box, key, KEY_SIZE);
            if (count < num) {
                sum = sum + multiply_sum(key_list, p, key_list_size);
            }
            else {
                sum = sum + multiply_sum(key_list, p, last_num);
                break;
            }
            free(key_list);
            count++;
            p = (unsigned long long*) & file_str[BUFFER_SIZE * count];
        }
        std::cout << std::hex << sum << std::endl;
        return (byte_t*)&sum;
}

byte_t* Hash_DU(std::string file_str, byte_t* key)
{
    return nullptr;
}



