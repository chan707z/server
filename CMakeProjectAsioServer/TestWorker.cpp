#include "TestWorker.h"
#include "AsioSection.h"

//test
#include <iostream>

TestWorker::TestWorker()
{
}

TestWorker::~TestWorker()
{
}

void TestWorker::onRecieve(std::shared_ptr<AsioSection> pSection, const char* pData, const size_t& size)
{
	if (pSection == nullptr) {
		return;
	}

	std::cout << "[Worker] From Client : " << &pData[0] << std::endl;
}