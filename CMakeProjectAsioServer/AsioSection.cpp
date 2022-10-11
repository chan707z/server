#include "AsioSection.h"
#include <boost/thread.hpp>
#include "PoolBuffer.h"
#include "UserBase.h"
#include "Protocol.h"

//test
#include <iostream>

AsioSection::AsioSection(shared_ptr<io_service> pNetworkService, shared_ptr<io_service> pWorkerService, shared_ptr<ip::tcp::acceptor> pAcceptor, onWorkerCallBack workerCallBack)
	:m_pAcceptor(pAcceptor), m_WorkerCallBack(workerCallBack)
{
	m_pNetworkStrand = make_shared<io_service::strand>(*pNetworkService.get());
	m_pWorkerStrand = make_shared<io_service::strand>(*pWorkerService.get());
}

AsioSection::~AsioSection()
{
	Disconnect();
	m_pAcceptor = nullptr;
	m_pNetworkStrand = nullptr;
	m_pWorkerStrand = nullptr;
}

void AsioSection::Init(shared_ptr<ip::tcp::socket> pSocket) {
	if (m_pSocket != nullptr) {
		return;
	}

	m_pSocket = pSocket;
}

shared_ptr<ip::tcp::socket> AsioSection::getSocket() {
	return m_pSocket;
}

void AsioSection::Disconnect() {

	if (m_pSocket != nullptr) {
		if (m_pSocket->is_open() == true) {
			m_pSocket->shutdown(ip::tcp::socket::shutdown_both);
			m_pSocket->close();
		}

		m_pSocket = nullptr;
	}

	if (GetUserBase() != nullptr) {
		GetUserBase()->Disconnect();
		SetUserBase(nullptr);
	}
}

void AsioSection::onConnect(const boost::system::error_code& err) {
	if (err) {
		cout << "[Error onConnect] Number : " << err.value() << " Message : " << err.message() << endl;
		return;
	}

	socket_base::keep_alive option(true);
	m_pSocket->set_option(option);

	_Recive();
}

void AsioSection::onReceive(const boost::system::error_code& err, size_t bytes_transferred) {
	if (err) {
		if (err == error::eof) {
			cout << "Disconnet Client" << endl;
			Disconnect();
		}
		else {
			cout << "[Error onReceive] Number : " << err.value() << " Message : " << err.message() << endl;
		}
		return;
	}

	m_OffSetReceive += static_cast<int>(bytes_transferred);

	Protocol_Packet* pPacket = reinterpret_cast<Protocol_Packet*>(m_ReceiveBuffer);
	if (m_OffSetReceive >= pPacket->size) {
		m_OffSetReceive = m_OffSetReceive - pPacket->size;
		memcpy(m_ReceiveBuffer, m_ReceiveBuffer + pPacket->size, m_OffSetReceive);

		shared_ptr<char[]> pBuffer(m_ReceiveBuffer);

		m_pWorkerStrand->dispatch(boost::bind(m_WorkerCallBack, shared_from_this(), pBuffer));

		char Message[MAX_BUFFER] = {};
		memcpy(Message, m_ReceiveBuffer, bytes_transferred);
	}

	_Recive();
}

void AsioSection::onSend(shared_ptr<char[]> data, const boost::system::error_code& err, size_t bytes_transferred) {
	if (err) {
		cout << "[Error onSend] Number : " << err.value() << " Message : " << err.message() << endl;
		return;
	}

}

void AsioSection::Send(char* pData, int size) {
	_Send(pData, size);
}

void AsioSection::_Recive() {
	async_read(*m_pSocket.get(),
		buffer(m_ReceiveBuffer + m_OffSetReceive, MAX_BUFFER - m_OffSetReceive),
		m_pNetworkStrand->wrap(boost::bind(&AsioSection::onReceive, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred))
	);
}

void AsioSection::_Send(char* pData, int size) {
	shared_ptr<char[]> pPacket(pData);
	async_write(*m_pSocket.get(),
		buffer(pPacket.get(), size),
		m_pNetworkStrand->wrap(boost::bind(&AsioSection::onSend, shared_from_this(), pPacket,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred))
	);
}