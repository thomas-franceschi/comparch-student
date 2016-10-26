#include <stdio.h>

void func(){
    int x = 3;
    int y = 1;
    int z = x + y;

    while ( z > 0){
        z--;
    }
    return;
}

int main (void){
    func();
}