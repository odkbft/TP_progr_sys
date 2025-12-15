#include "enseash.h"

int main(void){
    char welcome[] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
    print(welcome);

    while(1){
        print("enseash %");
        exit(EXIT_SUCCESS);
    }
}
