#include <iostream>

#include "CustomVector.h"

int main()
{
	int push_num = 4;

	CustomVector<bool> ver_bool;
	ver_bool.PrintData();
	
	bool data_bool = true;
	
	
	for (int i = 0; i < push_num; i++)
	{
		ver_bool.push_back(data_bool);
		ver_bool.PrintBitLayout(i);
	}

	ver_bool.pop_back();
	ver_bool.PrintBitLayout(push_num - 1);
	ver_bool.PrintElements();

	ver_bool.insert(2, false);
	ver_bool.PrintBitLayout(2);
	ver_bool.PrintElements();
	

	ver_bool.erase(2);
	ver_bool.PrintBitLayout(2);
	ver_bool.PrintElements();
	
	ver_bool.clear();


	std::printf("------------------------------\n");

	CustomVector<char> ver_char;
	ver_char.PrintData();

	char data_char = 'A';

	for (int i = 0; i < push_num; i++)
	{
		ver_char.push_back(data_char);
	}

	ver_char.pop_back();
	ver_char.PrintElements();
	ver_char.insert(2, 'B');
	ver_char.PrintElements();
	ver_char.erase(2);
	ver_char.PrintElements();
	ver_char.clear();


	std::printf("------------------------------\n");

	// CustomVector<int> ver_int;
	// ver_int.PrintData();
	// 
	// int data_int = 1;
	// 
	// for (int i = 0; i < push_num; i++)
	// {
	// 	ver_int.push_back(data_int);
	// }
	// 
	// ver_int.pop_back();
	// ver_int.PrintElements();
	// ver_int.insert(2, 2);
	// ver_int.PrintElements();
	// ver_int.clear();
	// 
	// 
	// std::printf("------------------------------\n");
	// 
	// CustomVector<float> ver_float;
	// ver_float.PrintData();
	// 
	// float data_float = 0.1f;
	// 
	// for (int i = 0; i < push_num; i++)
	// {
	// 	ver_float.push_back(data_float);
	// }
	// 
	// ver_float.pop_back();
	// ver_float.PrintElements();
	// ver_float.insert(2, 0.2f);
	// ver_float.PrintElements();
	// ver_float.clear();
	// 
	// 
	// std::printf("------------------------------\n");
	// 
	// CustomVector<long long> ver_longlong;
	// ver_longlong.PrintData();
	// 
	// long long data_longlong = 10000LL;
	// 
	// for (int i = 0; i < push_num; i++)
	// {
	// 	ver_longlong.push_back(data_longlong);
	// }
	// 
	// ver_longlong.pop_back();
	// ver_longlong.PrintElements();
	// ver_longlong.insert(2, 20000LL);
	// ver_longlong.PrintElements();
	// ver_longlong.clear();
	// 
	// 
	// std::printf("------------------------------\n");

	return 0;
}