#pragma once

#include "libh.h"
#include "ConcurrentMap.h"


const int numStrokiKvant = 128*8;
const std::chrono::milliseconds sleepTimer = 500ms;
const std::chrono::milliseconds sleepTimerMain = 750ms;


class InfoSearchStroka
{   
public:
    int pos; // позиция в строке
    int num; // номер строки
    string line; // строка 
};

class SearchTextData
{
public:
    std::string stroki[numStrokiKvant];
    //int pos[numStrokiKvant];
    int numStroki; // число строк в блоке 
    int nn; // номер блока:: координаты строк в файле nn*numStrokiKvant+i
};

//typedef contfree_safe_ptr< std::map<int, SearchTextData>> _SearchTextData;
typedef contfree_safe_ptr<std::queue<SearchTextData>> _SearchTextData;
typedef contfree_safe_ptr<std::map<int,InfoSearchStroka>> map_InfoSearchStroki;
