#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "temperature.h"
typedef int64_t i64;

const int N = 50000;
struct P { int x, y, t; } b[N];
struct PP { int y; int64_t s; } a[17][N];
int64_t sum;
int cnt;

int cmp(const void *a, const void *b)
{
  int u = (*(P *)a).x, v = (*(P *)b).x;
  return u > v ? 1 : u < v ? -1 : 0;
}

void build(int d, int l, int r)
{
  if (l == r-1) {
    a[d][l].y = b[l].y;
    a[d][l].s = b[l].t;
    return;
  }
  int m = (l+r)/2;
  build(d+1, l, m);
  build(d+1, m, r);
  for (int o = l, i = l, j = m; i < m || j < r; ) {
    if (i == m || j < r && a[d+1][j].y < a[d+1][i].y) {
      a[d][o] = a[d+1][j];
      if (m < j) a[d][o].s -= a[d+1][j-1].s;
      j++;
    } else {
      a[d][o] = a[d+1][i];
      if (l < i) a[d][o].s -= a[d+1][i-1].s;
      i++;
    }
    if (l < o)
      a[d][o].s += a[d][o-1].s;
    o++;
  }
}

#define BISECTION(P, name, op, x) \
  P *name(P *l, P *r, int x) \
  { \
    while (l < r) { \
      P *m = l + (r-l)/2; \
      if (m->x op x) l = m+1; \
      else r = m; \
    } \
    return l; \
  }
BISECTION(P, lowerBoundX, <, x)
BISECTION(PP, lowerBoundY, <, y)
BISECTION(P, upperBoundX, <=, x)
BISECTION(PP, upperBoundY, <=, y)

void count(int d, int l, int r, int ll, int rr, int p, int q)
{
  if (ll <= l && r <= rr) {
    p = lowerBoundY(a[d]+l, a[d]+r, p) - a[d];
    q = upperBoundY(a[d]+l, a[d]+r, q) - a[d];
    cnt += q-p;
    if (l < q) sum += a[d][q-1].s;
    if (l < p) sum -= a[d][p-1].s;
    return;
  }
  int m = (l+r)/2;
  if (ll < m) count(d+1, l, m, ll, rr, p, q);
  if (m < rr) count(d+1, m, r, ll, rr, p, q);
}

int main()
{
  int n = GetNumOfStation();
  for (int i = 0; i < n; i++) {
    int t;
    GetStationInfo(i, &b[i].x, &b[i].y, &t);
    b[i].t = t;
  }
  qsort(b, n, sizeof *b, cmp);
  build(0, 0, n);

  int ll, rr, p, q;
  while (GetQuery(&ll, &p, &rr, &q)) {
    ll = lowerBoundX(b, b+n, ll) - b;
    rr = upperBoundX(b, b+n, rr) - b;
    sum = cnt = 0;
    count(0, 0, n, ll, rr, p, q);
    Response(cnt ? int(sum/cnt) : 0);
  }
}
