#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint64_t u64;

u64 d, opt = ULLONG_MAX, b[531441];
bool optf;
int a[24], n, m, id;
char op[24];

template<typename T>
T max(T a, T b) { return a > b ? a : b; }

int cmp(const void* p, const void* q)
{
  u64 a = *(u64*)p, b = *(u64*)q;
  return a < b ? -1 : a == b ? 0 : 1;
}

bool dfs(int k, u64 x, u64 needle)
{
  if (k == m) {
    if (x == needle) return true;
    b[id++] = x;
    return false;
  }
  u64 w = 0;
  for (int i = k; i < m && w <= ULLONG_MAX/10 && w * 10 + a[i] >= a[i]; i++) {
    w = w * 10 + a[i];
    if (n/2 <= i && i < m-1)
      continue;
    if (x + w >= w && (op[k] = '+', dfs(i + 1, x + w, needle)))
      return true;
    if (x && x <= ULLONG_MAX/w && (op[k] = '*', dfs(i + 1, x * w, needle)))
      return true;
    op[k] = '\0';
  }
  return false;
}

bool dfs2(int k, u64 mult, u64 plus)
{
  if (k == n) {
    int l = 0, r = id;
    while (l < r) {
      int mid = (l + r) / 2;
      if (b[mid] > ULLONG_MAX/mult) // overflow
        r = mid;
      else if (b[mid] * mult + plus < plus) // overflow
        r = mid;
      else if (b[mid] * mult + plus >= d)
        r = mid;
      else
        l = mid + 1;
    }
    if (l < id && b[l] <= ULLONG_MAX/mult && b[l] * mult + plus >= plus) {
      u64 res = b[l] * mult + plus;
      if (res == d) {
        dfs(0, 0, b[l]);
        for (int i = 0; i < n; i++) {
          if (i && op[i]) putchar(op[i]);
          printf("%d", a[i]);
        }
        puts("");
        return true;
      }
      if (d < res && res <= opt) {
        optf = true;
        opt = res;
      }
    }
    return false;
  }
  u64 w = 0;
  for (int i = k; i < n && w * 10 >= w && w * 10 + a[i] >= a[i]; i++) {
    w = w * 10 + a[i];
    if (plus + w >= w && (op[k] = '+', dfs2(i + 1, mult, plus + w)))
        return true;
    if (plus <= ULLONG_MAX/w && (op[k] = '*', dfs2(i + 1, mult * w, plus * w)))
      return true;
    op[k] = '\0';
  }
  return false;
}

int main()
{
  scanf("%d%"SCNu64, &n, &d);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);

  for (m = n/2; ++m <= n; ) {
    id = 0;
    dfs(0, 0, 0);
    qsort(b, id, sizeof *b, cmp);
    if (dfs2(m, 1, 0)) return 0;
  }
  printf("No\n%"PRIu64"\n", optf ? opt : 0);
}
