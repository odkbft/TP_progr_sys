#include "enseash.h"
extern struct timespec time_start;
extern struct timespec time_end;

void print(char * str){
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

void separate_command(char * buffer,char ** command){                   //The goal of this function is to split our command in a char**.
                                                                        //So buffer='hostname -i' will become command[0]='hostname', command[1]='-i' and command[2]=NULL.
    int length_command = strnlen(buffer, MAX_LENGHT);                   
    int index_of_words=0;
    int indix_letters_current_word=0;
    char current_word[MAX_LENGHT];                                      //it's the current word we are manipuling. For 'hostname -i' it can be 'hostname' or '-i'

    for (int i = 0; i < length_command; i++) {                          //we make a loop on each character of the buffer
        if (buffer[i]==' '){
            current_word[indix_letters_current_word]='\0';              //if we have a space character we end the current word by adding '\0' at the end
            command[index_of_words]=strndup(current_word, MAX_LENGHT);  //we have to use strndup because we can't just use command[count]=current_word because it give the adress of current_word and it will be erease after 
            //https://stackoverflow.com/questions/9210528/split-string-with-delimiters-in-c and we cant just use strtok() because its forbidden in the instructions so we need to use strndup() (and not strdup()) 
            //to create a new image of current_word
            index_of_words=index_of_words+1;                            //when we have a space we need to increase the index of words because we have a new word                                    
            indix_letters_current_word=0;                               //we also have to reset the index of the current word
        }
        else{
            current_word[indix_letters_current_word]=buffer[i];         //if we don't have space character so we are always in the same word and we can juste add the current character of the buffer to the current word
            indix_letters_current_word=indix_letters_current_word+1;    //and we also increase the index of the current word
        }
    }
    current_word[indix_letters_current_word]='\0';                      //at the end we do not have append the last word (because there is no space at the end) so we finish him with a '\0'
    command[index_of_words]=strndup(current_word, MAX_LENGHT);          //and we add it
    command[index_of_words+1] = NULL;                                   //we don't forget to add the NULL in the command
}
