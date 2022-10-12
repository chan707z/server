#pragma once

struct Protocol_Header {
	unsigned int protocol_number;
	unsigned int size;
};

struct Protocol_Packet : public Protocol_Header {
	
};

struct Protocol_Test : public Protocol_Packet {
	char msg[1024] = "";
};