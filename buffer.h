#pragma once
#pragma warning(disable:4996)
#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <string>
#include <fstream>
#include <future>
#include <condition_variable>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#define MAKEWORD(a,b)   ((WORD)(((BYTE)(a))|(((WORD)((BYTE)(b)))<<8)))

using namespace std;
class buffer
{
private:
	condition_variable cv;
	mutex crown;
	bool work;
	string file_name;
	SOCKET Connection;
public:
	buffer(string,char*,int );
	bool Connect(char* ,int);
	bool Check_string(string temp);
	void Write();
	void Read();
	void Sort_String(string &);
	string Replacement(string );
	int Sum(char[]);
	~buffer();
};

