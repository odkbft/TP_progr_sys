#define MAX_LENGHT 64    //nombre maximale de caractères de la commande

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