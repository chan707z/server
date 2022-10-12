#pragma once
#include "ProtocolEnum.h"

using namespace Protocol;

struct PT_Header {
	unsigned int protocol;
	unsigned int size;
};

struct PT_Packet2S : public PT_Header {
	
};

struct PT_Packet2C : public PT_Header {
	int errorCode = 0;
};

struct PT_Login2S : public PT_Packet2S {
	int64_t uid = 0;

	PT_Login2S()
	{
		protocol = Login2S;
		size = sizeof(*this);
	}
};

struct PT_Login2C : public PT_Packet2C {
	PT_Login2C()
	{
		protocol = Login2C;
		size = sizeof(*this);
	}
};

struct PT_Test2S : public PT_Packet2S {
	char msg[1024] = "";

	PT_Test2S()
	{
		protocol = TestProtocol2S;
		size = sizeof(*this);
	}
};

struct PT_Test2C : public PT_Packet2C {
	char msg[1024] = "";

	PT_Test2C()
	{
		protocol = TestProtocol2C;
		size = sizeof(*this);
	}
};