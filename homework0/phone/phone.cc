#include <stdio.h>

int f()
{
  int h, m, s;
  scanf("%d:%d:%d", &h, &m, &s);
  return (h * 60 + m) * 60 + s;
}

int main()
{
  int t = f();
  t = f() - t;
  if (t < 0) t += 24 * 60 * 60;
  printf("%d\n", t);
}
