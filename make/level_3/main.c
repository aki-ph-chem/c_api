#include <stdio.h>
#include <greet.h> 
#include <add.h>

int main(void) {
    greet("Aki");
    int x = 1100;
    int y = 11;
    printf(" x + y = %d\n"
            ,add(x,y));
}
