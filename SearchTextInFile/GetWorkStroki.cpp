#include "GetWorkStroki.h"

#include "Fault.h"
#include "GetWorkStroki.h"

GetWorkStroki::GetWorkStroki(int index, string fname) : m_thread(nullptr), ready(false)
{
	//contfree_safe_ptr <char*> name = 
	//safe_THREAD_NAME-> = threadName;
	//THREAD_NAME = threadName;
	this->index = index;
	this->fname = fname;

	THREAD_NAME = name();
	//safe_SearchTextData = safe_std;

}

//----------------------------------------------------------------------------
// ~GetWorkStroki
//----------------------------------------------------------------------------
GetWorkStroki::~GetWorkStroki()
{
	ExitThread();
}

//----------------------------------------------------------------------------
// CreateThread
//----------------------------------------------------------------------------
bool GetWorkStroki::CreateThread()
{
	if (!m_thread)
	{
		//cout << " GetWorkStroki Start thread [" << THREAD_NAME << "]" << endl;
		m_thread = std::unique_ptr<std::thread>(new thread(&GetWorkStroki::Run, this));
	}
	else
	{
		//cout << " GetWorkStroki Thread [" << THREAD_NAME << "] not created" << endl;
	}
	return true;
}

std::string GetWorkStroki::name()
{
	std::string str = string("Worker[") + std::to_string(index) + "]\n";	
	return str;
}

std::thread::id GetWorkStroki::GetThreadId()
{
	ASSERT_TRUE(m_thread != nullptr);
	return m_thread->get_id();
}

std::thread::id GetWorkStroki::GetCurrentThreadId()
{
	return this_thread::get_id();
}

//----------------------------------------------------------------------------
// ExitThread
//----------------------------------------------------------------------------
void GetWorkStroki::ExitThread()
{
	if (!m_thread)
		return;

	m_thread->join();
	m_thread = nullptr;

	//cout << " GetWorkStroki Stop Thread [" << name() << "] Timer" << endl;
}

void GetWorkStroki::Run()
{
	ifstream input;
	size_t pos;
	string line;
	cout << " !!!! START READING INPUT file: " << fname << endl;
	input.open(fname);
	if (input.is_open())
	{
		long k = 0;
		long nn = 0;
		string stroki[numStrokiKvant];
		SearchTextData* _std = new SearchTextData;
		while (getline(input, line))
		{			
			_std->stroki[k%numStrokiKvant]=line;
			if ((k+1)%numStrokiKvant == 0) 
     		{
				_std->numStroki = k%numStrokiKvant;
				_std->nn = nn;
				safe_std->push_back(*_std);
				nn++;
				delete _std;
				_std = new  SearchTextData;
			};
		    k++;
		}
		if ((k + 1) % numStrokiKvant != 0)
		{
			_std->numStroki = k % numStrokiKvant;
			_std->nn = nn;
			safe_std->push_back(*_std);
			nn++;
			delete _std;
			_std = new  SearchTextData;
		};
		k++;
	}



	//cout << " GetWorkStroki Stop Thread [" << name() << "] Timer" << endl;
	cout << " FINISHED READING INPUT file: " << fname << endl;
	return;
	//system("pause");
	
}