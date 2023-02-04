/*
    배열기반 전화번호부 
    구조체 포인터, 동적 할당
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAPACITY 100
#define BUFFER_LENGTH 100

typedef struct person{
    char* name;
    char* number;
    char* email;
    char* group;
}   PERSON;

PERSON**    directory;
int         capacity;
int         num;

void init();
void process_command();

int  search(char str[]);
int  compose_name(char* name_str, int limit);
void reallocate();
void handdle_add(char* name);
void release_person(PERSON* p);
void print_person(PERSON* p);


int  read_line(FILE* fp ,char str[], int limit);   //line 단위 입력은 fgets(), getline() 등의 함수를 사용할 수도 있다.
void status();
void load(char* filename);
void add(char* name, char* number, char* email, char* group);
void find(char* name);
void save(char* filename);
void delete(char* name);


int main()
{
    init();
    process_command();

    return 0;
}

void init()
{
    directory = (PERSON**)malloc(sizeof(PERSON*) * INIT_CAPACITY);
    capacity = INIT_CAPACITY;
}

void process_command()
{
    char command_line[BUFFER_LENGTH];
    char name_str[BUFFER_LENGTH];
    char *command, *arg1;

    while(1)
    {
        printf("$ ");

        // 입력이 없는 경우 continue
        if(read_line(stdin, command_line, BUFFER_LENGTH) <= 0)
            continue;
        
        // command token
        command = strtok(command_line, " ");

        if(!strcmp(command,"read"))
        {
            arg1 = strtok(NULL," ");

            if(!arg1)
            {
                printf("File name required.\n");
                continue;
            }

            load(arg1);
        }
        else if(!strcmp(command,"add"))
        {
            if(compose_name(name_str, BUFFER_LENGTH) <= 0)
            {
                printf("Invalid argument.\n");
                continue;
            }

            handdle_add(name_str);
        }
        else if(!strcmp(command,"find"))
        {
            if(compose_name(name_str, BUFFER_LENGTH) <= 0)
            {
                printf("Invalid argument.\n");
                continue;
            }

            find(name_str);
        }
        else if(!strcmp(command,"status"))
            status();
        else if(!strcmp(command,"delete"))
        {
            if(compose_name(name_str, BUFFER_LENGTH) <= 0)
            {
                printf("Invalid argument.\n");
                continue;
            }
            delete(name_str);
        }
        else if(!strcmp(command,"save"))
        {
            arg1 = strtok(NULL," ");
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

int search(char str[])
{
    for(int i=0; i<num; i++)
    {
        if(!strcmp(directory[i]->name,str))
        {
            return i;
        }
    }
    return -1;
}

//앞, 뒤의 불필요한 공백은 없애고 단어와 단어사이의 여러 개의 공백을 하나의 공백으로 압축
int compose_name(char* name_str, int limit)
{
    char* ptr;
    int length = 0;

    ptr = strtok(NULL, " ");
    if(!ptr)
        return 0;

    strcpy(name_str, ptr);
    length += strlen(ptr);

    while( (ptr = strtok(NULL, " ")) != NULL)
    {
        if(length + strlen(ptr) + 1 < limit)
        {   
            name_str[length++] = ' ';
            name_str[length] = '\0';
            strcat(name_str, ptr);
            length += strlen(ptr);
        }
    }

    return length;
}

void reallocate()
{
    capacity *= 2;
    PERSON** tmp = (PERSON**)malloc(sizeof(PERSON*) * capacity);

    for(int i=0; i<num; i++)
        tmp[i] = directory[i];

    free(directory);
    directory = tmp;
}

void handdle_add(char* name)
{
    char number[BUFFER_LENGTH], email[BUFFER_LENGTH], group[BUFFER_LENGTH];

    printf("  Phone: ");
    read_line(stdin, number, BUFFER_LENGTH);

    printf("  Email: ");
    read_line(stdin, email, BUFFER_LENGTH);

    printf("  Group: ");
    read_line(stdin, group, BUFFER_LENGTH);

    // 입력되지 않는 항목들을 하나의 공백 문자로 대체
    add(strdup(name),   (char*)(strlen(number)>0 ? strdup(number) : NULL),
                        (char*)(strlen(email)>0 ? strdup(email) : NULL),
                        (char*)(strlen(group)>0 ? strdup(group) : NULL));
}

void release_person(PERSON* p)
{
    free(p->name);
    if(p->number)   free(p->number);
    if(p->email)   free(p->email);
    if(p->group)   free(p->group);
    free(p);
}

void print_person(PERSON* p)
{
    printf("%s:\n", p->name);
    printf("  Phone: %s\n", (char*)(p->number ? p->number : " "));
    printf("  Email: %s\n", (char*)(p->email ? p->email : " "));
    printf("  Group: %s\n", (char*)(p->group ? p->group : " "));
}


// 키보드, 파일로 부터 data를 읽을 수 있다.    [키보드 : stdin, 파일 : opend file pointer]
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


void status()
{
    for(int i=0; i<num; i++)
    {
        print_person(directory[i]);
    }
    printf("Total %d persons.\n",num);
}


void load(char* filename)
{
    char buffer[BUFFER_LENGTH];
    char* name, *number, *email, *group;
    char* token;

    FILE* fp = fopen(filename,"r");
    if(fp == NULL)
    {
        printf("Open failed.\n");
        return;
    }  

    while(1)
    {
        if(read_line(fp, buffer, BUFFER_LENGTH) <= 0)
            break;

        name = strtok(buffer, "#");

        // 존재하지 않는 항목은 공백문자로 저장되어 있는데, 이걸 그대로 공백문자로 구성된 문자열을 저장하는 것이 아닌 NULL로 저장하여 표현해준다.
        token = strtok(NULL, "#");
        if(!strcmp(token," "))
            number = NULL;
        else
            number = strdup(token); // 미리 복제를 해두고, 복제된 문자열의 주소를 add()로 넘겨준다.

        token = strtok(NULL, "#");
        if(!strcmp(token," "))
            email = NULL;
        else
            email = strdup(token);

        token = strtok(NULL, "#");
        if(!strcmp(token," "))
            group = NULL;
        else
            group = strdup(token);

        add(strdup(name), number, email, group);
    }

    fclose(fp);
}


void add(char* name, char* number, char* email, char* group)
{
    if(num >= capacity)
        reallocate();

    int i = num-1;
    // 데이터가 들어있는 원소 끝에서부터 들어가야할 공간의 index를 찾아간다.
    while(i>=0 && strcmp(directory[i]->name, name) > 0)
    {
        // 새로운 data 저장을 위한 공간 확보
        directory[i+1] = directory[i];
        i--;
    }

    directory[i+1] = (PERSON*)malloc(sizeof(PERSON));

    directory[i+1]->name = name;
    directory[i+1]->number = number;
    directory[i+1]->email = email;
    directory[i+1]->group = group;

    num++;
}


void find(char* name)
{
    int index = search(name);
    if(index == -1)
        printf("No person named '%s' exists.\n",name);
    else
        print_person(directory[index]);
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
        fprintf(fp, "%s#", directory[i]->name);
        fprintf(fp, "%s#", (char*)(directory[i]->number ? directory[i]->number : " "));
        fprintf(fp, "%s#", (char*)(directory[i]->email ? directory[i]->email : " "));
        fprintf(fp, "%s#\n", (char*)(directory[i]->group ? directory[i]->group : " "));
    }
    fclose(fp);

}


void delete(char* name)
{
    int index = search(name);
    if(index == -1)
    {
        printf("No person named '%s' exists.\n",name);
        return;
    }
    
    PERSON* p = directory[index];
    for(int i=index; i<num-1; i++)
    {
        directory[i] = directory[i+1];
    }
    num--;
    release_person(p);
    printf("%s was deleted successfully.\n",name);
}


