﻿/*
 * sample_task_with_lambda.cpp
 *
 *  Created on: 2014年5月19日
 *      Author: owent
 *
 *  Released under the MIT license
 */


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <inttypes.h>
#include <stdint.h>
#include <vector>

// include manager header file
#include <libcotask/task.h>

#if defined(COTASK_MACRO_ENABLED) && defined(__cplusplus) && (__cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1600))

typedef cotask::task<> my_task_t;

int main(int argc, char *argv[]) {
    int test_code = 128;

    // create a task using lambda expression
    my_task_t::ptr_t first_task = my_task_t::create([&]() {
        puts("|first task running and will be yield ...");
        cotask::this_task::get_task()->yield();
        puts("|first task resumed ...");
        printf("test code already reset => %d\n", ++test_code);
    });

    // add many next task using lambda expression
    first_task
        ->next([=]() {
            puts("|second task running...");
            printf("test code should be inited 128 => %d\n", test_code);
        })
        ->next([&]() {
            puts("|haha ... this is the third task.");
            printf("test code is the same => %d\n", ++test_code);
            return "return value will be ignored";
        })
        ->next([&]() {
            puts("|it's boring");
            printf("test code is %d\n", ++test_code);
            return 0;
        });

    test_code = 0;
    // start a task
    first_task->start();
    first_task->resume();

    // these code below will failed.
    first_task->next([]() {
        puts("this will never run.");
        return 0;
    });

    printf("|task start twice will failed: %d\n", first_task->start());
    printf("|test_code end with %d\n", test_code);
    return 0;
}
#else
int main() {
    puts("this sample require cotask enabled and compiler support c++11");
    return 0;
}
#endif
