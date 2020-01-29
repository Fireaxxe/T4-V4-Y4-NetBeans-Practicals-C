/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Cotsios
 *
 * Created on March 7, 2018, 11:22 AM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main() {
    int i = 10;
    
    int * p, * q;
    //p = &i;
    q = &i;
    //p = i; //run failed
    //*p = &i; //run failed
    //&p = q; //error
    //p = &q; //it runs but incompatible pointer type
    
    //p = *&q; //RUNS, p gets value of q
    
    //p = q; //RUNS simple syntax
    
    //p = *q; //run failed    
    //*p = q; //runs but takes integer from pointer without cast
    
    *p = *q; //RUNS takes value but p has not the same address as i 
    
    
    printf("%p\n ", &i);
    printf("%d\n ", i);
    printf("%p\n ", p);
    printf("%d\n ", *p);

    return (0);
}

