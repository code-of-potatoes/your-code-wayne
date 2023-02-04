#ifndef __POLY_H__
#define __POLY_H__

#define MAX_POLYS 20

typedef struct term_
{
    int    coef;
    int    expo;
    struct term_*  next;
}   TERM;

typedef struct polynomial_
{
    char   name;
    int    size;
    TERM*  first;    // head
}   POLYNOMIAL;

POLYNOMIAL* polys[MAX_POLYS];   // 생성된 polynomial에 대한 포인터 배열
int polys_num;

void print_poly(POLYNOMIAL* poly);
void destroy_all();
void insert_polynomial(POLYNOMIAL* ptr_poly);

int eval(POLYNOMIAL* poly, int x);

POLYNOMIAL* search(char name);
POLYNOMIAL* create_by_parse_polynomial(char name, char* body);
POLYNOMIAL* create_by_add_two_polynomias(char name, char f, char g);


#endif