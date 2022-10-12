#pragma once

#include <memory>
#include "define.h"
#include "Protocol.h"

class AsioSection;
class BaseWorker
{
public:
	BaseWorker();
	~BaseWorker();

	virtual void onRecieve(shared_ptr<AsioSection> pSection, shared_ptr<Buffer> pPacketBuffer) = 0;
private:

};