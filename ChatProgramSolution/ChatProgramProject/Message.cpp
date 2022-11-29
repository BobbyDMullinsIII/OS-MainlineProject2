#include "Message.h"
#include <stdlib.h>
#include <io.h>
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <queue>
using namespace std;

queue<string> msgs;
mutex m;
condition_variable ConVar;

void ShowMsg(string text)
{
	//print text
}

string GetMsg()
{
	string message;
	unique_lock<mutex> lock(m);

	ConVar.wait(lock, []() {return not msgs.empty();});
	//gets client message
	message = msgs.front();
	msgs.pop();

	return message;
}

void PutMsg(string message)
{
	std::lock_guard<std::mutex> lk(m);
	msgs.push(message);
	ConVar.notify_one();
}


int main(int argc, char** argv)
{
	//join server thread with client(s) thread to show messages

	return 0;
}




