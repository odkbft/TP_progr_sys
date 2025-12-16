#include "enseash.h"
char buffer[MAX_LENGHT];

int main(void){
    int pid, status;
    
    print(welcome);
    
    while(1){
        print("enseash %");

        read_function(buffer);
        if (strncmp(buffer,"exit\0",MAX_LENGHT)==0){
            print("Bye bye ...\n");
            exit(EXIT_SUCCESS);
        }

        pid = fork();

        if (pid==-1){                    //fork error
            perror("Fork error");
            exit(EXIT_FAILURE);
        }
        else if (pid==0){                                       //son process
            execlp(buffer, buffer, (char *) NULL);          //the execlp is supposed to replace the son process(the son become the command)
            perror("exceclp error");                        //if not it's an error
            exit(EXIT_FAILURE);
        }
        else if (pid>0){                //father process
            wait(&status);              //wait for the son to die
        }                               //when the son die restart the while loop

    }
}