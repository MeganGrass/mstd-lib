/*
*
*	Megan Grass
*	January 01, 2024
*
*/


#pragma once


#include <future>

#include <mutex>

#include <condition_variable>

#include <thread>

#include <queue>

constexpr std::size_t MIN_HW_THREADS = 4;

#define MAX_HW_THREADS  std::thread::hardware_concurrency()


class Standard_Thread_Pool {
private:

	struct T_FuncExec
	{
		virtual ~T_FuncExec() = default;
		virtual void execute(void) = 0;
		virtual void operator()() = 0;
	};

	template <typename _Ret>
	class FuncExec :
		public T_FuncExec
	{
	private:
		std::packaged_task<_Ret()> m_Function;
	public:

		explicit FuncExec(std::packaged_task<_Ret()> Function) :
			m_Function(std::move(Function)) {}

		void execute(void) override { m_Function(); }

		void operator()() override { m_Function(); }

	};

	Standard_Thread_Pool(Standard_Thread_Pool&&) = delete;
	Standard_Thread_Pool& operator = (Standard_Thread_Pool&&) = delete;

	Standard_Thread_Pool(const Standard_Thread_Pool&) = delete;
	Standard_Thread_Pool& operator = (const Standard_Thread_Pool&) = delete;

	bool b_Terminate;
	std::mutex m_Mutex;
	std::condition_variable m_Condition;
	std::vector<std::jthread> m_Threads;
	std::deque<T_FuncExec*> m_Queue;

	void ThreadPoolManager(void);

public:


	/*
		Construction
	*/
	explicit Standard_Thread_Pool(void) :
		b_Terminate(false)
		{}


	/*
		Deconstruction
	*/
	virtual ~Standard_Thread_Pool(void)
	{
		ThreadPoolStop();
	}


	/*
		Initialize the thread pool
	*/
	void ThreadPoolInit(std::size_t nThreads);


	/*
		Get the number of threads in the pool
	*/
	[[nodiscard]] std::size_t ThreadPoolSize(void) const { return m_Threads.size(); }


	/*
		Resize the thread pool
	*/
	void ThreadPoolResize(std::size_t nThreads);


	/*
		Add a job to the queue
		-- multiple functions can be simultaneously added to the thread pool at once
		-- Example: auto Future = ThreadPoolEnqueue([]() { foo(); bar(); });
		-- Example: auto Future = Foo->ThreadPoolEnqueue([this]() { a = 1; foo->bar(); });
	*/
	template<typename _Fty, typename... Args, typename _Ret = std::invoke_result_t<_Fty, Args...>>
	auto ThreadPoolEnqueue(_Fty&& _Func, Args&&... _Args) -> std::future<_Ret>
	{
		std::packaged_task<_Ret()> Task(std::bind(std::forward<_Fty>(_Func), std::forward<Args>(_Args)...));
		auto Future = Task.get_future();
		{
			std::scoped_lock<std::mutex> Lock(m_Mutex);
			m_Queue.emplace_back(new FuncExec<_Ret>(std::move(Task)));
		}
		m_Condition.notify_one();
		return Future;
	}


	/*
		Test if the thread pool is busy
	*/
	[[nodiscard]] bool ThreadPoolBusy(void);


	/*
		Terminate the thread pool
	*/
	void ThreadPoolStop(void);


};