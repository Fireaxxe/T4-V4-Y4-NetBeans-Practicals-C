#include <stdio.h>

int main()
{
    printf("Enter input: ");

    float amount;
    scanf("%f",&amount);
    int x = (int)(amount * 100.0 + 0.5); // x stores the user input in cents

    int y = x / 2000; // 20 pounds is 2000
    printf("\n20 pound bills: %d",y);
    x = x % 2000;

   y = x / 1000; 
    printf("\n10 pound bills: %d",y);
    x = x % 1000;
    
    y = x / 500; 
    printf("\n5 pound bills: %d",y);
    //x = x % 500;
    
    y = x / 200; 
    printf("\n2 pound coins: %d",y);
    //x = x % 200;
    
    y = x / 100; 
    printf("\n1 pound coins: %d",y);
    //x = x % 100;
    
    y = x / 50; 
    printf("\n50p coins: %d",y);
    //x = x % 50;

    y=x / 20; // we're working with pennies, so 20 = 20 pennies
    printf("\n20p coins: %d",y);    
    //x = (x % 20);
    
    y = x / 10; 
    printf("\n10p coins: %d",y);
    //x = x % 10;
    
     y = x / 5; 
    printf("\n5p coins: %d",y);
    //x = x % 5;
    
     y = x / 2; 
    printf("\n2p coins: %d",y);
    //x = x % 2;
    
     y = x / 1; 
    printf("\n1p coins: %d",y);
    //x = x % 1;
}