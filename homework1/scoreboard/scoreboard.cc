#include <stdio.h>

int main()
{
  int m, a[10], c, x = 0;
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    scanf("%d", &c);
    a[c] = i;
  }
  while (scanf("%1d", &c) == 1)
    x = x * m + a[c];
  printf("%d\n", x);
}
