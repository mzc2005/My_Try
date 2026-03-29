#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <iostream>
#include <list>
#include <cstdio>
#include <exception>
#include <queue>
#include <functional>
#include <thread>
#include <vector>
#include <semaphore.h>
#include <stdexcept>
#include <pthread.h>
#include <mutex>

class ThreadPool
{
public:
    ThreadPool(int max_Pool_Size = 8, int max_Queue_Size = 100);
    ~ThreadPool();

    bool Append_Task(std::function<void()> task);

private:
    void run();

private:
    std::mutex my_Queue_mutex;
    std::queue<std::function<void()>> my_Queue;
    int my_Queue_MaxSize;
    std::vector<std::thread> my_Threads;
    int my_Thread_MaxSize;
    sem_t my_Sem;
};

ThreadPool::ThreadPool(int max_Pool_Size, int max_Queue_Size)
{
    if (max_Pool_Size <= 0 || max_Queue_Size <= 0)
        throw std::exception();

    my_Thread_MaxSize = max_Pool_Size;
    my_Queue_MaxSize = max_Queue_Size;
    int ret = sem_init(&my_Sem, 0, 0);
    if (ret != 0)
        throw std::runtime_error("信号量初始化失败！");

    for (int i = 0; i < max_Pool_Size; i++)
    {
        my_Threads.emplace_back(&ThreadPool::run, this);
        // my_Threads.back().detach();
    }
}

ThreadPool::~ThreadPool()
{
    int ret = sem_destroy(&my_Sem);
    if (ret != 0)
        throw std::runtime_error("信号量销毁失败！");
}

bool ThreadPool::Append_Task(std::function<void()> task)
{
    my_Queue_mutex.lock();
    if (my_Queue.size() >= my_Queue_MaxSize)
    {
        my_Queue_mutex.unlock();
        return false;
    }
    my_Queue.push(task);
    my_Queue_mutex.unlock();
    sem_post(&my_Sem);
    return true;
}

void ThreadPool::run()
{
    while (true)
    {
        sem_wait(&my_Sem);
        my_Queue_mutex.lock();
        if (my_Queue.size() == 0)
        {
            my_Queue_mutex.unlock();
            continue;
        }
        std::function<void()> temp = my_Queue.front();
        my_Queue.pop();
        my_Queue_mutex.unlock();
        temp();
    }
}

#endif