#pragma once
#include "kdmapper/kdmapper.hpp"

class Mapper {
public:
	Mapper();
	~Mapper();

	bool MapDriver(unsigned char* image);
	HANDLE iqvw64e = nullptr;
};