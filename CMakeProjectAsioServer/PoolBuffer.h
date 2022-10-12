#pragma once

//#include <boost/thread.hpp>
//#include <boost/asio.hpp>
//
//class Buffer;
//class AsioSection;
//class PoolBuffer
//{
//public:
//	PoolBuffer();
//	~PoolBuffer();
//
//public:
//	void Init(const unsigned short bufferPoolCount, shared_ptr<io_service::strand> pWorkerStrand);
//	void WriteData(shared_ptr<AsioSection> pSection, const char* pBuffer, unsigned short size);
//	void ReadData();
//
//private:
//	vector<Buffer> m_vecBuffer;
//	shared_ptr<io_service::strand> m_pWorkerStrand = nullptr;
//	function<void(shared_ptr<AsioSection>, const char*, const size_t&)> m_WorkerCallBack;
//
//	bool m_OverCount = false;
//	unsigned short m_WriteCount = 0;
//	unsigned short m_ReadCount = 0;
//};