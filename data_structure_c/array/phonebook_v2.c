
/*
    배열기반 전화번호부 
    정렬을 유지하여 file로 부터 data를 읽고 data를 file로 다시 저장하는 기능 추가 (file은 항상 정렬된 상태라고 가정)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 20
#define MAX_PHONE_NUMBER 20
#define MAX_COMMAND 10

char*   names[MAX_NAME];
char*   numbers[MAX_PHONE_NUMBER];
char    command[MAX_COMMAND];
int     num;

void load();
void save();
int search(char str[]);
void add();
void find();
void status();
void delete();


int main()
{
    while(1)
    {
        printf("$ ");

        scanf("%s",command);

        if(!strcmp(command,"add"))
            add();
        else if(!strcmp(command,"find"))
            find();
        else if(!strcmp(command,"status"))
            status();
        else if(!strcmp(command,"delete"))
            delete();
        else if(!strcmp(command,"read"))
            load();
        else if(!strcmp(command,"save"))
            save();
        else if(!strcmp(command,"exit"))
            break; 
    }

    return 0;
}


void load()
{
    char filename[MAX_NAME];
    char name_buf[MAX_NAME], phone_buf[MAX_PHONE_NUMBER];
    scanf("%s",filename);

    FILE* fp = fopen(filename,"r");
    if(fp == NULL)
    {
        printf("Open failed.\n");
        return;
    }  

    while( fscanf(fp, "%s", name_buf) != EOF )
    {
        fscanf(fp, "%s", phone_buf);
        names[num] = strdup(name_buf);
        numbers[num] = strdup(phone_buf);
        num++;
    }

    fclose(fp);
}


void save()
{
    char filename[MAX_NAME];
    scanf("%s",filename);

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



void add()
{
    int i = num-1;
    char name_buf[MAX_NAME], phone_buf[MAX_PHONE_NUMBER];
    scanf("%s",name_buf);
    scanf("%s",phone_buf);

    // 데이터가 들어있는 원소 끝에서부터 들어가야할 공간의 index를 찾아간다.
    while(i>=0 && strcmp(names[i], name_buf) > 0)
    {
        // 새로운 data 저장을 위한 공간 확보
        names[i+1] = names[i];
        numbers[i+1] = numbers[i];
        i--;
    }

    names[i+1] = strdup(name_buf);
    numbers[i+1] = strdup(phone_buf);

    num++;
    printf("%s was added successfully.\n", name_buf);
}



void find()
{
    char name_buf[MAX_NAME];
    scanf("%s",name_buf);

    int index = search(name_buf);
    if(index == -1)
        printf("No person named '%s' exists.\n",name_buf);
    else
        printf("%s\n",numbers[index]);
}



void status()
{
    for(int i=0; i<num; i++)
    {
        printf("%s %s\n",names[i],numbers[i]);
    }

    printf("Total %d persons.\n",num);
}



void delete()
{
    char name_buf[MAX_NAME];
    scanf("%s",name_buf);

    int index = search(name_buf);

    if(index == -1)
    {
        printf("No person named '%s' exists.\n",name_buf);
        return;
    }
    
    for(int i=index; i<num-1; i++)
    {
        names[i] = names[i+1];
        numbers[i] = numbers[i+1];
    }

    num--;
    printf("%s was deleted successfully.\n",name_buf);
}
