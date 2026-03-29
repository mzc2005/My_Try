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
#endif