#include <stdio.h>
#include <stdint.h>
#include <string.h>

const size_t M = 8000009;
short c[M];

uint32_t murmur2(const char *s, size_t n)
{
  const uint32_t m = 0x5bd1e995, r = 24;
  uint32_t h = 19921213 ^ n;
  while (n >= 4) {
    uint32_t k = *(uint32_t *)s;
    k *= m;
    k ^= k >> r;
    k *= m;

    h *= m;
    h ^= k;

    s += 4;
    n -= 4;
  }

  switch (n) {
  case 3:
    h ^= ((unsigned char *)s)[2] << 16;
  case 2:
    h ^= ((unsigned char *)s)[1] << 8;
  case 1:
    h ^= ((unsigned char *)s)[0];
    h *= m;
  }

  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;
  return h;
}

int minRep(char *a, size_t n)
{
  n = strlen(a);
  int i = 0, j = 1;
  while (i < n && j < n) {
    int k = 0;
    while (k < n && a[(i+k)%n] == a[(j+k)%n]) k++;
    if (a[(i+k)%n] <= a[(j+k)%n]) j += k+1;
    else i += k+1;
    if (i == j) j++;
  }
  return i < j ? i : j;
}

void reverse(char *p, char *q)
{
  for (; p < --q; p++) {
    char t = *p;
    *p = *q;
    *q = t;
  }
}

void rotate(char *p, char *q, char *r)
{
  reverse(p, q);
  reverse(q, r);
  reverse(p, r);
}

int main()
{
  int m, n;
  char s[10001];
  scanf("%d%d", &m, &n);
  for (int i = 1; i <= m; i++) {
    scanf("%s", s);
    int f = minRep(s, n);
    rotate(s, s+f, s+n);
    uint32_t h = murmur2(s, n) % M;
    printf("%d\n", c[h]);
    if (! c[h]) c[h] = i;
  }
}
