#pragma once

#include <stdio.h>
#include <time.h>

#define TIME_SOLUTION(sol)                                                   \
        {                                                                    \
                double t = 0.0;                                              \
                for (int i = 0; i < 10000; i++) {                            \
                        double startTime = (double)clock() / CLOCKS_PER_SEC; \
                        sol();                                               \
                        double endTime = (double)clock() / CLOCKS_PER_SEC;   \
                        double timeElapsed = endTime - startTime;            \
                        t += timeElapsed;                                    \
                }                                                            \
                t /= 10000;                                                  \
                printf("Took %f ms\n", t * 1000);                            \
        };
