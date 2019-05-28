// DLL.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include "Main.h"
#include<iostream>
#include <string>
using namespace std;
JNIEXPORT jstring JNICALL Java_Main_Function(JNIEnv * env, jclass cls)
{
	string str;
	char **ptr_toscope = NULL;
	char **ptr_toarray = NULL;
	char *mas[3] = { "Hello","Laboratory","Work" };
	//зарезервировали память
	ptr_toscope = (char**)VirtualAlloc(NULL, 1024, MEM_RESERVE, PAGE_READWRITE);
	//распределили память
	str += "Memory is reserved\n";
	ptr_toarray = (char**)VirtualAlloc(ptr_toscope, 500, MEM_COMMIT, PAGE_READWRITE);
	str += "Memory is commmitted\n";
	ptr_toarray = mas;//
	str += "First word: ";
	str += *(ptr_toarray);
	str += "\n";//вывел первое слово
	str += "Third word: ";
	str += *(ptr_toarray + 2);
	str += "\n";//вывел первое слово
	if (VirtualFree(ptr_toscope, 0, MEM_RELEASE))
		str += "Memory is free\n";
	char **ptr_toscope2 = NULL;
	char **ptr_toarray2 = NULL;
	char *mas2[3] = { "Hello","Laboratory","Work" };
	ptr_toscope2 = (char**)VirtualAlloc(NULL, 1024, MEM_RESERVE, PAGE_READWRITE);
	ptr_toarray2 = (char**)VirtualLock(ptr_toscope2, 4000);
	ptr_toarray2 = mas2;//
	cout << "Second word: " << *(ptr_toarray + 1) << endl;//вывел 1 слово
	if (VirtualFree(ptr_toscope2, 0, MEM_RELEASE))
		str += "Memory is free\n";
	else
		str += "Memort is not free\n";
	return env->NewStringUTF(str.c_str());
}
