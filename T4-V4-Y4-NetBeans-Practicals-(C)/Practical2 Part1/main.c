#include<stdio.h>

int main() {
    int rev = 0, n;
    printf("Reverse is: ");
    scanf("%d", &n);
x:
    if (n > 0)
        rev = rev * 10 + n % 10;
    n = n / 10;
    if (n > 0)
        goto x;
    printf("%d", rev);
}