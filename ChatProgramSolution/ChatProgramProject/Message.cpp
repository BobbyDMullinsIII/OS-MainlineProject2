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

	//may need to check for multiple messages
	ConVar.wait(lock, []() {return not msgs.empty();});
	//gets client message
	message = msgs.front();
	//removes message from queue
	msgs.pop();

	return message;
}

void PutMsg(string message)
{
	lock_guard<mutex> lk(m);
	//enqueue message
	msgs.push(message);
	//notifies conditional variable, and allows a waiting thread to run
	ConVar.notify_one();
}


int main(int argc, char** argv)
{
	//join server thread with client(s) thread to show messages

	return 0;
}




