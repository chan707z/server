#pragma once
//#include "define.h"
//#include <memory>
//
//class AsioSection;
//class Buffer {
//public:
//	Buffer();
//	~Buffer();
//
//public:
//	void Init(shared_ptr<AsioSection> pSection, const char* Buffer, unsigned short size);
//	shared_ptr<AsioSection> getSection();
//	char* getBuffer();
//	unsigned short& getSize();
//
//private:
//	shared_ptr<AsioSection> m_pSection = nullptr;
//	char m_Buffer[MAX_BUFFER];
//	unsigned short m_size = 0;
//};

#include <String.h>

class Buffer {
public:
	Buffer(char* data, unsigned int size) {
		memcpy(buffer, data, size);
	}

public:
	char* getBuffer() {
		return buffer;
	}

private:
	char buffer[MAX_BUFFER] = { 0, };
};