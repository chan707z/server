#pragma once
#include "define.h"
#include <boost/thread.hpp>
#include <boost/asio.hpp>

class BaseSection;
struct PT_Packet2C;
class UserBase
{
public:
	UserBase();
	~UserBase();

	void Send(char* pData, unsigned short size);
	void Send(PT_Packet2C &packet);
	void Disconnect();
	
protected:
	void SetSection(shared_ptr<BaseSection> pSection);
	virtual void OnDisconnect() = 0;

private:
	shared_ptr<BaseSection> m_pSection = nullptr;
};