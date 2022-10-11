#pragma once
#include "define.h"
#include <memory>

class AsioSection;
class Buffer {
public:
	Buffer();
	~Buffer();

public:
	void Init(shared_ptr<AsioSection> pSection, const char* Buffer, unsigned short size);
	shared_ptr<AsioSection> getSection();
	char* getBuffer();
	unsigned short& getSize();

private:
	shared_ptr<AsioSection> m_pSection = nullptr;
	char m_Buffer[MAX_BUFFER];
	unsigned short m_size = 0;
};