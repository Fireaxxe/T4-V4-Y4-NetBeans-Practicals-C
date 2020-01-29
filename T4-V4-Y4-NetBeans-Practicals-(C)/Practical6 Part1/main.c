/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Cotsios
 *
 * Created on March 17, 2018, 1:59 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main() {
    
    int a[] = {5, 15, 34, 54, 14, 2, 52, 72};
    int *p;  
    int *q;
    p = &a[1];
    q = &a[5];
    
    if (*p<*q){
        printf("If prints this, the condition is true\n");
    }
    
    if (&p<&q) {
       printf("If prints this, the 2nd condition is true\n");
    }
    
    if (p<q) {
      printf("If prints this, the 3nd condition is true\n");
    }
    
    printf("*p is %d\n", *p);
    printf("*p + 1 is %d\n", *(p+1));
    printf("*p + 2 is %d\n", *(p+2));
    printf("*p + 3 is %d\n", *(p+3));
    printf("*q is %d\n", *q);
    printf("*q - 1 is %d\n", *(q-1));
    printf("*q - 2 is %d\n", *(q-2));
    printf("*q - 3 is %d\n", *(q-3));
    printf("address of p is %p\n", p);
    printf("address of q is %p\n", q);
    printf("q - p is %d\n", q-p);
    printf("q - p is %d\n", *q-*p);
    
    printf("%d/n", (p * 2) );

    return (EXIT_SUCCESS);
}

