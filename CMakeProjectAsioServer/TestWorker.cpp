#include "TestWorker.h"
#include "AsioSection.h"
#include "Protocol.h"
#include "Buffer.h"
#include "User.h"
#include "UserManager.h"
//test
#include <iostream>

TestWorker::TestWorker()
{
}

TestWorker::~TestWorker()
{
}

void TestWorker::onRecieve(shared_ptr<BaseSection> pSection, shared_ptr<Buffer> pPacketBuffer)
{
	if (pSection == nullptr) {
		return;
	}

	if (pPacketBuffer == nullptr) {
		return;
	}

	PT_Packet2S* pPacket = reinterpret_cast<PT_Packet2S*>(pPacketBuffer->getBuffer());
		
	ErrorCode::Enum errCode = TestWorker::Instance()->Recieve(pSection, pPacket);
	if (errCode != ErrorCode::SUCCESS)
	{
		cout << "[Error] onRecieve" << endl;
	}
}

void TestWorker::Init() {
	m_MapRecieveFuc.insert(make_pair(Protocol::Login2S, [&](shared_ptr<User> pUser, PT_Packet2S* pPacket)->ErrorCode::Enum { return Login2S(pUser, pPacket); }));
	m_MapRecieveFuc.insert(make_pair(Protocol::TestProtocol2S, [&](shared_ptr<User> pUser, PT_Packet2S* pPacket)->ErrorCode::Enum { return Test2S(pUser, pPacket); }));
}

ErrorCode::Enum TestWorker::Recieve(std::shared_ptr<BaseSection> pSection, PT_Packet2S* pPacket) {
	
	auto iter = m_MapRecieveFuc.find(pPacket->protocol);
	if (iter == m_MapRecieveFuc.end()) {
		return ErrorCode::SYSTEM_ERROR;
	}

	shared_ptr<User> pUser = nullptr;
	if (pPacket->protocol == Protocol::Login2S) {
		PT_Login2S* pLoginPacket = reinterpret_cast<PT_Login2S*>(pPacket);
		pUser = UserManager::Instance()->getUser(pLoginPacket->uid);
		if (pUser == nullptr) {
			pUser = make_shared<User>();
			pUser->Init(pSection);
			UserManager::Instance()->JoinUser(pUser);
			pSection->SetUserBase(pUser);
		}
	}
	else {
		auto pBaseUser = pSection->GetUserBase();
		if (pBaseUser == nullptr) {
			cout << "[Error] pBaseUser == nullptr Packet : " << pPacket->protocol << endl;
			return ErrorCode::SYSTEM_ERROR;
		}

		pUser = static_pointer_cast<User>(pSection->GetUserBase());
	}

	return iter->second(pUser, pPacket);
}

ErrorCode::Enum TestWorker::Login2S(shared_ptr<User> pUser, PT_Packet2S* pPacket) {
	PT_Login2S* pReq = reinterpret_cast<PT_Login2S*>(pPacket);

	PT_Login2C res;
	pUser->Send(res);
	return ErrorCode::SUCCESS;
}

ErrorCode::Enum TestWorker::Test2S(shared_ptr<User> pUser, PT_Packet2S* pPacket) {
	PT_Test2S* pReq = reinterpret_cast<PT_Test2S*>(pPacket);

	cout << "[Worker] From Client : " << pReq->msg << endl;

	PT_Test2C res;
	pUser->Send(res);
	return ErrorCode::SUCCESS;
}