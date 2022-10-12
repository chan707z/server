#pragma once

#include <boost/asio.hpp>
#include "define.h"
#include "BaseSection.h"

using namespace boost::asio;

class Buffer;
class UserBase;
class AsioSection : public BaseSection, enable_shared_from_this<AsioSection>
{
	using onWorkerCallBack = function<void(shared_ptr<AsioSection>, shared_ptr<Buffer>)>;

public:
	AsioSection(shared_ptr<io_service> pNetworkService, shared_ptr<io_service> pWorkerService, shared_ptr<ip::tcp::acceptor> pAcceptor, onWorkerCallBack workerCallBack);
	~AsioSection();

	void Init(shared_ptr<ip::tcp::socket> pSocket);
	shared_ptr<ip::tcp::socket> getSocket();

	void onConnect(const boost::system::error_code& err);
	void onReceive(shared_ptr<AsioSection> pSection, const boost::system::error_code& err, size_t bytes_transferred);
	void onSend(shared_ptr<AsioSection> pSection, shared_ptr<char[]> data, const boost::system::error_code& err, size_t bytes_transferred);
	
	void Disconnect();
	void Send(char* data, int size);
private:
	void _Recive();
	void _Send(char* pData, int size);

private:
	char m_ReceiveBuffer[MAX_BUFFER];
	unsigned int m_OffSetReceive = 0;

	onWorkerCallBack m_WorkerCallBack;

	shared_ptr<ip::tcp::socket> m_pSocket = nullptr;
	shared_ptr<ip::tcp::acceptor> m_pAcceptor = nullptr;
	shared_ptr<io_service::strand> m_pNetworkStrand = nullptr;
	shared_ptr<io_service::strand> m_pWorkerStrand = nullptr;
};