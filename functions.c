#include "enseash.h"


void print(char *str){
    int wrt = write(STDOUT_FILENO, str , strnlen(str,MAX_LENGHT));
    if (wrt==-1){
        perror("Write error");
        exit(EXIT_FAILURE);
    }
    else if (wrt<strnlen(str,MAX_LENGHT)){        //all the text is not write
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
        buffer[rd-1]='\0';                       //so we need to replace the enter key \n by \0 which terminate the char *
    }
}


void int_to_ASCII(int n, char s[]){    //source : https://en.wikibooks.org/wiki/C_Programming/stdlib.h/itoa
    int i, sign;
 
    if ((sign = n) < 0)  
        n = -n;                  //if n is negative it become positive (absolute value)
    i = 0;
    do {       
        s[i++] = n % 10 + '0';   //take the last digit of the number (if its 123 it will be 3) and add it to the table with the next index
    } while ((n /= 10) > 0);     //make a loop with a duration of the number of digits (for example 123 will be 3 loops)
    if (sign < 0){               //if n was negative at first just add a negative sign(-) at the end (he will be at the beginning when we will reverse)
       s[i++] = '-';
    }
    s[i] = '\0';                 //add the character to end
     everse(s);                  //reverse all the digits
}


void reverse(char s[]){         //function that reverse all the characters (the first become the last and ...)
    int i, j;
    char c;
 
    for (i = 0, j = strnlen(s,MAX_LENGHT)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}