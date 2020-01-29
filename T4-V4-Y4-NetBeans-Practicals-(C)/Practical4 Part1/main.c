#include <stdio.h>



void calc(int *twenty, int *ten, int *five, int *one, int x){
int *tw = twenty;    
int twenties = x / *tw;
x = x % *tw;

int *t = ten;
int tens = x / *t;
x = x % *t;

int *f = five;
int fives = x / *f;
x = x % *f;

int *o = one;
int ones = x / *o;
x = x % *o;

printf("%d\n", twenties);
printf("%d\n", tens);
printf("%d\n", fives);
printf("%d\n", ones);
}

int main()
{   
    int twentie = 20;
    int ten = 10;
    int five = 5;
    int one = 1;  

    float amount;
    scanf("%f",&amount);
    int x = (int)(amount);
    
     calc(&twentie, &ten, &five, &one, x);    

    return 0;
}