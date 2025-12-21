#include "enseash.h"
char buffer[MAX_LENGHT];
char * command[MAX_LENGHT];
struct timespec time_start;
struct timespec time_end;

int main(void){
    int pid, status=0;
    char converted_int_exit[MAX_LENGHT];
    char converted_int_signal[MAX_LENGHT];
    char converted_time_in_characters[MAX_LENGHT];
    
    print(WELCOME);                                                         //welcoming message

    while(1){
        print("enseash");
        
        if (WIFEXITED(status)){                                            
            int_to_ASCII(WEXITSTATUS(status), converted_int_exit);          //transform into char *
            print(" [exit:");
            print(converted_int_exit);                                      //print exit code
            print_time(time_start.tv_sec,time_start.tv_nsec,time_end.tv_sec,time_end.tv_nsec,converted_time_in_characters);
            print("] %");
        }

        else if (WIFSIGNALED(status)){
            int_to_ASCII(WTERMSIG(status), converted_int_signal);           //transform into char *
            print(" [sign:");
            print(converted_int_signal);                                    //print signal code
            print_time(time_start.tv_sec,time_start.tv_nsec,time_end.tv_sec,time_end.tv_nsec,converted_time_in_characters);
            print("] %");
        }

        read_function(buffer);

        separate_command(buffer,command);                                   //we separate each word of the buffer and we put them in a char ** command

        if (strncmp(buffer,"exit\0",MAX_LENGHT)==0){                        //if we type "exit" we go out the shell
            print("Bye bye ...\n");
            exit(EXIT_SUCCESS);
        }

        start_timer();                                                      //start the timer just before the son was born

        pid = fork();

        if (pid==-1){                                                       //fork error
            perror("Fork error");
            exit(EXIT_FAILURE);
        }
        else if (pid==0){                                                  //son process
            execvp(command[0], command);                                    //the execvp is supposed to replace the son process(the son become the command)
            //execvp take 2 arguments : the name of the command and the command and all the arguments.
            perror("excecvp error");                                        //if not it's an error
            exit(EXIT_FAILURE);
        }
        else if (pid>0){                                                    //father process
            wait(&status);                                                  //wait for the son to die
            end_timer();                                                    //end the timer when the son die (=end of the execlp)
        }                                                                   //when the son die restart the while loop

    }
}