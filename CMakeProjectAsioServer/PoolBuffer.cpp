//#include "PoolBuffer.h"
//#include "Buffer.h"
//
////test
//#include <iostream>
//
//PoolBuffer::PoolBuffer()
//{
//}
//
//PoolBuffer::~PoolBuffer()
//{
//}
//
//void PoolBuffer::Init(const unsigned short bufferPoolCount, shared_ptr<io_service::strand> pWorkerStrand)
//{
//	m_vecBuffer.reserve(bufferPoolCount);
//
//	for (int i = 0; i < bufferPoolCount; ++i) {
//		m_vecBuffer.push_back(Buffer());
//	}
//
//	m_pWorkerStrand = pWorkerStrand;
//}
//
//void PoolBuffer::WriteData(shared_ptr<AsioSection> pSection, const char* pBuffer, unsigned short size)
//{
//	if (m_OverCount == true && m_WriteCount >= m_ReadCount) {
//		//Error
//		return;
//	}
//
//	lock_guard<mutex> lock(m_Mutex);
//
//	m_vecBuffer[m_WriteCount].Init(pSection, pBuffer, size);
//
//	if (m_WriteCount == m_vecBuffer.size())
//	{
//		m_WriteCount = 0;
//		m_OverCount = true;
//	}else {
//		++m_WriteCount;
//	}
//}
//
//void PoolBuffer::ReadData()
//{
//	if (m_OverCount == false && m_WriteCount <= m_ReadCount) {
//		//Wait
//		cout << " Read Wait " << endl;
//		return;
//	}
//
//	lock_guard<mutex> lock(m_Mutex);
//
//	Buffer buffer = m_vecBuffer[m_ReadCount];
//
//	if (m_ReadCount == m_vecBuffer.size())
//	{
//		m_ReadCount = 0;
//		m_OverCount = false;
//	}
//	else {
//		++m_ReadCount;
//	}
//
//	//m_pWorkerStrand->dispatch(boost::bind(m_WorkerCallBack, buffer.getSection().get(), buffer.getSection(), buffer.getBuffer(), buffer.getSize()));
//}