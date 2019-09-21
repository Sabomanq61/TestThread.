// Server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#pragma comment(lib,"ws2_32.lib")
#pragma  warning (disable:4996)
#include <iostream>
#include <winsock2.h>
//#include <ws2tcpip.h>
//#define __T(x)      L ## x
#define MAKEWORD(a,b)   ((WORD)(((BYTE)(a))|(((WORD)((BYTE)(b)))<<8)))
int main()
{
	WSAData wsdata;
	WORD DLLversion = MAKEWORD(2, 1);
	if (WSAStartup(DLLversion, &wsdata) != 0)
	{
		std::cout << "Error" << std::endl;
		exit(1);
	}
	SOCKADDR_IN  addr;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;
	int siad = sizeof(addr);
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, siad);
	listen(sListen, SOMAXCONN);

	SOCKET connection;
	connection = accept(sListen, (SOCKADDR*)&addr, &siad);
	
	if (connection == 0)
	{
		std::cout << "Error connection" <<std:: endl;
	}
	else
	{
		std::cout << "Connection success" << std::endl;
		char s[256];
		while (true)
		{
			if (recv(connection, s, sizeof(s), NULL) == -1)
			{
				break;
			}
			if (sizeof(s) > 2 && atoi(s) % 32 == 0)
			{
				std::cout << "Data received: " << s << std::endl;
			}
			else
			{
				std::cout << "Wrong data" << std::endl;
			}
		}
	}

	system("pause");
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
