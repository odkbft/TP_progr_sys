#define MAX_LENGHT 64                                                               //Maximal number of charcater by command
#define WELCOME "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"     //welcome message
#define CLOCK CLOCK_MONOTONIC                                                       //clock used

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
void start_timer(void);
void end_timer(void);
int time_calculation(int time_start_s,int time_start_ns,int time_end_s,int time_end_ns);
void print_time(int time_start_s,int time_start_ns,int time_end_s,int time_end_ns,char * converted_time_in_characters);