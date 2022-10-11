#pragma once
#include "define.h"
#include <boost/thread.hpp>
#include <boost/asio.hpp>

class AsioSection;
class UserBase
{
public:
	UserBase();
	~UserBase();

	void Send(char* pData, unsigned short size);
	void Disconnect();
	
protected:
	void SetSection(shared_ptr<AsioSection> pSection);
	virtual void OnDisconnect() = 0;

private:
	mutex m_Mutex;
	shared_ptr<AsioSection> m_pSection = nullptr;
};