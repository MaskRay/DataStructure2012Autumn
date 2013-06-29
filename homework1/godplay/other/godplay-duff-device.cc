#include <stdio.h>

int main()
{
  int n, m;
  scanf("%d%d", &n, &m);
  if (n < 3) {
    printf("%d\n", n % m);
    return 0;
  }

  unsigned long long a = 1, b = 1 + n % 2;
  n /= 2;
  int c = (n + 21) / 22;
  switch (n % 22) {
  case 0:
    do {
      a += b; b += a;
    case 21: a += b; b += a;
    case 20: a += b; b += a;
    case 19: a += b; b += a;
    case 18: a += b; b += a;
    case 17: a += b; b += a;
    case 16: a += b; b += a;
    case 15: a += b; b += a;
    case 14: a += b; b += a;
    case 13: a += b; b += a;
    case 12: a += b; b += a;
    case 11: a += b; b += a;
    case 10: a += b; b += a;
    case 9: a += b; b += a;
    case 8: a += b; b += a;
    case 7: a += b; b += a;
    case 6: a += b; b += a;
    case 5: a += b; b += a;
    case 4: a += b; b += a;
    case 3: a += b; b += a;
    case 2: a += b; b += a;
    case 1: a += b; b += a;
      a %= m; b %= m;
    } while (--c > 0);
  }
  printf("%d\n", int(a));
}
