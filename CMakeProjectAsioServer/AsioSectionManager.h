#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>

class PoolBuffer;
class AsioSection;
class AsioSectionManager
{
public:
	AsioSectionManager(std::shared_ptr<boost::asio::io_service> pService, std::shared_ptr<boost::asio::ip::tcp::acceptor> pAcceptor, std::shared_ptr<PoolBuffer> pBuffer);
	~AsioSectionManager();

	void Init(int sectionCount);
	void ProcessSectionAccept();
private:
	void _ExtendSection(int ExtendCount);

private:
	std::shared_ptr<boost::asio::io_service> m_pService = nullptr;
	std::shared_ptr<boost::asio::ip::tcp::acceptor> m_pAcceptor = nullptr;
	std::shared_ptr<boost::thread_group> m_pSectionThread = nullptr;
	std::shared_ptr<boost::asio::io_service::strand> m_pStrand = nullptr;
	std::shared_ptr<PoolBuffer> m_pPoolBuffer = nullptr;

	std::vector<std::shared_ptr<AsioSection>> m_vecSection;
};