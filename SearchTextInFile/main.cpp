#include "WorkerThread.h"
#include "DamagerResultSearch.h"
#include "GetWorkStroki.h"
#include "Fault.h"
#include <iostream>
#include <string>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS 10

const int numRunThreads = 8;
WorkerThread *thrVec[numRunThreads];
map_InfoSearchStroki safe_ResultSearch;
string mask;
string fname;

void OutPut(string fname, string mask, map_InfoSearchStroki safe_info)
{
	ofstream fout("output.txt");
	fout << "file: " << fname << " | mask: " << mask << '\n' << endl;
	for (std::map<int, InfoSearchStroka>::iterator it = safe_info->begin(); it != safe_info->end(); ++it)
	{
		//std::cout << it->first << " => " << it->second. << '\n';
		fout << " " << it->second.num << " " << it->second.pos << " " << it->second.line<< '\n'<<endl;
	}
	fout.close(); // закрываем файл
}

#include "Search.h"

//------------------------------------------------------------------------------
// main
//------------------------------------------------------------------------------
int main(int argc, char** argv)
{	

	setlocale(LC_ALL, "");

	if (argc > 1)// если передаем аргументы, то argc будет больше 1(в зависимости от кол-ва аргументов)
	{
		cout << argv[1] << endl;
		cout << argv[2] << endl;// вывод второй строки из массива указателей на строки(нумерация в строках начинается с 0 )
		
		fname = argv[1];
		mask = argv[2];
	}
	else
	{
		cout << "Not arguments" << endl;
		mask = "System";
		fname = "test3.txt";
	}
	
	/*cout << "----- 2 ----" << endl;
	ex2();
	cout << "----- 3 ----" << endl;
	ex3();
	cout << "----- 4 ----" << endl;
	ex4();
	cout << "----- 5 ----" << endl;
	ex5();


	
	system("pause");
	return 0;

	mask = "System";
	fname = "test3.txt";
*/


	// запуск чтения файла и составления блоков для поиска SearchInfoText
	GetWorkStroki gws(1, fname);
	gws.CreateThread();
	std::this_thread::sleep_for(2000ms);//sleepTimerMain);
	
	// запусr воркеров для поиска слов в тексте
	for (int i = 0; i < numRunThreads; i++)
	{
		thrVec[i] = new WorkerThread(i,mask);		
		thrVec[i]->CreateThread(gws.safe_std, safe_ResultSearch);
	}

	std::this_thread::sleep_for(sleepTimerMain);
	while (!gws.safe_std->empty()) {
		std::this_thread::sleep_for(sleepTimerMain);
		cout << " [leave works:"<< gws.safe_std->size()<<"] " ;		
	}

	cout << "\n\n\n SEARCH FINISHED"  << endl;
	std::this_thread::sleep_for(sleepTimerMain);
	for (int i = 0; i < numRunThreads; i++)
	{
		thrVec[i]->ExitThread();
	}

	
	OutPut(fname, mask, safe_ResultSearch);
	cout << "\n\n RESULT SEARCH WRITE to OUTPUT.TXT" << endl;

	//for (int i = 0; i < 100; i++)
	//{
	//	std::string str = string("UserData[") + to_string(i) + "]";
	//	char nameMsg[100];
	//	for (int i = 0; i < str.length(); i++) {
	//		nameMsg[i] = str[i];
	//	}
	//	nameMsg[str.length()] = '\0';

	//	std::shared_ptr<UserData> userData(new UserData());
	//		
	//	//const int num=static_co str.length();
	//	
	//	userData->msg = nameMsg;
	//	userData->year = 2017 + i;

	//	// Post the message to worker thread 1
	//	thrVec[i]->PostMsg(userData);
	//}

	//	// Give time for messages processing on worker threads
	//this_thread::sleep_for(3s);

	//for (int i = 0; i < numRunThreads; i++)
	//{
	//	thrVec[i]->ExitThread();
	//}

	//return 0;
}

