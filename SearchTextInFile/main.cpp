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

//записываем найденные строки в файл
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
		//cout << "Not arguments" << endl;
		//mask = "System.?o";
		//mask = "CAA";
		mask = "aB";
		fname = "test5.txt";
		cout << "file: " << fname << " | mask: " << mask << '\n' << endl;
		//fname = "test2__.txt";
	}
	
	

	// запуск чтения файла и составления блоков для поиска SearchInfoText
	GetWorkStroki gws(1, fname);
	gws.CreateThread();

	// даем сформироваться первым блокам из файла
	std::this_thread::sleep_for(2000ms);//sleepTimerMain);
	
	//выводим оставшиеся блоки строк из файла для обработки
	cout << " [INPUT leave num blocks works]" << endl;
	cout << " [leave works:" << gws.safe_std->size() << "] ";
	// запусr воркеров для поиска слов в тексте
    // создаем обработчики блоков
	for (int i = 0; i < numRunThreads; i++)
	{
		thrVec[i] = new WorkerThread(i,mask);		
		thrVec[i]->CreateThread(gws.safe_std, safe_ResultSearch);
	}

	
	std::this_thread::sleep_for(sleepTimerMain);

	//выводим оставшиеся блоки строк из файла для обработки	
	while (!gws.safe_std->empty()) {
		std::this_thread::sleep_for(sleepTimerMain);
		cout << " [leave works:"<< gws.safe_std->size()<<"] " ;		
	}

	if (safe_ResultSearch->empty())
	cout << "\n\n RESULT SEARCH NOT FIND" << endl;

	// поиск строк завершен, удаляем обработчики
	cout << "\n\n\n SEARCH FINISHED .... Wait write result ..."  << endl;
	std::this_thread::sleep_for(sleepTimerMain);
	for (int i = 0; i < numRunThreads; i++)
	{
		thrVec[i]->ExitThread();
	}
	gws.ExitThread();

	if (!safe_ResultSearch->empty())
	{
		// записываем в фйл
		OutPut(fname, mask, safe_ResultSearch);
		cout << "\n\n Found [" << safe_ResultSearch->size() << "] strok. RESULT SEARCH WRITE to OUTPUT.TXT" << endl;
	}
	else
	{
		cout << "\n\n RESULT SEARCH NOT FIND" << endl;
	}

	system("pause");
}

