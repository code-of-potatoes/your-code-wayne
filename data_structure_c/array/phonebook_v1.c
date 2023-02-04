/*
    단순한 배열만을 이용한 전화번호부
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
        else if(!strcmp(command,"exit"))
            break; 
    }

    return 0;
}



void add()
{
    char name_buf[MAX_NAME], phone_buf[MAX_PHONE_NUMBER];
    scanf("%s",name_buf);
    scanf("%s",phone_buf);

    names[num] = strdup(name_buf);
    numbers[num] = strdup(phone_buf);
    num++;

    printf("%s was added successfully.\n", name_buf);
}



void find()
{
    char name_buf[MAX_NAME];

    scanf("%s",name_buf);

    for(int i=0; i<num; i++)
    {
        if(!strcmp(names[i],name_buf))
        {
            printf("%s\n",numbers[i]);
            return;
        }
    }
    
    printf("No person named '%s' exists.\n",name_buf);
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

    for(int i=0; i<num; i++)
    {
        if(!strcmp(names[i],name_buf))
        {
            free(names[i]);
            free(numbers[i]);
           
            // 순서를 유지해야하는 경우 
            /*
            for(int j=i; j<num-1; j++)
            {
                names[j] = names[j+1];
                numbers[j] = numbers[j+1];
            }
            */

            // 순서 유지가 필요없는 경우
            names[i] = names[num-1];
            numbers[i] = numbers[num-1];

            num--;
            printf("%s was deleted successfully.\n",name_buf);
            return;
        }
    }
    printf("No person named '%s' exists.\n",name_buf);
}












