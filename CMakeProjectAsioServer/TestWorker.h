#pragma once
#include <memory>
#include "BaseWorker.h"

class AsioSection;
class TestWorker : public BaseWorker
{
public:
	TestWorker();
	~TestWorker();

	static void onRecieve(shared_ptr<AsioSection> pSection, shared_ptr<char[]> pPacketBuffer);
private:
};