// InfoTecsTest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <string>
#include <fstream>
#include <future>
#include <condition_variable>
#include <winsock2.h>
#include "buffer.h"
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define MAKEWORD(a,b)   ((WORD)(((BYTE)(a))|(((WORD)((BYTE)(b)))<<8)))

using namespace std;

int main(int argc,char *argv)
{
	
	string str = "bufer.txt";
	char s[] = "127.0.0.1";
	buffer file(str, s, 1111);
	
	thread t1(&buffer::Write,ref(file));
	thread t2(&buffer::Read, ref(file));
	t1.join();
	t2.join();
	


	system("pause");
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
