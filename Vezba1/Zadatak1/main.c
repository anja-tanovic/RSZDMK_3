#include <stdio.h>

void PrintResult(int res)
{
printf("Result: %d\n", res);
}

int Calculation(int a, int b)
{
if(a > b)
return a - b;
else
return b - a;
}

int main()
{
int a = 3;
int b = 8;
int c;
c = Calculation(a, b);
PrintResult(c);
return 0;
}