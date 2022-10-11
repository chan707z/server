//#include "Buffer.h"
//
//Buffer::Buffer()
//{
//}
//
//Buffer::~Buffer()
//{
//}
//
//void Buffer::Init(shared_ptr<AsioSection> pSection, const char* Buffer, unsigned short size)
//{
//	memset(m_Buffer, 0, MAX_BUFFER);
//
//	m_pSection = pSection;
//	memcpy(m_Buffer, Buffer, size);
//	m_size = size;
//}
//
//shared_ptr<AsioSection> Buffer::getSection()
//{
//	return m_pSection;
//}
//
//char* Buffer::getBuffer()
//{
//	return m_Buffer;
//}
//
//unsigned short& Buffer::getSize()
//{
//	return m_size;
//}
