## Autores
- [Francisco Bernad](https://github.com/FrBernad)
- [Nicolás Rampoldi](https://github.com/NicolasRampoldi) 
- [Patrick Dey](https://github.com/patrickmdey)

# Manual de usuario

1. Ingresar a la carpeta ***"Toolchain"*** y ejecutar el comando `make all`.

2. En la carpeta principal, ejecutar el comando `make all`.

3. Ejecutar el programa mediante terminal ingresando `./run.sh`.

Una vez ejecutado el programa, se abrirá una ventana con una pantalla dividida en dos. Por defecto se encontrará en la mitad derecha, donde se estará ejecutando la ***shell***. Para acceder a la ***calculadora*** e intercambiar pantallas, basta con presionar la tecla ***tab***.


## Shell

La shell brinda una variedad de comandos, lo cuales son ejecutados al escribir su nombre y presionar ***enter***.
Los comandos son los siguientes:

- ***help:*** muestra la lista de comandos y la descripción de cada uno.
- ***inforeg:*** imprime en pantalla el valor de los registros del programa en cierto momento, para actualizar dicho valor presionar ctrl + s.
- ***time:*** imprime en pantalla el tiempo actual del sistema.
- ***cpuInfo:*** imprime en pantalla el modelo y vendedor del CPU. 
- ***cpuTemp:*** imprime en pantalla la temperatura actual del CPU. 
- ***printmem:*** dump de 32 bytes de memoria a partir de la dirección hexadecimal pasada como parámetro. 
- ***checkZeroException:*** causa una excepción de división por cero. 
- ***checkInvalidOpCodeException:*** causa una excepción de código de operación inválido.
- ***changeUsername:*** cambia el nombre del usuario de la shell al pasado como parámetro.
- ***showArgs:*** imprime en pantalla los argumentos del comando.


## Calculadora

La calculadora realiza operaciones aritméticas con una ***sintaxis específica***. Las reglas son las siguientes:

1. Los operadores y operandos deben estar ***separados por espacios*** (si se quiere denotar un número como negativo se permite también poner el ‘-’ pegado al número. ej: -1.2 +  2).

2. No tomará caracteres que ***no*** sean ***dígitos***, ***espacios***, ***puntos***, ***parentesis*** u ***operadores*** (‘+’, ‘-’, ‘*’, ‘%’, o ‘=’).

3. Una vez ingresada la expresión se debe presionar ***'='*** y el resultado de la expresión será impreso en pantalla.

***Ejemplo:***  ( 2.5 * 536 ) - 25 =

## Syscalls

***int 80h***

| %rax | System Call | %rdi             | %rsi              | %rdx              | %r10                | %r8 | %r9 |
| ---- | ----------- | ---------------- | ----------------- | ----------------- | ------------------- | --- | --- |
| 0    | sys_getMem  | uint64_t memDir  | uint64_t* memData |                   |                     |     |     |
| 1    | sys_rtcTime | t_timeInfo tInfo |                   |                   |                     |     |     |
| 2    | sys_temp    |                  |                   |                   |                     |     |     |
| 3    | sys_write   | char * string    | uint8_t length    | t_colour bgColour | t_colour fontColour |     |     |
| 4    | sys_getchar |                  |                   |                   |                     |     |     |
| 5    | sys_clear   |                  |                   |                   |                     |     |     |
| 6    | sys_loadApp | t_PCB * app      |                   |                   |                     |     |     |
| 7    | sys_run     |                  |                   |                   |                     |     |     |
| 8    | sys_exit    |                  |                   |                   |                     |     |     |
| 9    | sys_inforeg |                  |                   |                   |                     |     |     |

***int 81h***

| %rax | System Call   | %rdi | %rsi | %rdx | %r10 | %r8 | %r9 |
| ---- | ------------- | ---- | ---- | ---- | ---- | --- | --- |
| 0    | sys_changeApp |      |      |      |      |     |     |