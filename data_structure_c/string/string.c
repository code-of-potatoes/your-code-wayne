#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

int mystrlen(const char* str);
char* mystrcpy(char *dest, const char *src);
char* mystrdup(char* str);
char* mystrtok(char* str, const char* delim);  

int main()
{
    // strlen, strcpy, strdup
    /*
    char *words[100];
    char buf[BUFFER_SIZE];
    int n = 0;

    while(n<4 && scanf("%[^\n]%*c", buf) != EOF)
    {
        //words[n] = strdup(buf);
        words[n] = mystrdup(buf);
        n++;
    }

    for(int i=0; i < 4; i++)
    {
        printf("%s\n",words[i]);
    }
    */


    // strtok
    /*
        delimiter(구분 문자), 문자열 tokenizing = 구분 문자를 이용해 하나의 긴 문자열을 작은 문자열들로 자르는 것
        잘린 작은 문자열들을 보통 token이라 한다. 주로 strtok()을 이용
    */
    
    //char str[] = "now # is the time # to start preparing ### for the exam#";
    //char delim[] = "#";         
    char str[] = "   study hard,       or   sleep.     ";
    char delim[] = " ";       
    char* token;

/*
    printf("Before %s\n", str);
    token = strtok(str, delim);     // 원본 문자열의 delim문자 부분에 '\0'을 삽입함으로써 문자열에 변화를 준다. 그래서 보존해야하면 복사 후 실행해야 한다. 
                                    // 또한 원본 문자열은 string literal이 아닌 string array이여야 strtok을 사용할 수 있다.
                                    // 새로운 배열을 생성하지 않는다.

    while( token != NULL )
    {
        printf("next token is: %s:%ld\n", token, strlen(token));
        token = strtok(NULL, delim);
    }
    printf("After %s\n", str);
*/

    token = mystrtok(str, delim);     // 원본 문자열의 delim문자 부분에 '\0'을 삽입함으로써 문자열에 변화를 준다. 그래서 보존해야하면 복사 후 실행해야 한다. 
                                    // 또한 원본 문자열은 string literal이 아닌 string array이여야 strtok을 사용할 수 있다.
                                    // 새로운 배열을 생성하지 않는다.

    while( token != NULL )
    {
        printf("next token is: %s:%ld\n", token, strlen(token));
        token = mystrtok(NULL, delim);
    }


    return 0;
}


int mystrlen(const char* str)
{
    int len = 0;

    while(*str++)
    {
        len++;
    }

    return len;
}


char* mystrcpy(char *dest, const char *src)
{
    char* tmp = dest;

    while(*src)
    {
        *tmp++ = *src++;
    }

    *tmp = '\0';
    return dest;
}


char* mystrdup(char* str)
{
    char *p = (char *)malloc(sizeof(char)*(mystrlen(str)+1));
    if(p)   
        mystrcpy(p,str);

    return p;
}


char* mystrtok(char* str, const char* delim)
{
    static char* old = NULL;
    char*   token=NULL;

    if(!str)
    {
        if(!old)
            return NULL;
        str = old;
    }
        
    // token 시작점 탐색
    while(*str == *delim)
        str++;

    // 문자열의 끝인지 아닌지 판별
    if(*str == '\0')
    {
        old = NULL;
        return NULL;
    }
        
    token = str;
    // token의 끝 탐색
    while(*str != *delim)
    {
        if(*str == '\0')
        {
            old = str;
            return token;
        }    
        str++;
    }

    *str = '\0';
    old = str+1;
    return token;
}