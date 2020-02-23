#include "executor.h"
#include <cassert>
#include "function_duration_observer.h"

namespace util {

	constexpr int time_out_function = 20;

		void executor::_execute() {

			while (is_continue_) {

				std::unique_lock<std::mutex> lc_{ mutex_ };
				const auto is_empty = queue_.empty();
				lc_.unlock();

				if (is_empty == false) {
					std::unique_lock<std::mutex> lck_{ mutex_ };
					auto fun = std::move(queue_.front());
					queue_.pop();
					lck_.unlock();
#ifdef _DEBUG
					//this only checks if fun() return within 5 seconds or not
					function_duration_observer obser{ std::chrono::seconds(time_out_function) };
#endif//
					fun();
				}
				else {
					//queue is empty
					std::unique_lock<std::mutex> lck_{ mutex_ };
					if (queue_.empty()) {
						cv_.wait_for(lck_, std::chrono::seconds(5));
					}
				}
			}
		}

		void executor::submit(std::function<void()> fun) {
			std::lock_guard<std::mutex> lc_{ mutex_ };
			queue_.push(fun);
			cv_.notify_one();
		}

		executor::~executor() {
			is_continue_ = false;
			if(t_.joinable())
				t_.join();
		}


		void executor::execute() {
			assert(is_continue_ == false);
			is_continue_ = true;
			t_ = std::thread{ &executor::_execute, this };
		}

}