#include <iostream>
#include<fstream>
#include"stack.h"
#include"queue.h"
#include"dictionary.h"
using namespace std;


void main(int argc,char* argv[])
{
	
	ifstream in("C:\\Users\\lenovo\\Desktop\\date.txt");
	/*in.seekg(6);
	char ch = in.get();
	while (!in.eof())
	{
		cout << ch;
		ch = in.get();
	}*/
	ofstream out("C:\\Users\\lenovo\\Desktop\\out.txt");
	in.seekg(8);
	while (!in.eof())
	{
		char ch = in.get();
		out.put(ch);

	}
	//out.close();
	//cout << << endl;
	out.close();
	
	
	//cout << out.tellp() << endl;
}

