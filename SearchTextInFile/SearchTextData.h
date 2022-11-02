#pragma once

#include "libh.h"
#include "ConcurrentMap.h"


// колличетво строк для хранения
const int numStrokiKvant = 128*8;

// ожидание блока в обработчике WorkThread
const std::chrono::milliseconds sleepTimer = 500ms;

// ожидание текущей операции в основной программе
const std::chrono::milliseconds sleepTimerMain = 750ms;

// класс хранения результатов поиска в строке 
class InfoSearchStroka
{   
public: 
    int pos; // позиция в строке
    int num; // номер строки
    string line; // строка 
};

// тип потокобезопасной карты для хранения всех найденных строк
typedef contfree_safe_ptr<std::map<int, InfoSearchStroka>> map_InfoSearchStroki;


// блок строк  для обработки воркерами
class SearchTextData
{
public:
    std::string stroki[numStrokiKvant];
    //int pos[numStrokiKvant];
    int numStroki; // число строк в блоке 
    int nn; // номер блока:: координаты строк в файле nn*numStrokiKvant+i
};

//typedef contfree_safe_ptr< std::map<int, SearchTextData>> _SearchTextData;

// тип потокобезопасной очереди хранитель всех блоков строк
typedef contfree_safe_ptr<std::queue<SearchTextData>> _SearchTextData;

