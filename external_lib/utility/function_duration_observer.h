#ifndef __FUNCTION_DURATION_OBSERVER_H__
#define __FUNCTION_DURATION_OBSERVER_H__
#include <condition_variable>
#include <mutex>
#include <thread>

namespace util {
	using timeout_callback = std::function<void()>;

	class function_duration_observer {
	private:
		std::condition_variable cv_;
		std::mutex mutex_;
		std::thread t_;
		void wait_for(std::chrono::seconds duration, timeout_callback);
	public:
		function_duration_observer(std::chrono::seconds duration, timeout_callback timeout_callback_ = timeout_callback{});
		~function_duration_observer();
		

	};

}//namespace util


#endif//__FUNCTION_DURATION_OBSERVER_H__


