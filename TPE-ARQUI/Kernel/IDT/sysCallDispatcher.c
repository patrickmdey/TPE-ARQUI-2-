#include <sysCallDispatcher.h>
#include <RTCTime.h>
#include <stringLib.h>
#include <lib.h>
#include <taskManager.h>
#include <keyboardDriver.h>
#include <videoDriver.h>
#include <timerTick.h>

#define SYS_GETMEM_ID 0
#define SYS_RTC_TIME_ID 1
#define SYS_TEMP_ID 2
#define SYS_WRITE_ID 3
#define SYS_GETCHAR_ID 4
#define SYS_CLEAR_ID 5
#define SYS_LOAD_APP_ID 6
#define SYS_RUN_ID 7
#define SYS_EXIT_ID 8
#define SYS_INFOREG_ID 9
#define SYS_DRAW 10
#define SYS_MOVE_CURSOR 11
#define SYS_MOVE_CURSOR_TO 12
#define SYS_CURRENT_CURSOR 13
#define SYS_TICKS_ELAPSED 14

#define SYSCALLS 14

uint64_t sysCallDispatcher(t_registers *r) {
      if (r->rax >= 0 && r->rax <= SYSCALLS){
            switch (r->rax) {
                  case SYS_GETMEM_ID:
                        sys_getMem(r->rdi,(uint8_t*)r->rsi);
                        break;

                  case SYS_RTC_TIME_ID:
                        return getDecimalTimeInfo((t_timeInfo)(r->rdi));
                        break;

                  case SYS_TEMP_ID:
                        return cpuTemp();
                        break;

                  case SYS_WRITE_ID:
                        sys_write((char *)(r->rdi), (uint8_t)(r->rsi), (t_colour)(r->rdx), (t_colour)(r->r10));
                        break;

                  case SYS_GETCHAR_ID:
                        if((int) (r->rdi) == 1)
                              return getcharOnce();
                        return getchar();
                        break;

                  case SYS_CLEAR_ID:
                        if((int)(r->rdi) == 0 && (int)(r->rsi)==0 && (int)(r->rdx)==0 && (int)(r->r10)==0)
                              clearScreen();
                        else
                              clearScreenFromTo((int)(r->rdi),(int)(r->rsi),(int)(r->rdx),(int)(r->r10));
                        break;

                  case SYS_LOAD_APP_ID:
                        return addProcess((t_PCB*)r->rdi);
                        break;

                  case SYS_RUN_ID:
                        sys_forceStart();
                        break;

                  case SYS_EXIT_ID:
                        killCurrentProcess();
                        break;

                  case SYS_INFOREG_ID:
                        return (uint64_t)getSnapshot();
                        break;
                  case SYS_DRAW:
                        draw((char *)(r->rdi), (t_colour)(r->rsi), (uint32_t)(r->rdx));
                        break;
                  case SYS_MOVE_CURSOR:
                        moveCursor((uint32_t) r->rdi, (uint32_t) r->rsi);
                        break;
                  case SYS_MOVE_CURSOR_TO:
                        moveCursorTo((uint32_t) r->rdi, (uint32_t) r->rsi);
                        break;
                  case SYS_CURRENT_CURSOR:
                        return (int *)cursorPosition();
                        break;
                  case SYS_TICKS_ELAPSED:
                        return ticksElapsed();
            }
      }
      return 0;
}