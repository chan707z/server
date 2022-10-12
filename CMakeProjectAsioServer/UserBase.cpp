#include "UserBase.h"
#include "BaseSection.h"
#include "Protocol.h"
#include "ErrorCode.h"
UserBase::UserBase() {

}

UserBase::~UserBase()
{
}

void UserBase::Send(char* pData, unsigned short size)
{
	if (m_pSection == nullptr) {
		return;
	}

	m_pSection->Send(pData, size);
}

void UserBase::Send(PT_Packet2C& packet)
{
	packet.errorCode = ErrorCode::SUCCESS;

	Send(reinterpret_cast<char*>(&packet), packet.size);
}

void UserBase::Disconnect()
{
	OnDisconnect();
	m_pSection = nullptr;
}

void UserBase::SetSection(shared_ptr<BaseSection> pSection)
{
	if (m_pSection != nullptr) {
		m_pSection->Disconnect();
	}

	m_pSection = pSection;
}