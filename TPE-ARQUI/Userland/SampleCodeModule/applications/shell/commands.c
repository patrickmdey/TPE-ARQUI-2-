#include <commands.h>
#include <RTCTime.h>
#include <cpuInfo.h>
#include <lib.h>
#include <stringLib.h>
#include <systemCalls.h>
#include <utils.h>
#include <chess.h>

static void memToString(char* buffer, uint8_t* mem, int bytes);

void changeToChess(int argc, char** args, t_shellData* shellData){
      syscall(CLEAR,0,0,0,0,0,0);
      cleanBuffer(&shellData->buffer);
      sys_changeApp();
}

//devuelve el tiempo acutal del sistema
void time(int argc, char** args, t_shellData* shellData) {
      if (argc != 0) {
            printStringLn("Invalid ammount of arguments.");
            putchar('\n');
            return;
      }
      
      char dateFormat[3][3];

      uint8_t day = syscall(RTC_TIME,DAY,0,0,0,0,0);
      uint8_t month = syscall(RTC_TIME,MONTH,0,0,0,0,0);
      uint8_t year = syscall(RTC_TIME,YEAR,0,0,0,0,0);
      char aux[9] = {0};
      getCurrentTime(aux);
      printString(" >Current time: ");
      printString(aux);
      putchar('\n');
      printString(" >Current date: ");
      intToStr(day, dateFormat[0], 2);
      intToStr(month, dateFormat[1], 2);
      intToStr(year, dateFormat[2], 2);

      for (int i = 0; i < 3; i++) {
            printString(dateFormat[i]);
            if (i != 2) {
                  putchar('/');
            }
      }
      putchar('\n');
}

//devuelve el modelo y vendedor del cpu
void cpuInfo(int argc, char** args, t_shellData* shellData) {
      if (argc != 0) {
            printStringLn("Invalid ammount of arguments.");
            putchar('\n');
            return;
      }
      char vendor[13] = {0};
      t_cpuInfo cpuInfo = {vendor, 0};
      cpuVendor(cpuInfo.cpuVendor);
      cpuInfo.model = cpuModel();
      printString(" > CPU Vendor: ");
      printStringLn(cpuInfo.cpuVendor);
      printString(" > CPU model: ");
      printInt(cpuInfo.model);
      putchar('\n');
      putchar('\n');
}

//Hace un dump de 32 bytes de memria a partir de la direccion pedida
void printmem(int argc, char** args,  t_shellData* shellData) {
      if (argc != 1) {
            printStringLn("Invalid ammount of arguments.");
            putchar('\n');
            return;
      }

      int error = 0;
      uint64_t memDir = strToHex(args[0], &error);
      if (error) {
            printStringLn("Invalid argument for function printmem (must be a hex value).");
            putchar('\n');
            return;
      }

      int bytes = 32;

      uint8_t memData[bytes];
      syscall(GET_MEM, memDir,(uint64_t)memData, 0, 0, 0, 0);

      char byteStr[bytes * 2];
      memToString(byteStr, memData, bytes);

      printString(" >Data dump:");
      for (int i = 0; i < 32; i++) {
            if (i % 4 == 0) {
                  putchar('\n');
                  printString("   -[0x");
                  printHex(memDir);
                  printString("]: ");
                  memDir += 4;
            }
            if (i % 2 == 0) {
                  putcharWC(byteStr[i], BLACK, BLUE);
                  putcharWC(byteStr[i + 1], BLACK, BLUE);
                  putchar(' ');
            } else {
                  putchar(byteStr[i]);
                  putchar(byteStr[i + 1]);
                  putchar(' ');
            }
      }
      putchar('\n');
      putchar('\n');
}

//Imprime la temperatura actual del cpu
void cpuTemp(int argc, char** args, t_shellData* shellData) {
      if (argc != 0) {
            printStringLn("Invalid ammount of arguments.");
            putchar('\n');
            return;
      }
      printString("CPU temp: ");
      printInt(syscall(TEMP, 0, 0, 0, 0, 0, 0));
      printStringLn(" C");
      putchar('\n');
}

//causa una excepcion de dividir por cero
void checkZeroException(int argc, char** args, t_shellData* shellData) {
      if (argc != 0) {
            printStringLn("Invalid ammount of arguments.");
            putchar('\n');
            return;
      }
      int a = 0;
      int b = 20 / a;
      if (b == 0) {
      }
}

//causa una excepcion de tipo invalid opcode
void checkInvalidOpcodeException(int argc, char** args, t_shellData* shellData) {
      if (argc != 0) {
            printStringLn("Invalid ammount of arguments.");
            putchar('\n');
            return;
      }
      __asm__("ud2");  // https://hjlebbink.github.io/x86doc/html/UD2.html
}

//Muestra los argumentos pasados al comando
void showArgs(int argc, char** args, t_shellData* shellData) {
      for (int i = 0; i < argc && i < MAX_ARGS; i++) {
            printString("arg[");
            printInt(i);
            printString("]=");
            printStringLn(args[i]);
      }
      putchar('\n');
}

static void memToString(char* buffer, uint8_t* mem, int bytes) {
      for (int i = 0; i < bytes * 2; i++) {
            if (mem[i] <= 0xF) {
                  buffer[i] = '0';
                  uintToBase(mem[i], buffer + i + 1, 16);
            } else {
                  uintToBase(mem[i], buffer + i, 16);
            }
      }
}
