#ifndef _THREAD_STD_H
#define _THREAD_STD_H


#include "SearchTextData.h"


class WorkerThread
{
public:

    //map_InfoSearchStroki safe_ResultSearch;
    /// Constructor
    WorkerThread(const char* threadName);
    WorkerThread(int index, string mask);

    /// Destructor
    ~WorkerThread();
    string mask;
    int index;
        
    bool CreateThread(_SearchTextData &safe_std, map_InfoSearchStroki& safe_ResultSearch);
    std::string name();
    void ExitThread();
    std::thread::id GetThreadId();
    static std::thread::id GetCurrentThreadId();

private:
    WorkerThread(const WorkerThread&) = delete;
    WorkerThread& operator=(const WorkerThread&) = delete;

    void Run(_SearchTextData safe_std, map_InfoSearchStroki safe_ResultSearch);

    std::unique_ptr<std::thread> m_thread;    
    std::mutex m_mutex;    
    std::atomic<bool> ready;
    std::string THREAD_NAME;
    
    //string mask;

    _SearchTextData safe_SearchTextData;
    
    void FindSearch(
        string mask, 
        SearchTextData _std, 
        map_InfoSearchStroki& safe_ResultSearch);
};

#endif 

