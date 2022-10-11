#include "AsioSectionManager.h"
#include "AsioSection.h"
#include "PoolBuffer.h"

//test
#include <iostream>

AsioSectionManager::AsioSectionManager(shared_ptr<io_service> pNetworkService, shared_ptr<io_service> pWorkerService, shared_ptr<ip::tcp::acceptor> pAcceptor, onWorkerCallBack workerCallBack)
	:m_pNetworkService(pNetworkService), m_pWorkerService(pWorkerService), m_pAcceptor(pAcceptor), m_workerCallBack(workerCallBack)
{
	//m_pSectionThread = make_shared<boost::thread_group>();
}

AsioSectionManager::~AsioSectionManager()
{
	m_pAcceptor->close();
	m_pNetworkService->stop();
	m_pWorkerService->stop();
}

void AsioSectionManager::Init(int sectionCount = 1000)
{
	for (int i = 0; i < sectionCount; ++i) {
		AcceptSection();
	}

	//ProcessSectionAccept();
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

void AsioSectionManager::ProcessSectionAccept()
{
	/*m_pSectionThread->create_thread([&]() {
		while (true) {
			int Open_Section_Count = 0;
			int TestCount = 0;
			for (const auto& pSection : m_vecSection) {
				if (pSection->getSocket() == nullptr) {
					auto pSocket = make_shared<ip::tcp::socket>(*m_pService.get());
					pSection->Init(pSocket);

					m_pAcceptor->async_accept(
						*pSection->getSocket(),
						[=](const boost::system::error_code& error_Code) {
							pSection->onConnect(error_Code);
						}
					);
					cout << "Ready to Connect Section Num : " << TestCount << endl;
				}

				if (pSection->getSocket()->is_open() == true) {
					cout << "open Section : " << TestCount << endl;
					++Open_Section_Count;
				}

				++TestCount;
			}

			if (m_vecSection.size() / 2 < Open_Section_Count) {
				_ExtendSection(100);
			}

			boost::this_thread::sleep_for(boost::chrono::seconds(5));
		}
		});*/
}
