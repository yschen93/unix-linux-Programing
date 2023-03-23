#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <condition_variable>
#include <atomic>

using namespace std;

namespace cc
{   

class ThreadPool
{
public:
    ThreadPool(size_t thread_num)
    {
        threads_.emplace_back(
            [this] {
                while (true) {
                    std::lock_guard<std::mutex> lock(mtx_);
                }
            }
        );
    }

private:
    std::mutex mtx_;
    std::vector<std::thread> threads_;
    std::queue<std::function<void()>> tasks_;
    std::condition_variable cond_;
    std::atomic<bool> stop_ {false};
};

int main(int argc, char* argv[])
{
    std::thread th([]  {
        std::cout << "new thread!!!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    });
    th.join();
}

}

