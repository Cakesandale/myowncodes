#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
 
 
using namespace std;
//定义CSV读类
class CSVreader
{
	public:
		CSVreader(const char *);
		int readline();
		int data[3];
	private:
		ifstream csvInput;
};