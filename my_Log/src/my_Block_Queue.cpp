#include "../include/my_Block_Queue.h"
#include <iostream>
block_Queue::block_Queue(int max_Size)
{
    if (max_Size <= 0)
        exit(-1);
    my_Max_Size = max_Size;
    my_Count = 0;
    my_Front = 0;
    my_Last = 0;
    my_Queue.reserve(max_Size);
}

bool block_Queue::Full()
{
    std::unique_lock<std::mutex> lck(my_Mutex);
    if (my_Count == my_Max_Size)
        return true;
    else
        return false;
}

std::string block_Queue::Front()
{
    my_Mutex.lock();
    if (my_Count == 0)
    {
        my_Mutex.unlock();
        return NULL;
    }
    std::string s = my_Queue[my_Front];
    my_Mutex.unlock();
    return s;
}

std::string block_Queue::Back()
{
    my_Mutex.lock();
    if (my_Count == 0)
    {
        my_Mutex.unlock();
        return NULL;
    }
    std::string s = my_Queue[my_Last];
    my_Mutex.unlock();
    return s;
}

bool block_Queue::push(std::string s)
{
    std::unique_lock<std::mutex> lock(my_Mutex);
    if (my_Count == my_Max_Size)
    {
        my_Mutex.unlock();
        my_Condition.notify_all();
        return false;
    }
    my_Last = (my_Last + 1) % my_Max_Size;
    my_Queue[my_Last] = s;
    my_Count++;
    lock.unlock();
    my_Condition.notify_all();
    return true;
}

std::string block_Queue::pop()
{
    std::unique_lock<std::mutex> lock(my_Mutex);
    while (my_Count == 0)
    {
        my_Condition.wait(lock);
    }
    std::string s = my_Queue[my_Front];
    my_Front = (my_Front + 1) % my_Max_Size;
    my_Count--;
    return s;
}

void block_Queue::clear()
{
    std::unique_lock<std::mutex> lock(my_Mutex);
    my_Count = 0;
    my_Front = 0;
    my_Last = 0;
    return;
}
