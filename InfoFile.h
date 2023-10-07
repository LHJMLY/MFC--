#pragma once

#include <list>
#include <fstream>
#include <iostream>
#include <string>
#include "pch.h"

#define _F_LOGIN "./login.ini"
#define _F_STOCK "./stock.txt"

using namespace std;

struct msg
{
	int id;			//职工号
	string name;	//员工名
	int age;			//员工年龄
	string work_name;			//岗位名称
};

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	//读取登陆信息
	void ReadLogin(CString &name, CString &pwd);

	//修改密码
	void WritePwd(char* name, char* pwd);

	// 读取员工数据
	void ReadDocline();

	//员工写入文件
	void WirteDocline();

	//添加新员工
	void Addline(int id, CString name, int age, CString work_name);

	list<msg> ls;	//存储员工容器
	int num;	//用来记录员工个数

};

