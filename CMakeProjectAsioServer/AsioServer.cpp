#include "AsioServer.h"
#include "AsioSection.h"
#include "AsioSectionManager.h"
#include "PoolBuffer.h"
#include "Buffer.h"

AsioServer::AsioServer()
{
}

AsioServer::~AsioServer()
{
	m_pAsioRunThread->join_all();
	m_pWorkerThread->join_all();
}

void AsioServer::StartServer(const unsigned short port, int sectionCount, shared_ptr<io_service> pWorkerService, onWorkerCallBack workerCallBack)
{
	auto pNetworkService = make_shared<io_service>();
	ip::tcp::endpoint endpoint(ip::tcp::v4(), port);
	auto pAcceptor = make_shared<ip::tcp::acceptor>(*pNetworkService.get(), endpoint);

	m_pAsioSectionManager = make_shared<AsioSectionManager>(pNetworkService, pWorkerService, pAcceptor, workerCallBack);
	m_pAsioSectionManager->Init(sectionCount);

	m_pAsioRunThread = make_shared<boost::thread_group>();
	for (int i = 0; i < NETWORK_THREAD_COUNT; ++i) {
		m_pAsioRunThread->create_thread(boost::bind(&io_service::run, pNetworkService.get()));
	}
}