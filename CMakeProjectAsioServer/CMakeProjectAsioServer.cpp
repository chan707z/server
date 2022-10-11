// CMakeProjectAsioServer.cpp : 애플리케이션의 진입점을 정의합니다.
//

#include "CMakeProjectAsioServer.h"
#include "AsioServer.h"
#include "TestWorker.h"
#include <boost/asio.hpp>

#define SERVER_PORT 2001
using namespace boost::asio;

int main()
{
	cout << "Hello CMake." << endl;

	auto pWorkerService = make_shared<io_service>();

	AsioServer asioServer;
	asioServer.StartServer(SERVER_PORT, 10, pWorkerService, TestWorker::onRecieve);

	auto pWorkerThread = make_shared<boost::thread_group>();
	for (int i = 0; i < WORKER_THREAD_COUNT; ++i) {
		pWorkerThread->create_thread(boost::bind(&io_service::run, pWorkerService.get()));
	}

	auto pJoinThread = make_shared<boost::thread>([&]() {
		asioServer.JoinNetworkThread();
		pWorkerThread->join_all();
	});
	
	pJoinThread->join();

	return 0;
}
