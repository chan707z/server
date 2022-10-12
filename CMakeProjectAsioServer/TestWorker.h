#pragma once
#include <memory>
#include <functional>
#include <map>
#include "ErrorCode.h"
#include "Singleton.h"

class User;
class BaseSection;
class Buffer;
struct PT_Packet2S;
class TestWorker : Singleton<TestWorker>
{
public:
	TestWorker();
	~TestWorker();

	static void onRecieve(shared_ptr<BaseSection> pSection, shared_ptr<Buffer> pPacketBuffer);
	void Init();

protected:
	ErrorCode::Enum Recieve(std::shared_ptr<BaseSection> pSection, PT_Packet2S* pPacket);
	ErrorCode::Enum Login2S(shared_ptr<User> pUser, PT_Packet2S* pPacket);
	ErrorCode::Enum Test2S(shared_ptr<User> pUser, PT_Packet2S* pPacket);
private:
	map<int, function<ErrorCode::Enum(shared_ptr<User>, PT_Packet2S*)>> m_MapRecieveFuc;
};