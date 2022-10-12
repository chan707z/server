#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/pool/object_pool.hpp>
#include "define.h"

using namespace boost::asio;

class Buffer;
class AsioSection;
class AsioSectionManager
{
	using onWorkerCallBack = function<void(shared_ptr<AsioSection>, shared_ptr<Buffer>)>;

public:
	AsioSectionManager(shared_ptr<io_service> pNetworkService, shared_ptr<io_service> pWorkerService, shared_ptr<ip::tcp::acceptor> pAcceptor, onWorkerCallBack workerCallBack);
	~AsioSectionManager();

	void Init(int sectionCount);
	void AcceptSection();

private:
	shared_ptr<io_service> m_pNetworkService = nullptr;
	shared_ptr<io_service> m_pWorkerService = nullptr;
	shared_ptr<ip::tcp::acceptor> m_pAcceptor = nullptr;
	onWorkerCallBack m_workerCallBack;

	boost::object_pool<AsioSection> m_poolSection;
};