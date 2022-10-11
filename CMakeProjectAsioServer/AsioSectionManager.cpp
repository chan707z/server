#include "AsioSectionManager.h"
#include "AsioSection.h"
#include "PoolBuffer.h"

//test
#include <iostream>

AsioSectionManager::AsioSectionManager(std::shared_ptr<boost::asio::io_service> pService, std::shared_ptr<boost::asio::ip::tcp::acceptor> pAcceptor, std::shared_ptr<PoolBuffer> pBuffer)
	:m_pService(pService), m_pAcceptor(pAcceptor), m_pPoolBuffer(pBuffer)
{
	m_pSectionThread = std::make_shared<boost::thread_group>();
	m_pStrand = std::make_shared<boost::asio::io_service::strand>(*m_pService.get());
}

AsioSectionManager::~AsioSectionManager()
{
	m_pSectionThread->join_all();
	m_pAcceptor->close();
	m_pService->stop();

	m_vecSection.clear();
}

void AsioSectionManager::Init(int sectionCount = 1000)
{
	m_vecSection.reserve(sectionCount);
	
	_ExtendSection(sectionCount);

	ProcessSectionAccept();
}

void AsioSectionManager::ProcessSectionAccept()
{
	m_pSectionThread->create_thread([&]() {
		while (true) {
			int Open_Section_Count = 0;
			int TestCount = 0;
			for (const auto& pSection : m_vecSection) {
				if (pSection->getSocket() == nullptr) {
					auto pSocket = std::make_shared<boost::asio::ip::tcp::socket>(*m_pService.get());
					pSection->Init(pSocket);

					m_pAcceptor->async_accept(
						*pSection->getSocket(),
						[=](const boost::system::error_code& error_Code) {
							pSection->onConnect(error_Code);
						}
					);
					std::cout << "Ready to Connect Section Num : " << TestCount << std::endl;
				}

				if (pSection->getSocket()->is_open() == true) {
					std::cout << "open Section : " << TestCount << std::endl;
					++Open_Section_Count;
				}

				++TestCount;
			}

			if (m_vecSection.size() / 2 < Open_Section_Count) {
				_ExtendSection(100);
			}

			boost::this_thread::sleep_for(boost::chrono::seconds(5));
		}
		});
}

void AsioSectionManager::_ExtendSection(int ExtendCount)
{
	int Count = m_vecSection.size();

	for (int i = 0; i < ExtendCount; ++i) {
		auto pSocket = std::make_shared<boost::asio::ip::tcp::socket>(*m_pService.get());
		auto pAsioSection = std::make_shared<AsioSection>(m_pAcceptor, m_pStrand, m_pPoolBuffer, Count + i);
		if (pAsioSection == nullptr) {
			return;
		}
		pAsioSection->Init(pSocket);

		m_pAcceptor->async_accept(
			*pAsioSection->getSocket(),
			[=](const boost::system::error_code& error_Code) {
				pAsioSection->onConnect(error_Code);
			}
		);

		m_vecSection.push_back(pAsioSection);
	}
}