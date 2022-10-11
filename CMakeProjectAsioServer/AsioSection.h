#pragma once

#include <boost/asio.hpp>
#include "define.h"

class PoolBuffer;
class UserBase;
class AsioSection : public std::enable_shared_from_this<AsioSection>
{
public:
	AsioSection(std::shared_ptr<boost::asio::ip::tcp::acceptor> pAcceptor, std::shared_ptr<boost::asio::io_service::strand> pStrand, std::shared_ptr<PoolBuffer> pPoolBuffer, int num);
	~AsioSection();

	void Init(std::shared_ptr<boost::asio::ip::tcp::socket> pSocket);
	std::shared_ptr<boost::asio::ip::tcp::socket> getSocket();

	void onConnect(const boost::system::error_code& err);
	void onReceive(const boost::system::error_code& err, size_t bytes_transferred);
	void onSend(const boost::system::error_code& err, size_t bytes_transferred);
	
	void Disconnect();
	void Send(char* data, int size);
	void SetUserBase(std::shared_ptr<UserBase> pUserBase);
	std::shared_ptr<UserBase> GetUserBase();
private:
	void _Recive();
	void _Send(char* data, int size);

private:
	char m_ReceiveBuffer[MAX_BUFFER];
	char m_SendBuffer[MAX_BUFFER];

	std::shared_ptr<PoolBuffer> m_pPoolBuffer = nullptr;
	std::shared_ptr<UserBase> m_pUserBase = nullptr;
	std::shared_ptr<boost::asio::ip::tcp::acceptor> m_pAcceptor = nullptr;
	std::shared_ptr<boost::asio::ip::tcp::socket> m_pSocket = nullptr;
	std::shared_ptr<boost::asio::io_service::strand> m_pStrand = nullptr;

	int TestNumber = 0;
};