#include<stdio.h>
#include<string.h>

/* static을 사용하면 이 함수는 fseek.c에서만 사용가능 -> 이렇게 하면 같은 이름을 가진 함수를 파일마다 만들 수 있음
 원래 한 프로젝트에 aa.c와 fseek.c가 있다고 할 때 두 C파일에서 같은 함수의 이름을 정의할 수 X -> 컴파일 에러남 */
static int create_file(void)
{
        FILE * fp = fopen("pooh_file", "w");
        if(fp == NULL){     // fopen() 함수 실패하는 경우
                perror("fopen() fail\n");
                return -1;
        }

        printf("after fopen(). now offset=%ld\n", ftell(fp));   /* ftell이 long형이기 때문에 %ld -> 맨 처음상태이기 때문에 위치는 시작점인 0
        ftell함수는 파일 시작에서부터 현재 위치까지의 바이트 수를 알려주는 함수이다. */

        fputs("hello world\n", fp);     // pooh_file에 hello world 넣기(write), 단어 수 : 12(띄어쓰기 : 1, 개행문자('\n') : 1)
        fputs("hello world!\n", fp);    // 단어 수 : 13
        fputs("hello world!!\n", fp);   // 단어 수 : 14
        printf("after fputs, before fclose(). now offset=%ld\n", ftell(fp));     // ftell(fp)=39가 나오는데 이는 12+13+14=39
        printf("-----------------------------------------------\n\n");

        fclose(fp);
        return 0;
}

static int read_file(void)
{
        char buf[30];
        FILE * fp = fopen("pooh_file", "r+");    // r+는 read/write 모두 가능
        if(fp == NULL){     // fopen() 함수 실패하는 경우
                perror("fopen() fail\n");
                return -1;
        }

        printf("after fopen(). now offset=%ld\n", ftell(fp));   // 시작점이므로 위치 = 0
        //printf("now pointer=0x%p\n", fp);

        fgets(buf, sizeof(buf), fp);    /* sizeof(buf)라서 30만큼을 읽을 것 같지만 'hello world\n', 즉, 개행문자가 와서 이후의 문자들은 읽어들이지 않음
        주의 : fp는 fgets함수에 의해 buf를 가리키는 것 X, 파일은 파일대로 sizeof(buf)만큼 읽어들여져서 ftell(fp)=12이고 buf는 buf대로 sizeof(buf)만큼 읽어들인 문자들을 buf에 저장
        -> 포인터값 찍어보면 그대로이다. -> printf("now pointer=0x%p\n", fp); */
        // printf("after fgets(). now pointer=0x%p\n", fp);
        printf("after fgets(). now offset=%ld\n", ftell(fp));   // 그래서 ftell(fp)=12

        fseek(fp, 0, SEEK_END);
        /* 첫 번째 인자값 : 열린 파일 포인터
           두 번째 인자값 : 위치 값(양수/음수, 0 모두 가능)
           세 번째 인자값 : 1. SEEK_SET : 파일의 시작 기준
                          2. SEEK_END : 파일의 끝 기준
                          3. SEEK_CUR : 현재 파일 포지션의 기준
           성공 시 offset(위치)값 반환, 실패 시 -1 반환 */
        printf("after fseek(). now offset=%ld\n", ftell(fp));  // 위치값 0(시작부분)에서부터 SEEK_END(파일 끝)까지이므로 ftell(fp)=39

        fputs("linux\n", fp);   // 단어 수 6만큼 추가
        printf("after fputs, before fclose(). now offset=%ld\n", ftell(fp));     // ftell(fp)=39+6=45
        printf("-----------------------------------------------\n");

        fclose(fp);
        return 0;
}

int main(int argc, char **argv)
{
        create_file();
        read_file();
        return 0;
}