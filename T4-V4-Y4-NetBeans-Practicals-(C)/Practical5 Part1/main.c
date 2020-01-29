#include <stdlib.h>
#include <stdio.h>
#define DEBUG

int sum(int x, int y, int *z) {
    
    //we can change it to int c = 4 or char c = 'C'. but it's still unused
    //char c = 4; 
    
#ifdef DEBUG
    fprintf(stderr, "x=%d\n", x);
#endif
#ifdef DEBUG
    fprintf(stderr, "y=%d\n", y);
#endif
#ifdef DEBUG
    fprintf(stderr, "z=%d\n", z);
#endif
#ifdef DEBUG
    fprintf(stderr, "*z=%d\n", *z);
#endif
    return (x + y + *z);
}

int main(int argc, char *argv[]) {
    int i, j, k, *z;
    int result;
    k = 0;
    z = &k; //here is the problem. the *z = k is not valid.
    //z = &k makes more sense with the rest of the program
    // now z pointer is equal to the address of k, means that
    //any value that is inside k now is equal to z.
    printf("Address of z now is: %p\n", z);
    printf("Address of k is: %p\n", &k);
    
    if (argc != 4) {
        printf("Please specify three numbers as parameters.\n");
        exit(1);
    }
    i = atoi(argv[1]);
    j = atoi(argv[2]);
    k = atoi(argv[3]);
    k *= 2;
    result = sum(i, j, z) + sum(i, j, &k);
    printf("%d\n", result);
#ifdef DEBUG
    fprintf(stderr, "Number of parameters = %d\n", argc);
#endif
    return 0;
}