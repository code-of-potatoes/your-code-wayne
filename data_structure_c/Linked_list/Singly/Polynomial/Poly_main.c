/*
    Polynomial program
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Polynomial.h"

#define BUFFER_LEN 50

int read_line(FILE* fp, char*, int limit);
void erase_blanks(char* expression);
void handdle_print(char name);
void handdle_calc(char name, char* px);
void handdle_definition(char* expression);

void process_command();



int main()
{
    process_command();
    destroy_all();
    
    return 0;
}

int read_line(FILE* fp ,char str[], int limit)
{   
    int ch, i=0;

    while( (ch=fgetc(fp)) != '\n' && ch != EOF )
    {
        if(i < limit-1)
            str[i++] = ch;
    }
    str[i]='\0';

    return i;
}

void erase_blanks(char* expression)
{
   char*    p_exp = expression;
   char     flag = 0;

    while(*p_exp)
    {
        if(*p_exp != ' ')
            *expression++ = *p_exp;
        p_exp++;
    }
    *expression = '\0';
}

void handdle_print(char name)
{
    POLYNOMIAL* tmp = search(name);
    if(tmp)
        print_poly(tmp);
    else
        printf("polynomial '%c' does not exists.\n", name);
}

void handdle_calc(char name, char* px)
{
    POLYNOMIAL* tmp = search(name);
    if(tmp)
        printf("%d\n",eval(tmp, atoi(px)));
    else
        printf("polynomial '%c' does not exists.\n", name);
}

void handdle_definition(char* expression)
{
    erase_blanks(expression);

    char* f_name = strtok(expression, "=");
    if(!f_name || strlen(f_name) != 1)
    {
        printf("Unsupported command.\n");
        return;
    }

    char* exp_body = strtok(NULL, "=");
    if(!exp_body || strlen(exp_body) <= 0)
    {
        printf("Invalid expression format.\n");
        return;
    }

    if(exp_body[0] >= 'a' && exp_body[0] <= 'z' && exp_body[0] != 'x')
    {
        char* former = strtok(exp_body, "+");
        if(!former || strlen(former) != 1)
        {
            printf("Invalid expression formet. former\n");
            return;
        }

        char* later = strtok(NULL, "+");
        if(!later || strlen(later) != 1)
        {
            printf("Invalid expression formet. later\n");
            return;
        }

        POLYNOMIAL* pol = create_by_add_two_polynomias(f_name[0], former[0], later[0]);
        if(!pol)
        {
            printf("Invalid expression format. create\n");
            return;
        }
        insert_polynomial(pol);
    }
    else
    {
        POLYNOMIAL* pol = create_by_parse_polynomial(f_name[0], exp_body);
        if(!pol)
        {
            printf("Invalid expression format.\n");
            return;
        }
        insert_polynomial(pol);
    }
}

void process_command()
{
    char command_line[BUFFER_LEN];
    char copied[BUFFER_LEN];
    char* command, *arg1, *arg2;

    while(1)
    {
        printf("$ ");
        
        if(read_line(stdin, command_line, BUFFER_LEN) <= 0)
            continue;
        
        strcpy(copied, command_line);           // 다항식 정의 명령의 형식이 다르기 때문에 이를 위해 저장
        command = strtok(command_line, " ");

        if(!strcmp(command, "print"))
        {
            arg1 = strtok(NULL, " ");    // 함수 이름
            if(!arg1)
            {
                printf("Invalid arguments\n");
                continue;
            }
            handdle_print(arg1[0]);  // 함수 이름은 한 글자이기 때문에 문자 자체를 넘겨준다.
        }
        else if(!strcmp(command, "calc"))
        {
            arg1 = strtok(NULL, " ");   // 함수 이름.
            if(!arg1)
            {
                printf("Invalid arguments.\n");
                continue;
            }

            arg2 = strtok(NULL, " ");   // x의 값
            if(!arg2)
            {
                printf("Invalid arguments.\n");
                continue;
            }

            handdle_calc(arg1[0], arg2);
        }
        else if(!strcmp(command, "exit"))
            break;
        else
            handdle_definition(copied);
    }
}

