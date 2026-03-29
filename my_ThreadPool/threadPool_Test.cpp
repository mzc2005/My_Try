#include <iostream>
#include <unistd.h>
#include "./include/my_ThreadPool.h"

using namespace std;

void a(int i)
{
    cout << "a:" << i << endl;
}

void b(int i)
{
    cout << "b:" << i << endl;
}

int main()
{
    ThreadPool *pool = new ThreadPool;
    bool ret;
    for (int i = 0; i < 10000;)
    {
        ret = pool->Append_Task([i]()
                                { a(i); });
        i++;
        ret = pool->Append_Task([i]()
                                { b(i); });
        i++;
    }
    sleep(10);
}