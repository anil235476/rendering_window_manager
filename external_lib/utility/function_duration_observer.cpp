#include "function_duration_observer.h"
#include <cassert>

namespace util {

		function_duration_observer::function_duration_observer(std::chrono::seconds duration, timeout_callback timeout_callback_) {
			t_ = std::thread{ &function_duration_observer::wait_for, this, duration,  timeout_callback_ };
		}

		function_duration_observer::~function_duration_observer() {
			{
				std::lock_guard<std::mutex> lck_{ mutex_ };
				cv_.notify_all();
			}
			t_.join();
		}

		void 
		function_duration_observer::wait_for(std::chrono::seconds duration, timeout_callback timeout_callback_) {
			std::unique_lock<std::mutex> lck_{ mutex_ };
			auto const status = cv_.wait_for(lck_, duration);
			if (status == std::cv_status::timeout) {
				timeout_callback_();
			}
			assert(status != std::cv_status::timeout);
		}


}//namespace util