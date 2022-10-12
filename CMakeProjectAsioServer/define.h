#pragma once

#define MAX_BUFFER 1024 * 16
#define BUFFER_COUNT 10000
#define NETWORK_THREAD_COUNT 10
#define WORKER_THREAD_COUNT 10

using namespace std;

struct Buffer {
	char buffer[MAX_BUFFER] = {0,};
};