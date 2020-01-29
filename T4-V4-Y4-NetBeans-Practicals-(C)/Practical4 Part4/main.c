#include <stdio.h>
int twenties(int x)
{    
     int y = x / 2000; // 20 pounds is 2000            
    return y;
}

int tens(int x)
{    
    x = x % 2000;
    int y = x / 1000;     
    return y;
}

int fives(int x)
{    
    x = x % 1000;
    int y = x / 500; 
    return y;
}

int ones(int x)
{    
    x = x % 500;
    int y = x / 100;    
    return y;
}


int main(void)
{
int amount;
printf("Enter a dollar amount: ");
scanf("%d", &amount);
int x = (int)(amount * 100.0 + 0.5);//break the amount into pens

printf("\n"); /* blank line */
printf("$20 bills: %d\n", twenties(x));
printf("$10 bills: %d\n", tens(x));
printf(" $5 bills: %d\n", fives(x));
printf(" $1 bills: %d\n", ones(x));
return 0;
}