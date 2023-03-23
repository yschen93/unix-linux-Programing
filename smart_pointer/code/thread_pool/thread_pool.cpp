#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <condition_variable>
#include <atomic>
#include <future>
#include <string>

namespace cc
{

class ThreadPool
{
public:
    ThreadPool(size_t thread_num)
    {
        threads_.emplace_back(
            [this] {
                std::function<void()> task;
                while (true) {
                    std::unique_lock<std::mutex> lock(mtx_);
                    {
                        cond_.wait(lock, [this] { return (stop_.load() || !tasks_.empty()); });
                        if (stop_ && tasks_.empty())
                            return ;
                        
                        task = tasks_.front();
                        tasks_.pop();
                    }
                    task();
                }
            });
    }

    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args)
        ->std::future<typename std::result_of<F(Args...)>::type>
    {
        using return_type = typename std::result_of<F(Args...)>::type;
        auto task =
            std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        
        std::future<return_type> result = task->get_future();
        if (stop_.load())
                throw std::runtime_error("Enqueue on stop ThreadPool");
        {
            std::unique_lock<std::mutex> lock(mtx_);
            tasks_.emplace([task] { (*task)(); });
        }
        cond_.notify_one();

        return result;
    }

    ~ThreadPool()
    {
        stop_.store(true);
        cond_.notify_all();
        for (auto& thread : threads_)
        {
            thread.join();
        }
    }

private:
    std::mutex mtx_;
    std::vector<std::thread> threads_;
    std::queue<std::function<void()>> tasks_;
    std::condition_variable cond_;
    std::atomic<bool> stop_ {false};
};

}

std::string foo(int i)
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return std::string("this is i: ") + std::to_string(i);
}

int main(int argc, char* argv[])
{
    std::vector<std::future<std::string>> results;
    cc::ThreadPool pool(10);
    for (int i = 0; i < 5; ++i) {
        results.emplace_back(pool.enqueue(foo, i));
    }

    for (auto& result : results)
        std::cout << result.get() << std::endl;
    getchar();
    return 0;
}

