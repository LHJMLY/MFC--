#include "pch.h"
#include "InfoFile.h"



CInfoFile::CInfoFile()
{
}


CInfoFile::~CInfoFile()
{
}

//读取登陆信息
void CInfoFile::ReadLogin(CString &name, CString &pwd)
{
	ifstream ifs; //创建文件输入对象
	ifs.open(_F_LOGIN); //打开文件

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf)); //读取一行内容
	name = CString(buf);			 //char *转换为CString

	ifs.getline(buf, sizeof(buf));
	pwd = CString(buf);

	ifs.close(); //关闭文件
}

//修改密码
void CInfoFile::WritePwd(char* name, char* pwd)
{
	ofstream ofs;	 //创建文件输出对象
	ofs.open(_F_LOGIN); //打开文件

	ofs << name << endl; //name写入文件
	ofs << pwd << endl;	//pwd写入文件

	ofs.close();	//关闭文件
}

//读取员工信息
void CInfoFile::ReadDocline()
{
	ifstream ifs(_F_STOCK); //输入方式打开文件

	char buf[1024] = { 0 };
	num = 0;	//初始化员工数目为0
	ls.clear();
	//取出表头
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //没到文件结尾
	{
		msg tmp;

		ifs.getline(buf, sizeof(buf)); //读取一行
		num++;	//员工数目加一

		//AfxMessageBox(CString(buf));
		char *sst = strtok(buf, "|"); //以“|”切割
		if (sst != NULL)
		{
			tmp.id = atoi(sst); //员工号
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.name = sst;	//员工名称

		sst = strtok(NULL, "|");
		tmp.age  = atoi(sst);	//员工价格

		sst = strtok(NULL, "|");
		tmp.work_name = sst;	//岗位名称

		ls.push_back(tmp); //放在链表的后面
	}

	ifs.close(); //关闭文件
}

//员工写入文件
void CInfoFile::WirteDocline()
{
	ofstream ofs(_F_STOCK);//输出方式打开文件
	ofs << "工号|姓名|年龄|职位" << endl; //写入表头

	if (ls.size() > 0)	//员工链表有内容才执行
	{

		//通过迭代器取出链表内容，写入文件，以“|”分隔，结尾加换行
		for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++)
		{
			ofs << it->id << "|";		
			ofs << it->name << "|";
			ofs << it->age << "|";
			ofs << it->work_name << endl;
		}
	}

	ofs.close();//关闭文件
}

//添加新员工
//name:员工名称，age：年龄，id：职工号，work_name:岗位名称
void CInfoFile::Addline(int id, CString name, int age, CString work_name)
{
	msg tmp;
	if (!name.IsEmpty() && age > 0 && id > 0 && !work_name.IsEmpty())
		{
		    tmp.id = id;
			CStringA str;
			str = name;	//CString转CStirngA
			tmp.name = str.GetBuffer(); //CStirngA转char *，员工名称
			tmp.age = age;	//年龄
			tmp.work_name = CW2A(work_name);	//岗位
			ls.push_back(tmp);	//放在链表的后面
		}	
}


