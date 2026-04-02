#ifndef BLOCK_QUEUE_H
#define BLOCK_QUEUE_H

#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <string>

class block_Queue
{
public:
    block_Queue(int max_Size = 1000);
    ~block_Queue();
 
    bool Full(); //查看阻塞队列是否已满
    std::string Front();  //返回队列的首元素，失败返回NULL
    std::string Back();   //返回队列队尾元素，失败返回NULL
    bool push(std::string s); 
    std::string pop();    //弹出队首元素，失败返回NULL
    void clear();

private:
    int my_Max_Size;
    int my_Count;  //当前队列中元素数量
    int my_Front;  //队列首元素下标
    int my_Last;   //队尾元素下标
    std::mutex my_Mutex;
    std::condition_variable my_Condition;
    std::vector<std::string> my_Queue;

};
#endif