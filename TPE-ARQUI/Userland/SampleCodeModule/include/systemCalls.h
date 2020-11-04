#ifndef SYSTEM_CALLS
#define SYSTEM_CALLS

//dataTypes
#include <RTCTime.h>
#include <taskManager.h>
#include <colours.h>
#include <cpuInfo.h>
#include <stdint.h>

typedef enum{
    GET_MEM = 0,
    RTC_TIME = 1,
    TEMP = 2,
    WRITE = 3,
    GETCHAR = 4,
    CLEAR = 5,
    LOAD_APP = 6,
    RUN = 7,
    EXIT = 8,
    INFOREG = 9,
    DRAW = 10,
    MOVE_CURSOR = 11,
    MOVE_CURSOR_TO = 12,
    CURSOR_POSITION = 13,
    GET_TICKS_ELAPSED = 14
}syscallID;

uint64_t syscall(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9);
void sys_changeApp();

#endif