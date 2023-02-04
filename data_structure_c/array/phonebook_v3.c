/*
    배열기반 전화번호부 
    배열 할당, 라인단위 입력, 문자열 tokenizing
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAPACITY 3
#define MAX_NAME 20
#define MAX_PHONE_NUMBER 20
#define MAX_COMMAND 50


char**   names;             // 문자열 포인터 배열을 resizing하기 위해 names와 number 모두 더블 포인터로 정의
char**   numbers;
char     delim[] = " ";     // delimiter
int      capacity = INIT_CAPACITY;
int      num;


void init_directory();
void process_command();

int read_line(char str[], int limit);   //line 단위 입력은 fgets(), getline() 등의 함수를 사용할 수도 있다.
int search(char str[]);
void reallocate();
void status();

void load(char* filename);
void save(char* filename);
void add(char* name, char* number);
void find(char* name);
void delete(char* name);




int main()
{
    init_directory();
    process_command();

    return 0;
}

void init_directory()
{
    names = (char**)malloc(sizeof(char*)*INIT_CAPACITY);
    numbers = (char**)malloc(sizeof(char*)*INIT_CAPACITY);
}

void process_command()
{
    char command_line[MAX_COMMAND];
    char *command, *arg1, *arg2;

    while(1)
    {
        printf("$ ");

        // 입력이 없는 경우 continue
        if(read_line(command_line, MAX_COMMAND) <= 0)
            continue;
        
        // command token
        command = strtok(command_line, delim);

        if(!strcmp(command,"read"))
        {
            arg1 = strtok(NULL,delim);

            if(!arg1)
            {
                printf("File name required.\n");
                continue;
            }

            load(arg1);
        }
        else if(!strcmp(command,"add"))
        {
            arg1 = strtok(NULL,delim);
            arg2 = strtok(NULL,delim);

            if(!arg1 || !arg2)
            {
                printf("Invalid arguments.\n");
                continue;
            }

            add(arg1, arg2);
            printf("%s was added succesfully.\n", arg1);
        }
        else if(!strcmp(command,"find"))
        {
            arg1 = strtok(NULL,delim);
            if(!arg1)
            {
                printf("Invalid argument.\n");
                continue;
            }
            find(arg1);
        }
        else if(!strcmp(command,"status"))
            status();
        else if(!strcmp(command,"delete"))
        {
            arg1 = strtok(NULL,delim);
            if(!arg1)
            {
                printf("Invalid argument.\n");
                continue;
            }
            delete(arg1);
        }
        else if(!strcmp(command,"save"))
        {
            arg1 = strtok(NULL,delim);

            if(!arg1)
            {
                printf("File name required.\n");
                continue;
            }
            save(arg1);
        }
        else if(!strcmp(command, "exit"))
            break;
    }
}

int read_line(char str[], int limit)
{   
    int ch, i=0;

    while( (ch = getchar()) != '\n')
    {
        if(i < limit-1)
            str[i++] = ch;
    }
    str[i]='\0';

    return i;
}

int search(char str[])
{
    for(int i=0; i<num; i++)
    {
        if(!strcmp(names[i],str))
        {
            return i;
        }
    }
    return -1;
}

void reallocate()
{
    capacity *= 2;
    char** temp1 = (char**)malloc(sizeof(char*)*capacity);
    char** temp2 = (char**)malloc(sizeof(char*)*capacity);

    for(int i=0; i<num; i++)
    {
        temp1[i] = names[i];
        temp2[i] = numbers[i];
    }

    free(names);
    free(numbers);

    names = temp1;
    numbers = temp2;

}

void status()
{
    for(int i=0; i<num; i++)
    {
        printf("%s %s\n",names[i],numbers[i]);
    }

    printf("Total %d persons.\n",num);
}


void load(char* filename)
{
    char name_buf[MAX_NAME], number_buf[MAX_PHONE_NUMBER];

    FILE* fp = fopen(filename,"r");
    if(fp == NULL)
    {
        printf("Open failed.\n");
        return;
    }  

    while( fscanf(fp, "%s", name_buf) != EOF )
    {
        fscanf(fp, "%s", number_buf);
        add(name_buf, number_buf);
    }
    fclose(fp);
}


void save(char* filename)
{
    FILE* fp = fopen(filename,"w");
    if(fp == NULL)
    {
        printf("Open failed.\n");
        return;
    }  

    for(int i=0; i<num; i++)
    {
        fprintf(fp, "%s %s\n", names[i], numbers[i]);
    }

    fclose(fp);

}


void add(char* name, char* number)
{
    if(num >= capacity)
        reallocate();
    
    int i = num-1;

    // 데이터가 들어있는 원소 끝에서부터 들어가야할 공간의 index를 찾아간다.
    while(i>=0 && strcmp(names[i], name) > 0)
    {
        // 새로운 data 저장을 위한 공간 확보
        names[i+1] = names[i];
        numbers[i+1] = numbers[i];
        i--;
    }

    names[i+1] = strdup(name);
    numbers[i+1] = strdup(number);

    num++;
}


void find(char* name)
{
    int index = search(name);
    if(index == -1)
        printf("No person named '%s' exists.\n",name);
    else
        printf("%s\n",numbers[index]);
}


void delete(char* name)
{
    int index = search(name);

    if(index == -1)
    {
        printf("No person named '%s' exists.\n",name);
        return;
    }
    
    for(int i=index; i<num-1; i++)
    {
        names[i] = names[i+1];
        numbers[i] = numbers[i+1];
    }
    num--;
    printf("%s was deleted successfully.\n",name);
}


