
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <thread> // POSIX 中的 pthread.h

#include <gtest/gtest.h>

// 函数 f() 做一些耗时的工作
int f(void* thr_data) // POSIX 中返回 void*
{
    volatile double d = 0;
    for (int n=0; n<10000; ++n)
       for (int m=0; m<10000; ++m)
           d += d*n*m;
    return 0;
}

TEST(CHRONO, CLOCK){
    clock_t t1 = clock();

    thrd_t thr1, thr2;  // C11 ；POSIX 中用 pthread_t
    thrd_create(&thr1, f, NULL); // C11 ； POSIX 中用 pthread_create
    thrd_create(&thr2, f, NULL);
    thrd_join(thr1, NULL); // C11 ； POSIX 中用 pthread_join
    thrd_join(thr2, NULL);

    clock_t t2 = clock();

    double dur = 1000.0*(t2-t1)/CLOCKS_PER_SEC;

    printf("CPU time used (per clock(): %.2f ms\n", dur);
}