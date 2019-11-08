#include<stdio.h>
#include<string.h>

int main(void)
{
        while(1){
                char input[30];
                printf(">> ");
                scanf("%s", input);
                if(!strcmp(input, "ls")){     // 입력값이 "ls"인 경우
                        printf("ls 실행");
                }
        }
        return 0;
}
