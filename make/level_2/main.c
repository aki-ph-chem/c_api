#include <stdio.h>
#include "add.h"
#include "greet.h" 

int main(void) {
    greet("Aki");

    int x = 1100;
    int y = 11;
    printf("x + y = %d\n"
            ,add(x,y));
}
