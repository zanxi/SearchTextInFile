#pragma once

#include "libh.h"
#include "SearchTextData.h"

// класс запуска потока для чтения файла источника и 
// формирования блоков строк для обработчиков WorkerThread

class GetWorkStroki
{
public:    
    GetWorkStroki(int index, string fname = "test.txt");    
    ~GetWorkStroki();
    bool CreateThread();
    std::string name();    
    _SearchTextData safe_std; // коллекция блоков строк
        
    void ExitThread();
    std::thread::id GetThreadId();
    static std::thread::id GetCurrentThreadId();

private:
    GetWorkStroki(const GetWorkStroki&) = delete;
    GetWorkStroki& operator=(const GetWorkStroki&) = delete;
        
    void Run();
    
    std::mutex m_mutex;
    std::unique_ptr<std::thread> m_thread;
    std::string THREAD_NAME;
    int index;
    string fname; // имя файла для поиска
    std::atomic<bool> ready;

    //_SearchTextData safe_SearchTextData;
};

