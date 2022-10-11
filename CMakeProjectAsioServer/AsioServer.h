#pragma once
#include <boost/asio.hpp>
#include <boost/thread.hpp>

class AsioSectionManager;
class AsioSection;
class PoolBuffer;
class AsioServer
{
public:
	AsioServer();
	~AsioServer();

	void StartServer(const unsigned short port, int sectionCount, int threadCount);

private:
	std::shared_ptr<boost::thread_group> m_pAsioRunThread = nullptr;
	std::shared_ptr<boost::thread_group> m_pWorkerThread = nullptr;
	std::shared_ptr<AsioSectionManager> m_pAsioSectionManager = nullptr;
	std::shared_ptr<PoolBuffer> m_pPoolBuffer = nullptr;
	std::shared_ptr<boost::asio::io_service::strand> m_pWorkerStrand = nullptr;
};
