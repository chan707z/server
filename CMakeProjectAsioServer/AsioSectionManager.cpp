#include "AsioSectionManager.h"
#include "AsioSection.h"
#include "PoolBuffer.h"

//test
#include <iostream>

AsioSectionManager::AsioSectionManager(shared_ptr<io_service> pNetworkService, shared_ptr<io_service> pWorkerService, shared_ptr<ip::tcp::acceptor> pAcceptor, onWorkerCallBack workerCallBack)
	:m_pNetworkService(pNetworkService), m_pWorkerService(pWorkerService), m_pAcceptor(pAcceptor), m_workerCallBack(workerCallBack)
{
}

AsioSectionManager::~AsioSectionManager()
{
	m_pAcceptor->close();
	m_pNetworkService->stop();
	m_pWorkerService->stop();
}

void AsioSectionManager::Init(int sectionCount = 100)
{
	for (int i = 0; i < sectionCount; ++i) {
		AcceptSection();
	}
}

void AsioSectionManager::AcceptSection()
{
	auto pSocket = make_shared<ip::tcp::socket>(*m_pNetworkService.get());

	AsioSection* pSection = m_poolSection.construct(AsioSection(m_pNetworkService, m_pWorkerService, m_pAcceptor, m_workerCallBack));
	if (pSection == nullptr) {
		return;
	}

	shared_ptr<AsioSection> pAsioSection(pSection);
	pAsioSection->Init(pSocket);

	m_pAcceptor->async_accept(
		*pAsioSection->getSocket(),
		[=](const boost::system::error_code& error_Code) {
			pAsioSection->onConnect(error_Code);
			AcceptSection();
		}
	);
}