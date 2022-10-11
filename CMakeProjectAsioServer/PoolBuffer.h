#pragma once

#include <boost/thread.hpp>
#include <boost/asio.hpp>

class Buffer;
class AsioSection;
class PoolBuffer
{
public:
	PoolBuffer();
	~PoolBuffer();

public:
	void Init(const unsigned short bufferPoolCount, std::shared_ptr<boost::asio::io_service::strand> pWorkerStrand);
	void WriteData(std::shared_ptr<AsioSection> pSection, const char* pBuffer, unsigned short size);
	void ReadData();

private:
	std::mutex m_Mutex;
	std::vector<Buffer> m_vecBuffer;
	std::shared_ptr<boost::asio::io_service::strand> m_pWorkerStrand = nullptr;
	std::function<void(std::shared_ptr<AsioSection>, const char*, const size_t&)> m_WorkerCallBack;

	bool m_OverCount = false;
	unsigned short m_WriteCount = 0;
	unsigned short m_ReadCount = 0;
};