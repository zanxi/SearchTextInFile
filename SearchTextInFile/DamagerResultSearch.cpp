#include "Fault.h"
#include "DamagerResultSearch.h"

DamagerResultSearch::DamagerResultSearch(int index) : m_thread(nullptr) 
{
	//contfree_safe_ptr <char*> name = 
	//safe_THREAD_NAME-> = threadName;
	//THREAD_NAME = threadName;
	this->index = index;

	THREAD_NAME = name();
	//safe_SearchTextData = safe_std;

}

//----------------------------------------------------------------------------
// ~DamagerResultSearch
//----------------------------------------------------------------------------
DamagerResultSearch::~DamagerResultSearch()
{
	ExitThread();
}

//----------------------------------------------------------------------------
// CreateThread
//----------------------------------------------------------------------------
bool DamagerResultSearch::CreateThread()
{
	if (!m_thread)
	{
		cout << " Start thread [" << THREAD_NAME << "]" << endl;
		m_thread = std::unique_ptr<std::thread>(new thread(&DamagerResultSearch::Run, this));
	}
	else
	{
		cout << " Thread [" << THREAD_NAME << "] not created" << endl;
	}
	return true;
}

std::string DamagerResultSearch::name()
{
	std::string str = string("DamagerResultSearch Worker[") + std::to_string(index) + "]";
	//const int num=static_co str.length();
	/*char nameThreads[100];
	for (int i = 0; i < str.length(); i++) {
		nameThreads[i] = str[i];
	}
	nameThreads[str.length()] = '\0';*/
	return str;
}

std::string DamagerResultSearch::nameUserData()
{
	std::string str = string("DamagerResultSearch Worker[") + std::to_string(index) + "]";
	//const int num=static_co str.length();
	/*char nameThreads[100];
	for (int i = 0; i < str.length(); i++) {
		nameThreads[i] = str[i];
	}
	nameThreads[str.length()] = '\0';*/
	return str;
}

//----------------------------------------------------------------------------
// GetThreadId
//----------------------------------------------------------------------------
std::thread::id DamagerResultSearch::GetThreadId()
{
	ASSERT_TRUE(m_thread != nullptr);
	return m_thread->get_id();
}

//----------------------------------------------------------------------------
// GetCurrentThreadId
//----------------------------------------------------------------------------
std::thread::id DamagerResultSearch::GetCurrentThreadId()
{
	return this_thread::get_id();
}

//----------------------------------------------------------------------------
// ExitThread
//----------------------------------------------------------------------------
void DamagerResultSearch::ExitThread()
{
	if (!m_thread)
		return;

	// Create a new ThreadMsg
	//std::shared_ptr<ThreadMsg> threadMsg(new ThreadMsg(MSG_EXIT_THREAD, 0));

	//// Put exit thread message into the queue
	//{
	//	lock_guard<mutex> lock(m_mutex);
	//	m_queue.push(threadMsg);
	//	m_cv.notify_one();
	//}

	m_thread->join();
	m_thread = nullptr;

	//cout << "\n Thread [" << this->THREAD_NAME << "]{"<< index <<"} finished" << endl;
	//cout << "\n Thread [" << name() << "]{" << index << "} finished" << endl;
	cout << " Stop Thread [" << name() << "] Timer" << endl;
}

void DamagerResultSearch::Run()
{
	while (1)
	{
		/*if (safe_std->empty())
		{
			std::this_thread::sleep_for(1000ms);
			continue;
		}*/

		{
			std::unique_lock<std::mutex> lk(m_mutex);
			SearchTextData searchTD;
			//searchTD = safe_std->begin();
		}
	}
}