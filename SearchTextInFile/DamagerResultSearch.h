#pragma once

#include "libh.h"
#include "SearchTextData.h"

struct ThreadMsg;

class DamagerResultSearch
{
public:
    /// Constructor    
    DamagerResultSearch(int index);

    /// Destructor
    ~DamagerResultSearch();

    /// Called once to create the worker thread
    /// @return True if thread is created. False otherwise. 
    bool CreateThread();

    std::string name();
    std::string nameUserData();


    /// Called once a program exit to exit the worker thread
    void ExitThread();

    /// Get the ID of this thread instance
    /// @return The worker thread ID
    std::thread::id GetThreadId();

    /// Get the ID of the currently executing thread
    /// @return The current thread ID
    static std::thread::id GetCurrentThreadId();
        
private:
    DamagerResultSearch(const DamagerResultSearch&) = delete;
    DamagerResultSearch& operator=(const DamagerResultSearch&) = delete;

    /// Entry point for the worker thread
    void Run();

    /// Entry point for timer thread
    //void TimerThread();

    std::mutex m_mutex;
    std::unique_ptr<std::thread> m_thread;
    std::string THREAD_NAME;
    int index;

    //_SearchTextData safe_SearchTextData;
};



