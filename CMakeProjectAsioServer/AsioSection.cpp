#include "AsioSection.h"
#include <boost/thread.hpp>
#include "PoolBuffer.h"
#include "UserBase.h"

//test
#include <iostream>

AsioSection::AsioSection(std::shared_ptr<boost::asio::ip::tcp::acceptor> pAcceptor, std::shared_ptr<boost::asio::io_service::strand> pStrand, std::shared_ptr<PoolBuffer> pPoolBuffer, int num)
	:m_pAcceptor(pAcceptor), m_pStrand(pStrand), m_pPoolBuffer(pPoolBuffer), TestNumber(num)
{
}

AsioSection::~AsioSection()
{
}

void AsioSection::Init(std::shared_ptr<boost::asio::ip::tcp::socket> pSocket) {
	if (m_pSocket != nullptr) {
		return;
	}

	m_pSocket = pSocket;
}

std::shared_ptr<boost::asio::ip::tcp::socket> AsioSection::getSocket() {
	return m_pSocket;
}

void AsioSection::Disconnect() {

	if (m_pSocket != nullptr) {
		if (m_pSocket->is_open() == true) {
			m_pSocket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
			m_pSocket->close();
		}

		m_pSocket = nullptr;
		std::cout << "Disconnet Num : " << TestNumber << std::endl;
	}

	if (m_pUserBase != nullptr) {
		m_pUserBase->Disconnect();
		m_pUserBase = nullptr;
	}
}

void AsioSection::onConnect(const boost::system::error_code& err) {
	if (err) {
		cout << "[Error onConnect] Number : " << err.value() << " Message : " << err.message() << endl;
		return;
	}

	cout << "Connet Num : " << TestNumber << endl;

	boost::asio::socket_base::keep_alive option(true);
	m_pSocket->set_option(option);

	_Recive();
}

void AsioSection::onReceive(const boost::system::error_code& err, size_t bytes_transferred) {
	if (err) {
		if (err == boost::asio::error::eof) {
			cout << "Disconnet Client" << endl;
			Disconnect();
		}
		else {
			cout << "[Error onReceive] Number : " << err.value() << " Message : " << err.message() << endl;
		}
		return;
	}

	char Message[MAX_BUFFER] = {};
	memcpy(Message, m_ReceiveBuffer, bytes_transferred);

	cout << "From Client : " << &Message[0] << " Num : " << TestNumber << endl;

	m_pPoolBuffer->WriteData(shared_from_this(), Message, bytes_transferred);

	_Recive();
}

void AsioSection::onSend(const boost::system::error_code& err, size_t bytes_transferred) {
	if (err) {
		cout << "[Error onSend] Number : " << err.value() << " Message : " << err.message() << endl;
		return;
	}
}

void AsioSection::Send(char* data, int size) {
	_Send(data, size);
}

void AsioSection::SetUserBase(std::shared_ptr<UserBase> pUserBase)
{
	m_pUserBase = pUserBase;
}

std::shared_ptr<UserBase> AsioSection::GetUserBase()
{
	return m_pUserBase;
}

void AsioSection::_Recive() {
	boost::asio::async_read(*m_pSocket.get(),
		boost::asio::buffer(m_ReceiveBuffer, MAX_BUFFER),
		m_pStrand->wrap(boost::bind(&AsioSection::onReceive, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred))
	);
}

void AsioSection::_Send(char* data, int size) {
	memcpy(m_SendBuffer, data, size);
	boost::asio::async_write(*m_pSocket.get(),
		boost::asio::buffer(m_SendBuffer, MAX_BUFFER),
		m_pStrand->wrap(boost::bind(&AsioSection::onSend, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred))
	);
}