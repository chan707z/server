#include "UserBase.h"
#include "AsioSection.h"

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

void UserBase::Disconnect()
{
	OnDisconnect();
	m_pSection = nullptr;
}

void UserBase::SetSection(shared_ptr<AsioSection> pSection)
{
	if (m_pSection != nullptr) {
		m_pSection->Disconnect();
	}

	m_pSection = pSection;
}