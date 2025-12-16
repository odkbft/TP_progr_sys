#define MAX_LENGHT 64                                                               //Maximal number of charcater by command
#define welcome "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"     //welcome message

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void print(char *str);
void read_function(char *buffer);
void int_to_ASCII(int n, char s[]);
void reverse(char s[]);