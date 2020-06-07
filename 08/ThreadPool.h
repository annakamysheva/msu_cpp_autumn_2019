#include <thread>
#include <pthread.h>
#include <future>
#include <queue>
#include <vector>
#include <functional>
#pragma once

class ThreadPool
{
	bool stop;
	std::mutex mut;
	std::vector <std::thread> threads;
	std::queue <std::function<void()>> tasks;
	std::condition_variable condition_; 

public:
    explicit ThreadPool(size_t poolSize): stop(true) {
    	for (size_t i = 0; i < poolSize; ++i) {
    		threads.emplace_back(
    			[this]() {
    					while(stop) {
		    				std::unique_lock <std::mutex> lock(mut);
				            while (stop && tasks.empty()) {
				            	condition_.wait(lock);
				            }
				            if (!stop) {
				                break;
				            }
				            auto task = tasks.front();
				            tasks.pop();
				            task();
				        }
		    	}
		    );
    	}
    }
    

    ~ThreadPool() {
    	stop = false;
    	condition_.notify_all();
    	for (auto &thr: threads) {
    		thr.join();
    	}
    }


    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
    	auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>>
            (std::bind(func, args...));
        std::unique_lock<std::mutex> lock(mut);
        tasks.push([task]() { (*task)(); });
        condition_.notify_one();
        return task->get_future();
    }
};