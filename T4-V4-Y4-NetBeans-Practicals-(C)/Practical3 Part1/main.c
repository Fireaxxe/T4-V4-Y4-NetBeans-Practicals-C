#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define length 20

int main (void)
{
int number;
int digit;
int n;
bool digit_seen[length] = {false};
bool one_repeat = false;
printf("Enter a number: ");
scanf("%d", &number);
printf("Repeated digits:\n");

while (number > 0)
{
  digit = number % 10; // Input: 28212 >>>>> digit = number % 10 = 2
  if (digit_seen[digit])
  {
   printf("%d " , digit);
   one_repeat = true;
  }
  digit_seen[digit] = true;
  number /= 10;
}
printf("\n");
if (!one_repeat)
{
  printf("None\n");
}
return 0;
}
 