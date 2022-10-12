#include "TestWorker.h"
#include "AsioSection.h"
#include "Protocol.h"

//test
#include <iostream>

TestWorker::TestWorker()
{
}

TestWorker::~TestWorker()
{
}

void TestWorker::onRecieve(shared_ptr<AsioSection> pSection, shared_ptr<Buffer> pPacketBuffer)
{
	if (pSection == nullptr) {
		return;
	}

	Protocol_Test* pTestPacket = reinterpret_cast<Protocol_Test*>(pPacketBuffer.get());

	cout << "[Worker] From Client : " << pTestPacket->msg << endl;
}