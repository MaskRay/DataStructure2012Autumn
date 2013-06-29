#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "temperature.h"
typedef int64_t i64;

const int N = 50000;
struct P { int x, y, t; } b[N];
struct PP { int y, lc, rc; int64_t s; } a[17][N];
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
  for (int i = l, j = m, o = l; o < r; o++) {
    for (; i < m && a[d+1][i].y < a[d][o].y; i++);
    a[d][o].lc = i;
    for (; j < r && a[d+1][j].y < a[d][o].y; j++);
    a[d][o].rc = j;
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

void count(int d, int l, int r, int xl, int xr, int yl, int yr)
{
  if (xl <= l && r <= xr) {
    cnt += yr-yl;
    if (l < yr) sum += a[d][yr-1].s;
    if (l < yl) sum -= a[d][yl-1].s;
    return;
  }
  int m = (l+r)/2;
  if (xl < m) count(d+1, l, m, xl, xr, yl == r ? m : a[d][yl].lc, yr == r ? m : a[d][yr].lc);
  if (m < xr) count(d+1, m, r, xl, xr, yl == r ? r : a[d][yl].rc, yr == r ? r : a[d][yr].rc);
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

  int xl, xr, yl, yr;
  while (GetQuery(&xl, &yl, &xr, &yr)) {
    xl = lowerBoundX(b, b+n, xl) - b;
    xr = upperBoundX(b, b+n, xr) - b;
    yl = lowerBoundY(a[0], a[0]+n, yl) - a[0];
    yr = upperBoundY(a[0], a[0]+n, yr) - a[0];
    sum = cnt = 0;
    count(0, 0, n, xl, xr, yl, yr);
    Response(cnt ? int(sum/cnt) : 0);
  }
}
