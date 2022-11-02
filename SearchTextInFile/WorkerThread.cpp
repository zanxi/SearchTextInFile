#include "Search.h"
#include "WorkerThread.h"
#include "Fault.h"
#include <iostream>
#include <string>

using namespace std;

#define MSG_EXIT_THREAD			1
#define MSG_POST_USER_DATA		2
#define MSG_TIMER				3

WorkerThread::WorkerThread(const char* threadName) : m_thread(nullptr), ready(false)
{
	THREAD_NAME = name();
}

WorkerThread::WorkerThread(int index, string mask) : m_thread(nullptr), ready(false), mask(mask)
{
	this->index = index;
	THREAD_NAME = name();
}

//----------------------------------------------------------------------------
// ~WorkerThread
//----------------------------------------------------------------------------
WorkerThread::~WorkerThread()
{
	ExitThread();
}

bool WorkerThread::CreateThread(_SearchTextData &safe_std, map_InfoSearchStroki& safe_ResultSearch)
{	
	if (!m_thread)
	{
		//cout << " WorkerThread Start thread [" << THREAD_NAME <<"]" << endl;		
		m_thread = std::unique_ptr<std::thread>(new thread(&WorkerThread::Run, this, safe_std, safe_ResultSearch));
		
	}
	else
	{
		cout << " Thread [" << THREAD_NAME << "] not created" << endl;
	}
	return true;
}

std::string WorkerThread::name()
{
	std::string str = string("WorkerThread Worker[") + std::to_string(index) + "]";
	return str;
}

std::thread::id WorkerThread::GetThreadId()
{
	ASSERT_TRUE(m_thread != nullptr);
	return m_thread->get_id();
}

//----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------
std::thread::id WorkerThread::GetCurrentThreadId()
{
	return this_thread::get_id();
}

//----------------------------------------------------------------------------
// ExitThread
//----------------------------------------------------------------------------
void WorkerThread::ExitThread()
{
	if (!m_thread)
		return;


	ready = true;

    m_thread->join();
    m_thread = nullptr;
		
	//cout << " WorkerThread Stop Thread [" << name() << "] Timer" << endl;
}


void WorkerThread::FindSearch(
	string mask, 
	SearchTextData _std,
	map_InfoSearchStroki& safe_ResultSearch) {
	for (int k = 0; k < _std.numStroki; k++)
	{
		string line = _std.stroki[k];
		string mask2 = mask;
		if (line.length() < mask.size()) continue;
		int pos = Col(line, mask2);
		if (pos!=0) 
		{			
			{
				InfoSearchStroka iS;
				iS.pos = pos;
				iS.line = _std.stroki[k];
				iS.num = k + 1 + _std.nn * numStrokiKvant;
				safe_ResultSearch->insert(std::map<int, InfoSearchStroka>::value_type(iS.num, iS));

				//cout << " [pos:" << iS.pos << "][num:"<< iS.num <<"]" << endl;

			}
		}
	}
}
//----------------------------------------------------------------------------
// Process
//----------------------------------------------------------------------------
void WorkerThread::Run(
	_SearchTextData safe_std,
	map_InfoSearchStroki safe_ResultSearch)
{
	    
	while (!ready)
	{
		{
			std::unique_lock<std::mutex> lk(m_mutex);			
			{
				/*if (safe_std->size()<2)
				{
					std::this_thread::sleep_for(sleepTimer);
					continue;
				}*/
				if (!safe_std->empty()) {
					if (safe_std->size() > 0) 
					{
						SearchTextData searchTD = safe_std->front();
						safe_std->pop();

						//if (safe_std->size() >= 1) safe_std->pop();					
						FindSearch(mask, searchTD, safe_ResultSearch);
					}
					
				}
				std::this_thread::sleep_for(sleepTimer);
			}			
		}
	}
	std::unique_lock<std::mutex> lk(m_mutex);
	//cout << "\n WorkerThread Thread [" << name() << "] finished Process" << endl;
}

