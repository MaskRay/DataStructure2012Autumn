#include <stdio.h>

int main()
{
  int a, b, t;
  scanf("%d%d", &a, &b);
  while (t = a % b, a = b, b = t);
  printf("%d\n", a);
}
