#pragma once
#include "general.h"
#include <fstream>
class Server
{
public:
	byte_t* prove(byte_t Key[16]);
	char name[20];
	Server(std::string name);


};

