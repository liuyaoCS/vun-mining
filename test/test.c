#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char* argv[]){
    int i;
    char* ptr = getenv(argv[1]);
    printf("%s will be at %p\n", argv[1], ptr);
}