#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

class ThreadPool
{
private:
    std::vector<std::thread> workers;

    std::queue<std::function<void()>> tasks;

    std::mutex queue_mx;
    std::condition_variable cv;
    bool stop;
public:
    ThreadPool(size_t threads);

    void enqueue(std::function<void()> task);

    ~ThreadPool();
};

#endif