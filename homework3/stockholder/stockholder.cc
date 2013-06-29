#include <stdio.h>
#include <stdint.h>
#include <string.h>

const size_t M = 309989, L = 16;
struct Node
{
  int c;
  char s[L+1];
  Node *next;
} pool[10000], *buckets[M], *pit = pool;

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

Node *find(const char *s)
{
  size_t n = strlen(s);
  uint32_t h = murmur2(s, n) % M;
  for (Node *p = buckets[h]; p; p = p->next)
    if (! strcmp(p->s, s))
      return p;
  pit->next = buckets[h];
  pit->c = 0;
  strcpy(pit->s, s);
  return buckets[h] = pit++;
}

int main()
{
  int n, t, optc = -1;
  char name[L+1], *opts;
  for (scanf("%d", &n); n--; ) {
    scanf("%s%d", name, &t);
    find(name)->c += t;
  }
  for (Node *p = pool; p < pit; p++)
    if (p->c > optc) {
      optc = p->c;
      opts = p->s;
    }
  printf("%s %d\n", opts, optc);
}
