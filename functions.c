#include "enseash.h"

void print(char *str){
    int wrt = write(STDOUT_FILENO, str , strnlen(str,MAX_LENGHT));
    if (wrt==-1){
        perror("Write error");
        exit(EXIT_FAILURE);
    }
    else if (wrt<strnlen(str,MAX_LENGHT)){          //all the text is not write
        perror("Write error");
        exit(EXIT_FAILURE);
    }
}

void read_function(char *buffer){
    int rd=read(STDIN_FILENO,buffer,MAX_LENGHT);
    if (rd==-1){
        perror("Read error");
        exit (EXIT_FAILURE);
    }
    else if (rd==0){                             //When read return 0 it means EOF(end of file) as same as ctrl+d
        print("\nBye bye ...\n");                            
        exit (EXIT_SUCCESS);
    }
    else{                                        //because we read also the enter key \n
        buffer[rd-1]='\0';                        //so we need to replace the enter key \n by \0 which terminate the char
    }
}