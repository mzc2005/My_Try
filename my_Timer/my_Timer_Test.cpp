#include <iostream>
#include "./include/my_Timer.h"

void my_cb_func(client_data* data)
{
    static int count = 0;
    cout << "我是第" << count++ << "个" << endl;
}

void show(sort_timer_lst* my_list)
{
    
}

int main()
{
    sort_timer_lst* my_Timer_List = new sort_timer_lst;

    util_timer* a = new util_timer;
    a->cb_func = my_cb_func;

}