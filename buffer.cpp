#include "buffer.h"

buffer::buffer(string name, char* IP, int port)
{
	file_name = name;
	work = false;
	Connect(IP, port);
}
bool buffer::Connect(char* IP, int port)
{
	WSAData wsdata;
	WORD DLLversion = MAKEWORD(2, 1);
	if (WSAStartup(DLLversion, &wsdata) != 0)
	{
		return false;
	}
	SOCKADDR_IN  addr;
	addr.sin_addr.S_un.S_addr = inet_addr(IP);
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		return false;
	}
	return true;
}
bool buffer::Check_string(string temp)
{
	if (temp.size() > 64)
		return false;
	for (int i = 0; i < temp.size(); i++)
	{
		if (!((int(temp[i]) > 47 && int(temp[i]) < 58) || int(temp[i]) == 32))
			return false;
	}
	return true;
}

void buffer::Write()
{
	while (true) 
	{
		cout << "Enter string:";
		string str;
		if (getline(cin, str))
		{
			if (Check_string(str))
			{
				Sort_String(str);
				str = Replacement(str);
				ofstream file(file_name);
				file << str;
				cin.clear();
				file.close();
				work = true;
				cv.notify_one();
			}
		}
	}
}

void buffer::Read()
{
	while (true)
	{
		unique_lock<mutex> lock(crown);
		while (!work)
		{
			cv.wait(lock);
		}
		ifstream file(file_name);
		char s[100]{};
		for (int i = 0; file.get(s[i]); i++);
		cout << "Read data:" << s << endl;
		file.close();
		int sum = Sum(s);
		itoa(sum, s, 10);
		send(Connection, s, sizeof(s), NULL);
		work = false;
	}
}

void buffer::Sort_String(string &str)
{
	vector<int> array;
	for (int i = 0; i < str.size(); i++)
	{
		if ((int(str[i]) > 47 && int(str[i]) < 58))
		{
			int a = 0, j = 0;
			while (int(str[i]) != 32 && i < str.size())
			{
				a = a * 10 + (int(str[i]) - 48);
				i++;
				j++;
			}
			array.push_back(a);
		}
	}
	std::sort(array.begin(), array.end(), greater<int>());
	str = "";
	for (auto i = array.begin(); i != array.end(); i++)
	{
		str += to_string(*i);
		str += " ";
	}
}

string buffer::Replacement(string str)
{
	string rezult;
	for (int i = 0; i < str.size(); i++)
	{
		if ((int(str[i]) > 47 && int(str[i]) < 58))
		{
			int a = 0, j = 0;
			while (int(str[i]) != 32 && i < str.size())
			{
				a = a * 10 + (int(str[i]) - 48);
				i++;
				j++;
			}
			if (a % 2 == 0)
			{
				rezult += "RD";
			}
			else
			{
				rezult += to_string(a);
				rezult += " ";
			}
		}
	}
	return rezult;
}

int buffer::Sum(char s[])
{
	int sum = 0, a = 0;
	for (int i = 0; s[i]; i++)
	{
		if (int(s[i]) > 47 && int(s[i]) < 58)
		{
			a = a * 10 + (int(s[i]) - 48);
		}
		else
		{
			sum += a;
			a = 0;
		}
	}
	return sum;
}

buffer::~buffer()
{
}
