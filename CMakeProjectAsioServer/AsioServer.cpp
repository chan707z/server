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
}

void AsioServer::StartServer(const unsigned short port, int sectionCount, int threadCount)
{
	auto pService = make_shared<boost::asio::io_service>();
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
	auto pAcceptor = make_shared<boost::asio::ip::tcp::acceptor>(*pService.get(), endpoint);

	auto pWorkerService = make_shared<boost::asio::io_service>();
	m_pWorkerStrand = make_shared<boost::asio::io_service::strand>(*pWorkerService.get());
	
	m_pPoolBuffer = make_shared<PoolBuffer>();
	m_pPoolBuffer->Init(BUFFER_COUNT, m_pWorkerStrand);

	m_pAsioSectionManager = make_shared<AsioSectionManager>(pService, pAcceptor, m_pPoolBuffer);
	m_pAsioSectionManager->Init(sectionCount);

	m_pAsioRunThread = std::make_shared<boost::thread_group>();
	for (int i = 0; i < threadCount; ++i) {
		m_pAsioRunThread->create_thread(boost::bind(&boost::asio::io_service::run, pService.get()));
	}

	m_pWorkerThread = std::make_shared<boost::thread_group>();
	for (int i = 0; i < threadCount; ++i) {
		m_pWorkerThread->create_thread(boost::asio::bind_executor(*m_pWorkerStrand.get(), boost::bind(&boost::asio::io_service::run, pWorkerService.get())));
	}

	while (true) {

	}
}