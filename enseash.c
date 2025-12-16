#include "enseash.h"
char buffer[MAX_LENGHT];

int main(void){
    int pid, status;
    
    char welcome[] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
    print(welcome);
    while(1){
        print("enseash %");
        pid = fork();

        if (pid==-1){                    //fork error
            perror("Fork error");
            exit(EXIT_FAILURE);
        }
        else if (pid==0){                //son process
            read_function(buffer);
            execlp(buffer, buffer, (char *) NULL);          //the execlp is supposed to replace the son process(the son become the command)
            perror("exceclp error");                        //if not it's an error
            exit(EXIT_FAILURE);
        }
        else if (pid>0){                //father process
            wait(&status);              //wait for the son to die
        }                               //when the son die restart the while loop

    }
}
