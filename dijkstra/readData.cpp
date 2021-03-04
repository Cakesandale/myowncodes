#include "readData.h"
 
//构造函数，初始化文件路径
CSVreader::CSVreader(const char *path)
{
	csvInput.open(path);
}
//读取csv文件数据
int  CSVreader::readline()
{
	//定义一行数据为字符串
	string Oneline;
	//读取一行数据
	getline(csvInput, Oneline);
	
	//cout << "原始字符串：" << _Oneline << endl;
 
	//如果读取到首行数据，返回失败
	if (Oneline[0] == 'P')
		return EXIT_FAILURE;
	//定义字符串流对象
	istringstream Readstr(Oneline);	
	//定义一行数据中的各个字串
	string partOfstr;
	//将一行数据按'，'分割
	for(int i = 0; i < 3; i++)
	{	
		getline(Readstr, partOfstr, ',');
		data[i] = atof(partOfstr.c_str());	
		 
	}
	//判断是否读完数据
	// if ((data[0]||data[1]||data[2]) == 0)
		// return EXIT_FAILURE;
	return EXIT_SUCCESS;
};