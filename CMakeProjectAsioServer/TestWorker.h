#pragma once
#include <memory>

class AsioSection;
class TestWorker
{
public:
	TestWorker();
	~TestWorker();

	void onRecieve(std::shared_ptr<AsioSection> pSection, const char* pData, const size_t& size);
private:

};