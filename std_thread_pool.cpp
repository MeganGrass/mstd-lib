/*
*
*	Megan Grass
*	January 01, 2024
*
*/


#include "std_thread_pool.h"


void Standard_Thread_Pool::ThreadPoolManager(void)
{
	while (!b_Terminate)
	{
		std::unique_lock<std::mutex> Lock(m_Mutex);
		m_Condition.wait(Lock, [this] { return b_Terminate || !m_Queue.empty(); });
		if (b_Terminate || m_Queue.empty())
		{
			return;
		}
		T_FuncExec* Task = m_Queue.front();
		m_Queue.pop_front();
		Lock.unlock();
		Task->execute();
		delete Task;
	}
}

void Standard_Thread_Pool::ThreadPoolInit(std::size_t nThreads)
{
	if (!m_Threads.empty())
	{
		ThreadPoolResize(nThreads);
	}

	if (!nThreads)
	{
		nThreads = MIN_HW_THREADS;
	}

	if (nThreads > MAX_HW_THREADS)
	{
		nThreads = MAX_HW_THREADS;
	}

	for (std::size_t i = 0; i < nThreads; i++)
	{
		m_Threads.emplace_back([this] { ThreadPoolManager(); });
	}
}

void Standard_Thread_Pool::ThreadPoolResize(std::size_t nThreads)
{
	if (m_Threads.empty())
	{
		ThreadPoolInit(nThreads);
	}

	if (!nThreads)
	{
		nThreads = MIN_HW_THREADS;
	}

	if (nThreads > MAX_HW_THREADS)
	{
		nThreads = MAX_HW_THREADS;
	}

	if (nThreads < m_Threads.size())
	{
		while (ThreadPoolBusy())
		{
			std::this_thread::yield();
		}

		{
			std::scoped_lock<std::mutex> Lock(m_Mutex);
			b_Terminate = true;
		}

		m_Condition.notify_all();

		for (std::size_t i = nThreads; i < m_Threads.size(); i++)
		{
			m_Threads[i].detach();
			m_Threads.pop_back();
		}

		b_Terminate = false;
	}

	if (nThreads > m_Threads.size())
	{
		for (std::size_t i = m_Threads.size(); i < nThreads; i++)
		{
			m_Threads.emplace_back([this] { ThreadPoolManager(); });
		}
	}

}

bool Standard_Thread_Pool::ThreadPoolBusy(void)
{
	std::scoped_lock<std::mutex> Lock(m_Mutex);
	return !m_Queue.empty();
}

void Standard_Thread_Pool::ThreadPoolStop(void)
{
	{
		std::scoped_lock<std::mutex> Lock(m_Mutex);
		b_Terminate = true;
	}
	m_Condition.notify_all();
	for (std::size_t i = 0; i < m_Threads.size(); i++)
	{
		if (m_Threads[i].joinable()) { m_Threads[i].join(); }
	}
	m_Threads.clear();
	b_Terminate = false;
}