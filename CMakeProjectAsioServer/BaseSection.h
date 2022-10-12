#pragma once
#include "UserBase.h"

class BaseSection
{
public:
	BaseSection();
	~BaseSection();

	virtual void Disconnect() = 0;
	virtual void Send(char* data, int size) = 0;
	
	void SetUserBase(shared_ptr<UserBase> pUserBase);
	shared_ptr<UserBase> GetUserBase();

protected:
	shared_ptr<UserBase> m_pUserBase = nullptr;
};