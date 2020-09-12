#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 24
#define LINELEN 512
/** 
 * 优化方案：从标准输入中读入要分页的数据，直接从键盘读用户的输入 
 * 有一个文件 /dev/tty 这是键盘和显示器的设备描述文件，向这个文件 写 相当于显示在用户的屏幕上， 读 相当于从键盘获取用户的输入
 * `ls /bin | ./more02` : more有两个输入 ：1.程序的标准输入是ls的输出 2. 用户的输入，从/dev/tty得到数据
 */
int see_more(FILE *cmd){
    int c ;
    printf("\033[7m more? \033[m");

    while( (c=getc(cmd)) != EOF ){
        if(c == 'q'){
            return 0;
        }

        if(c == ' '){
            return PAGELEN;
        }

        if(c == '\n'){
            return 1;
        }
    }

    return 0;

}

void do_more(FILE *fp){
    char line[LINELEN];
    int num_of_lines = 0;
    int see_more(FILE *) ,reply;

    /* 对/dev/tty 读用户输入 */
    FILE *fp_tty;

    /*CMD stream*/
    fp_tty = fopen("/dev/tty","r");

    if(fp_tty == NULL){
        exit(1);
    }

    while(fgets(line ,LINELEN,fp)){
        if(num_of_lines == PAGELEN){
            reply = see_more(fp_tty);
            if(reply == 0){
                break;
            }

            num_of_lines -= reply;
        }

        /* 显示一行 */
        if(fputs(line,stdout) == EOF){
            exit(1);
        }

        num_of_lines++;

    }


}


int main(int ac ,char *av[]){
    
    FILE *fp;

    if(ac == 1){
        do_more(stdin);
    }else{

        while(--ac){

            if( (fp=fopen(*++av ,"r")) != NULL ){

                do_more(fp);
                fclose(fp);

            }else{

                exit(1);

            }

        }
    }

    return 0;

}

