#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *buf[]={"/bin/sh",NULL};
void main(int argc, char *argv[])
{ 
    execve("/bin/sh",buf,0);
    exit(0);
}