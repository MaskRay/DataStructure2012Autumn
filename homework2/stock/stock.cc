#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

typedef int64_t i64;

const int N = 10000000;
struct Node
{
  int x, c;
} q[N];

int readInt()
{
  int c, t = 0;
  while (c = getchar(), c < '0' || c > '9');
  while ('0' <= c && c <= '9') {
    t = t * 10 + c - '0';
    c = getchar();
  }
  ungetc(c, stdin);
  return t;
}

int main()
{
  int n = readInt();
  i64 sum = 0, sum2 = 0;
  Node *fore = q, *rear = q;
  for (int i = 0; i < n * 2; i++) {
    int d = readInt();
    sum += d;
    if (i) sum2 += i64(d) * (fore == rear ? 0 : fore->x);
    if (getchar() == ' ') {
      int x = readInt(), c = 1;
      while (fore < rear && rear[-1].x <= x)
        c += (--rear)->c;
      rear->x = x;
      rear->c = c;
      rear++;
    } else if (! --fore->c)
      fore++;
  }
  printf("%.2lf\n", (double)sum2 / sum);
}
