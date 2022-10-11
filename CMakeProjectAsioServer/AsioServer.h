#pragma once
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "define.h"
#include "AsioSection.h"

using namespace boost::asio;

class AsioSectionManager;
class AsioSection;
class PoolBuffer;
class AsioServer
{
	typedef function<void(shared_ptr<AsioSection>, shared_ptr<char[]>)> onWorkerCallBack;
public:
	AsioServer();
	~AsioServer();

	void StartServer(const unsigned short port, int sectionCount, shared_ptr<io_service> pWorkerService, onWorkerCallBack workerCallBack);

private:
	shared_ptr<boost::thread_group> m_pAsioRunThread = nullptr;
	shared_ptr<boost::thread_group> m_pWorkerThread = nullptr;
	shared_ptr<AsioSectionManager> m_pAsioSectionManager = nullptr;
	shared_ptr<PoolBuffer> m_pPoolBuffer = nullptr;
};
