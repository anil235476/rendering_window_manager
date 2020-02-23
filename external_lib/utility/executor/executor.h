#ifndef __EXECUTOR_H_H__
#define __EXECUTOR_H_H__
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <stlab/task.hpp>

namespace util {
	using task = stlab::v1::task<void()>;// std::function<void() >;
	class executor {
	private:
		std::queue<task>  queue_;
		std::thread t_;
		std::mutex mutex_;
		std::condition_variable cv_;
		bool is_continue_ = false;

		void _execute();

	public:
		~executor();
		void submit(std::function<void()> fun);
		void execute();

	};

	//helper function to return callable target

	template<typename Callable, typename... Args>
	auto make_task(Callable callable, Args... args) {
		return std::bind(callable, args...);
	}
} //namespace util

#endif//__EXECUTOR_H_H__
