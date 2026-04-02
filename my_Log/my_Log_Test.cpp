#include <iostream>
#include "include/my_Log.h"
#include <thread>
#include <unistd.h>

void flu()
{
    while (true)
    {
        Log::get_instance()->flush();
        cout << "flush" << endl;
        sleep(10);
    }
}

int main(void)
{
    Log::get_instance()->init("MyLog", 0, 8192, 50000000, 100);
    int m_close_log = 0;

    std::thread t1(flu);
    t1.detach();

    while (true)
    {
        string s;
        std::cin >> s;
        LOG_INFO("123INFO");
        LOG_ERROR("123ERROR");
        LOG_DEBUG("123DEBEG");
        LOG_WARN("123WARN");
        LOG_INFO(s.c_str());
        LOG_INFO("\n");
    }
    return 0;
}