#include "enseash.h"
extern struct timespec time_start;
extern struct timespec time_end;

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
    reverse(s);                  //reverse all the digits
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

void start_timer(void){                                 //start the timer and save the value in the struct time_start
    if (clock_gettime(CLOCK, &time_start)==-1){            
        perror("Clock error");
        exit(EXIT_FAILURE);
    }
}

void end_timer(void){                                   //end the timer and save the value in the struct time_end
    if (clock_gettime(CLOCK, &time_end)==-1){           
        perror("Clock error");
        exit(EXIT_FAILURE);
    }
}

int time_calculation(int time_start_s,int time_start_ns,int time_end_s,int time_end_ns){
    int delta_s = time_end_s - time_start_s;                            //difference of the seconds of the time
    int delta_ns = time_end_ns - time_start_ns;                         //difference of the ns of the time

    if (delta_ns < 0) {                                                 //example if start_time is 2s and 600 000 000 ns and end_time is 4s and 100 000 000 ns
        delta_s = delta_s - 1;                                          //delta_ns=-500 000 000 and delta_s=2s
        delta_ns = delta_ns + 1000000000;                               //delta_s become 1s and delta_ns become 500 000 000 ns (1 000 000 000 ns = 1s)
    }       

    int total_ms = (delta_s * 1000) + (delta_ns / 1000000);             //conversion of delta_s in ms and delta_ns in ms
    return total_ms;
}

void print_time(int time_start_s,int time_start_ns,int time_end_s,int time_end_ns,char * converted_time_in_characters){
    int_to_ASCII(time_calculation(time_start_s,time_start_ns,time_end_s,time_end_ns),converted_time_in_characters);      //conversion of the total_ms (difference in ms) in a character string and stock this string in the var converted_time_in_characters                        
    print("|");
    print(converted_time_in_characters);           
    print("ms");
}