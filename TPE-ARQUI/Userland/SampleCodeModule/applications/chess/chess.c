#include <chess.h>
#include <chessLib.h>
#include <keys.h>
#include <lib.h>
#include <registers.h>
#include <stdint.h>
#include <stringLib.h>
#include <systemCalls.h>
#include <utils.h>

static void initChess(t_chessData * chessData);
static void processChar(char c, t_chessData * chessData);
static void chessText(t_chessData * chessData);

void runChess(){
      t_chessData chessData;
      initChess(&chessData);

      char c;
      int elapsed;
      while (1) {
            elapsed = syscall(GET_TICKS_ELAPSED,0,0,0,0,0,0);
            c = getcharOnce();
            if(!chessData.lost){
                if(elapsed % 18 == 0){
                      chessData.currentChrono->time++;
                      if(abs(chessData.currentChrono->time - chessData.nextChrono->time) >= 60){
                            chessData.lost = 1;
                            putchar('\n');
                            chessText(&chessData);
                            printStringWC(" You ran out of time! YOU LOSE -- Press any key to restart",BLACK,RED);
			    }
                      else {
                          int x, y;
                          cursorPosition(&x,&y);
                          moveCursorTo(chessData.currentChrono->x, chessData.currentChrono->y);
                          printString(chessData.currentPlayer);
                          printString(" > ");
                          chronoTime(chessData.currentChrono->time);
                          moveCursorTo(x,y);
                      }
                }
            }
            
            if(c != 0)
                  processChar(c,&chessData);
      }
      syscall(EXIT, 0, 0, 0, 0, 0, 0);
}

static void initChess(t_chessData * chessData){

      chessData->lost = 0;
      strcpy("PLAYER 1", chessData->player1);
      strcpy("PLAYER 2", chessData->player2);
      chessData->currentPlayer = chessData->player1;
      chessData->nextPlayer = chessData->player2;

      chessData->chrono1.time = 0;      //5 minutos
      chessData->chrono1.x = 700;
      chessData->chrono1.y = 45;
      chessData->currentChrono = &(chessData->chrono1);
      

      chessData->chrono2.time = 0;      //5 minutos
      chessData->chrono2.x = 700;
      chessData->chrono2.y = 72;
      chessData->nextChrono = &(chessData->chrono2);

      putchar('\n');
      
      setBoard(chessData);
      drawBoard(chessData);
      chessText(chessData);

}

static void processChar(char c, t_chessData * chessData) {
    int command;
      if (c != 0) {
            if(chessData->lost){
                  resetGame(chessData);
                  chessText(chessData);
                  return;
            }

            switch (c) {
                  case '\t':
                        syscall(CLEAR,0,0,0,0,0,0);
                        cleanBuffer(&chessData->buffer);
                        sys_changeApp();
                        drawBoard(chessData);
                        chessText(chessData);

                        break;
                  case CLEAR_SCREEN:
                        // syscall(CLEAR,0,0,0,0,0,0);
                        // cleanBuffer(&chessData->buffer);
                        // chessText(chessData);
                        break;
                  case '\n':
                        command = processCommand(chessData);
                        if(command == 0) {                        //COMANDO INVALIDO
                            putchar('\n');
                            chessText(chessData);
                            printString("Invalid command");
                            moveCursor(-(strlen("Invalid command"))*8,-16);
                            int aux = (strlen(chessData->buffer.buffer)+1);
                            for(int i = 0;i<aux;i++)
                                putchar(' ');
                            moveCursor(-aux*8,0);
				}
                        else if (command ==1){                    //COMANDO VALIDO
                            char *aux = chessData->currentPlayer;
                            chessData->currentPlayer = chessData->nextPlayer;
                            chessData->nextPlayer = aux;

                            t_chrono *auxChrono = chessData->currentChrono;
                            chessData->currentChrono = chessData->nextChrono;
                            chessData->nextChrono = auxChrono;
                            cleanChessScreen(chessData);
                            drawBoard(chessData);
                            chessText(chessData);
                        }
                        else{
                            chessData->lost = 1;
                            cleanChessScreen(chessData);
                            drawBoard(chessData);
                            chessText(chessData);
                            printStringWC(" YOU WIN -- Press any key to restart",BLACK,GREEN);
                        }

                        cleanBuffer(&chessData->buffer);
                        
                        break;
                  case '\b':
                        if (chessData->buffer.index > 0) {
                              chessData->buffer.buffer[--chessData->buffer.index] = 0;
                              deletechar();
                        }
                        break;
                  case 'r':         //FALTA VER QUE LAS LOS MOVIMIENTOS FUNCIONEN
                        rotateBoard(chessData);
                        cleanChessScreen(chessData);
                        drawBoard(chessData); 
                        chessText(chessData);
                        break;

                  default:
                        if (chessData->buffer.index < BUFFER_SIZE) {
                              chessData->buffer.buffer[chessData->buffer.index++] = c;
                              putchar(c);
                        }
            }

      }
}

