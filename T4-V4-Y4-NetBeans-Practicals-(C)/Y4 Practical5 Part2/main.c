/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newmain.c
 * Author: Cotsios
 *
 * Created on February 26, 2018, 6:57 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main() {
    double myDouble = 12.34;
    int myInt = 56;
    char myChar = 'C';

    double *theDouble;
    int *theInt;
    char *theChar;

    theDouble = &myDouble;
    theInt = &myInt;
    theChar = &myChar;

    printf("myDouble value is : %f\n", myDouble);
    printf("myDouble address is : %p\n", &myDouble);
    printf("myDouble size is : %d\n", sizeof (myDouble));

    printf("myInt value is : %d\n", myInt);
    printf("myInt address is : %p\n", &myInt);
    printf("myInt size is : %d\n", sizeof (myInt));

    printf("myChar  is : %c\n", myChar);
    printf("myChar address is : %s\n", &myChar);
    printf("myChar size is : %d\n", sizeof (myChar));

    printf("theDouble value is : %f\n", *theDouble);
    printf("theDouble address is : %p\n", theDouble);
    printf("theDouble size is : %d\n", sizeof (theDouble));

    printf("theInt value is : %d\n", *theInt);
    printf("theInt address is : %p\n", theInt);
    printf("theInt size is : %d\n", sizeof (theInt));

    printf("theChar  is : %c\n", *theChar);
    printf("theChar address is : %s\n", theChar);
    printf("theChar size is : %d\n", sizeof (theChar));




    printf("theDouble old address is : %p\n", theDouble);
    printf("theInt old address is : %p\n", theInt);
    printf("theChar old address is : %s\n", theChar);
    theDouble = theDouble + 1;
    theInt = theInt + 1;
    theChar = theChar + 1;
    printf("theDouble new address is : %p\n", theDouble);
    printf("theInt new address is : %p\n", theInt);
    printf("theChar new address is : %s\n", theChar);


    return 0;
}

