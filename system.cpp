#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;

typedef struct {
	int code;
	char name[20];
	int sorce;
}list;

bool cmpbysorce(const list a, const list b)
{
	return a.sorce > b.sorce;
}
bool cmpbycode(const list a, const list b)
{
	return a.code < b.code;
}
void sortmessage(int mode)   //排序
{
	list srt[1000] = { NULL };
	list std;
	int i = 0;
	FILE* fp = fopen("flied.txt", "rb");
	if (!fp) {
		cout << "*文件不存在*" << endl;
		return;
	}
	if (fgetc(fp) == EOF) {        //当前文件为空
		cout << "*当前没有任何信息*" << endl;
		fclose(fp);
		return;
	}
	rewind(fp);
	while (1) {
		fread(&std, sizeof(list), 1, fp);
		if (feof(fp) != 0) break;
		srt[i++] = std;
	}
	fclose(fp);
	fp = fopen("flied.txt", "wb");
	switch (mode)
	{
	case 0:
		sort(srt,srt+i,cmpbysorce);
		break;
	case 1:
		sort(srt, srt + i,cmpbycode);
		break;
	}
	fwrite(srt, sizeof(list),i, fp);
	cout << "*排序完成*" << endl;
	fclose(fp);
}
void modifymessage()   //修改信息
{
	list std;
	list t;
	int i;
	FILE* fp = fopen("flied.txt", "rb+");
	if (fgetc(fp) == EOF) {        //当前文件为空
		cout << "*当前没有任何信息*" << endl;
		fclose(fp);
		return;
	}
	cout << "请输入要修改的学生学号" << endl;
	while (1) {
		i = 0;
		fflush(fp);
		cin >> std.code;
		if (std.code == -1) {
			fclose(fp);
			return;
		}
		fread(&t, sizeof(list), 1, fp);
		while (t.code != std.code) {
			fread(&t, sizeof(list), 1, fp);
			i++;
			if (feof(fp)) break;
		}
		if (feof(fp)) 
			cout << "*没有这个学生，请重新输入或者输入-1返回上一级*" << endl;
		else {
			strcpy(std.name, t.name);
			std.sorce = t.sorce;
			cout <<t.code << " " << setw(6) << t.name << " " << setw(3) << t.sorce << endl;
			break;
		}
	}
	getchar();
	fseek(fp,i*sizeof(list), SEEK_SET);
	while (1) {
		cout << "请选择你要修改的信息" << endl
			<< "	1.学号" << endl
			<< "	2.成绩" << endl;
		char ch = getchar();
		switch (ch)
		{
		case '1':
			cout << "请输入新的学号" << endl;
			cin >> std.code;
			fwrite(&std, sizeof(list), 1, fp);
			cout << "*修改成功*" << endl;
			fclose(fp);
			return;
		case '2':
			cout << "请输入新的成绩" << endl;
			cin >> std.sorce;
			fwrite(&std, sizeof(list), 1, fp);
			cout << "*修改成功*" << endl;
			fclose(fp);
			return;
		default:
			cout << "*输入有误，重新输入*" << endl;
			break;
		}
	}
}
void writemessage()
{                                //写入数据
	FILE* fp = fopen("flied.txt", "ab");
	list std1;
	while (1) {
		cin >> std1.code;
		if (std1.code == -1)
			break;
		cin >> std1.name >> std1.sorce;
		if (std1.code <= 10000) {
			fwrite(&std1, sizeof(list), 1, fp);
		}
		else {
			cout << "*写入失败,重新输入*" << endl;
		}
	}
	cout << "*录入完成*" << endl;
	fflush(fp);
	fclose(fp);
}
void searchmessage()
{           //查找指定数据
	int c;
	cin >> c;
	list std2;
	FILE* fp = fopen("flied.txt", "rb");
	fread(&std2, sizeof(list), 1, fp);
	while (std2.code != c) {
		fread(&std2, sizeof(list), 1, fp);
		if (feof(fp)) break;
	}
	if (feof(fp) == 0)
		cout << setw(6) << std2.code << " " << setw(6) << std2.name << " " << setw(3) << std2.sorce << endl;
	else
		cout << "*暂无此人*" << endl;
	fflush(fp);
	fclose(fp);
}
void deletemessage() 
{                 //删除指定数据
	list t[1000] = { NULL };
	list temp;
	int c;
	cin >> c;
	FILE* fp = fopen("flied.txt", "rb");
	int i = 0;
	if (fgetc(fp) == EOF) {        //当前文件为空
		cout << "*当前没有任何信息*" << endl;
		fclose(fp);
		return;
	}
	while (1) {
		fread(&temp, sizeof(list), 1, fp);
		if (feof(fp) != 0) break;
		if (temp.code != c)
			t[i++] = temp;
	}
	fclose(fp);
	fp = fopen("flied.txt", "wb");
	fwrite(t, sizeof(list), i, fp);
	fclose(fp);
	cout << "*删除成功*" << endl;
}
void printmessage() {              //输出所有数据
	FILE* fp = fopen("flied.txt", "rb");
	list str;
	if (fgetc(fp) == EOF) {        //当前文件为空
		cout << "*当前没有任何信息*" << endl;
		fclose(fp);
		return;
	}
	rewind(fp);
	double total = 0;
	double n = 0;
	while (1) {
		fread(&str, sizeof(list), 1, fp);
		if (feof(fp) != 0) break;
		cout << setw(6) << str.code << " " << setw(6) << str.name <<" "<< setw(3) << str.sorce<< endl;
		total += str.sorce;
		n++;
	}
	cout << "平均分：" << fixed << setprecision(2) << total / n <<endl;
	fclose(fp);
}

void starup() {
	cout << "   学生信息管理系统" << endl << endl;
	cout << "输入序号开始：" << endl
		<< "	1.添加一位学生的信息" << endl
		<< "	2.查找一位学生的信息" << endl
		<< "	3.删除一位学生的信息" << endl
		<< "	4.查看所有学生的信息" << endl
		<< "	5.修改一位学生的信息" << endl
		<< "	6.按学生成绩排序信息" << endl
		<< "	7.按学生学号排序信息" << endl
		<< "	0.结束" << endl;
}

int main()
{
	starup();
	while (1)
	{
		int choice;
		int i = 0;
		cout << "请输入序号" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "请输入数据,输入-1结束" << endl;
			writemessage();
			break;
		case 2:
			cout << "请输入学号" << endl;
			searchmessage();
			break;
		case 3:
			cout << "请输入要删除的学号" << endl;
			deletemessage();
			break;
		case 4:
			printmessage();
			break;
		case 5:
			modifymessage();
			break;
		case 6:
			sortmessage(0);
			break;
		case 7:
			sortmessage(1);
			break;
		case 0:
			cout << "*已关闭*";
			exit(0);
		default:
			cout << "*输入有误，请重新输入*" << endl;
			getchar();
			break;
		}
	}
	return 0;

}