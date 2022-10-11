#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/pool/object_pool.hpp>
#include "define.h"

using namespace boost::asio;

class AsioSection;
class AsioSectionManager
{
	typedef function<void(shared_ptr<AsioSection>, shared_ptr<char[]>)> onWorkerCallBack;

public:
	AsioSectionManager(shared_ptr<io_service> pNetworkService, shared_ptr<io_service> pWorkerService, shared_ptr<ip::tcp::acceptor> pAcceptor, onWorkerCallBack workerCallBack);
	~AsioSectionManager();

	void Init(int sectionCount);
	void AcceptSection();
	void ProcessSectionAccept();

private:
	shared_ptr<io_service> m_pNetworkService = nullptr;
	shared_ptr<io_service> m_pWorkerService = nullptr;
	shared_ptr<ip::tcp::acceptor> m_pAcceptor = nullptr;
	//shared_ptr<boost::thread_group> m_pSectionThread = nullptr;
	onWorkerCallBack m_workerCallBack;

	boost::object_pool<AsioSection> m_poolSection;
	//vector<shared_ptr<AsioSection>> m_vecSection;
};