//muestra en pantalla el texto para ingresar comando
static void chessText(t_chessData * chessData) {
      printStringWC(chessData->currentPlayer, BLACK, WHITE);
      printStringWC(" $ > ", BLACK, WHITE);
}





// "
// ______________\n
// ______________\n
// ______________\n
// ______________\n
// _____XXXX_____\n
// ____XXXXXX____\n
// _____XXXX_____\n
// ___XXXXXXXX___\n
// _____XXXX_____\n
// _____XXXX_____\n
// _____XXXX_____\n
// ____XXXXXX____\n
// __XXXXXXXXXX__\n
// ______________
// "

// "
// ______________\n
// ______________\n
// _XXX__XX__XXX_\n
// _XXX__XX__XXX_\n
// _XXX__XX__XXX_\n
// _XXXXXXXXXXXX_\n
// ___XXXXXXXX___\n
// ___XXXXXXXX___\n
// ___XXXXXXXX___\n
// ___XXXXXXXX___\n
// ___XXXXXXXX___\n
// _XXXXXXXXXXXX_\n
// _XXXXXXXXXXXX_\n
// ______________
// "



// "_____________\n
// ___XX__XXX____\n
// _XXXXXXXXXXX__\n
// XXXXXXXXX_XXX_\n
// XXXXXX_XXXXXXX\n
// XXXXXX___XXXXX\n
// XXXXXXXX______\n
// _XXXXXXXXX____\n
// __XXXXXXXXX___\n
// __XXXXXXXXXX__\n
// _XXXXXXXXXXXX_\n
// _XXXXXXXXXXXX_\n
// _XXXXXXXXXXXX_\n
// ______________
// "
    
// "
// ______________\n
// _______X______\n
// _____XXXX_____\n
// ____X_XXXX____\n
// ___XXX_XXXX___\n
// ____XXX_XX____\n
// ______XX______\n
// ______XX______\n
// _____XXXX_____\n
// _____XXXX_____\n
// ___XXXXXXXX___\n
// ___XXXXXXXX___\n
// __XXXXXXXXXX__\n
// ______________
// "

// "
// ______XX______\n
// _____XXXX_____\n
// ______XX______\n
// ____XXXXXX____\n
// ___X_XXXX_X___\n
// ____XXXXXX____\n
// ______XX______\n
// ______XX______\n
// _____XXXX_____\n
// _____XXXX_____\n
// ____XXXXXX____\n
// ___XXXXXXXX___\n
// __XXXXXXXXXX__\n
// ______________
// "
// "
// ______________\n
// ______XX______\n
// ____XXXXXX____\n
// ______XX______\n
// ___XXXXXXXX___\n
// ____X_XX_X____\n
// _____XXXX_____\n
// ______XX______\n
// _____XXXX_____\n
// _____XXXX_____\n
// ___XXXXXXXX___\n
// ___XXXXXXXX___\n
// __XXXXXXXXXX__\n
// ______________
// "