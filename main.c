#include "alok.h"
#include <stdlib.h>
#include <stdio.h>
#include <mem.h>

int* batata;


int main(){
    initAllocator();
    char* batata = (char *) alok(sizeof(char) + 45000);
    printf("%d\n", batata);
    char* batata2 = (char *) alok(sizeof(char) + 100);
    printf("%d\n", batata2);
    delok(batata2);
    char* batata3 = (char *) alok(sizeof(char) + 20);
    printf("%d\n", batata3);
    //batata3 reusa a alocação que a batata2 usou e se livrou
    strcpy(batata, "oi");
    strcpy(batata3, "mano");
    printf("%s\n", batata);
    printf("%s\n", batata3);
    getchar();
    return 0;
}
