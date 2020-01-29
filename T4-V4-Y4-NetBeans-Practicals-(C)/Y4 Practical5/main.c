/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Cotsios
 *
 * Created on February 26, 2018, 2:46 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(){
    int * pc, c;
    c=22;    
    printf("c value is %d\n", c);
    printf("c address is %p\n", &c);
    
    pc = &c;//assign pointer pc the address of c
    printf("pc value is %d\n", *pc);
    printf("pc address is %p\n", pc);
    
    c = 11;//assign the value 11 to c
    printf("pc new value is %d\n", *pc);
    printf("pc new address is %p\n", pc);
    
    *pc = 2;//assign the value 2 to the value pointed by pc
    printf("c new value is %d\n", c);
    printf("c new address is %p\n", &c);
    
    
    return 0;
}
