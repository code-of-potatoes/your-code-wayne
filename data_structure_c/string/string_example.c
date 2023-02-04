#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // isspace

#define MAX_STRING_LEN 21


int read_line(char str[], int limit);

// ex 1 : 개행문자를 제외한 문자열 받기
/*
int main()
{
    char buf[MAX_STRING_LEN];
    int len=0;
    while(1)
    {
        printf("$ ");

        //scanf("%[^\n]%*c",buf);
        len = read_line(buf,MAX_STRING_LEN);

        printf("%s:%ld\n",buf,len);

        fflush(stdin);
    }

    return 0;
}

int read_line(char str[], int limit)
{
    int ch, i=0;

    while((ch = getchar()) != '\n')
        if(i < (limit-1))
            str[i++] = ch;

    str[i]='\0';

    return i;
}
*/

// ex2 : 맨 앞과 뒤의 공백은 삭제, 문자 중간의 2개 이상 공백은 1개의 공백으로 만들어주기
int main()
{
    char buf[MAX_STRING_LEN];
    int len=0;
    while(1)
    {
        printf("$ ");

        //scanf("%[^\n]%*c",buf);
        len = read_line(buf,MAX_STRING_LEN);

        printf("%s:%ld\n",buf,len);

        fflush(stdin);
    }

    return 0;
}


int read_line(char str[], int limit)
{
    int ch, i=0;

    while((ch = getchar()) != '\n')
    {
        if( i < (limit-1) &&  (!isspace(ch) || i>0 && !isspace(str[i-1])) )
            str[i++] = ch;
    }

    if(i>0 && isspace(str[i-1]))
        i--;
    str[i]='\0';

    return i;
}