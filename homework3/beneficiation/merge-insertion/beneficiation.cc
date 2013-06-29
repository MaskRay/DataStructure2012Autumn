#include <stdio.h>
#include <stdlib.h>
#include "beneficiation.h"

const int N = 10000, M = N + 2;
int a[N];

bool less(int i, int j)
{
  int a, b, c, d;
  Measure(i, j, -1, -1, &a, &b, &c, &d);
  return a < b;
}

template<typename T> void swap(T &a, T &b)
{ T c = a; a = b; b = c; }

template<typename T> void copy(T *first, T *last, T *out)
{ while (first < last) *out++ = *first++; }

void fordJohnson(int *l, int *r);

void insert(int *a, int n, int x)
{
  int l = 0, h = n, o[4];
  while (l < h) {
    int t1 = l + (h-l) / 3,
        t2 = h - (h-l) / 4;
    Measure(a[t1], a[t2-1], x, -1,
        &o[0], &o[1], &o[2], &o[3]);
    if (o[2] == -1)
      h = t1;
    else if (o[2] == 1)
      l = t2;
    else
      l = t1+1, h = t2-1;
  }
  for (; n > l; n--)
    a[n] = a[n-1];
  a[n] = x;
  //for (; n > 0 && less(x, a[n-1]); n--)
  //a[n] = a[n-1];
  //a[n] = x;
}

void excess4(int *l, int *r)
{
  int a[4], x[4], p = -1, q;
  int i, n = int(r - l);
  int *left = new int[n/4*2+3], *pleft = left,
      *right = new int[n/4*2], *pright = right,
      *mapping = new int[N];
  for (i = 0; i + 4 <= n; i += 4) {
    Measure(l[i], l[i+1], l[i+2], l[i+3], &a[0], &a[1], &a[2], &a[3]);
    bool flag = true;
    for (int j = 0; j < 4; j++) {
      if (a[j] == -1) pleft[0] = l[i+j];
      else if (a[j] == 1) pright[1] = l[i+j];
      else if (flag) flag = false, pleft[1] = l[i+j];
      else pright[0] = l[i+j];
    }
    pleft += 2;
    pright += 2;
  }

  for (; i < n; i++)
    *pleft++ = l[i];
  for (int i = 0; i < pright - right; i++)
    mapping[right[i]] = left[i];
  fordJohnson(right, right + n / 4 * 2);

  int size = 2;
  l[0] = mapping[right[0]];
  l[1] = right[0];
  for (i = 1; i + 2 <= pleft - left; i += 2) {
    if (i < n / 4 * 2)
      l[size++] = right[i];
    insert(l, size, i+1 < pright - right ? mapping[right[i+1]] : left[i+1]);
    size++;
    if (i + 1 < n / 4 * 2)
      l[size++] = right[i+1];
    insert(l, size, i < pright - right ? mapping[right[i]] : left[i]);
    size++;
  }
  if (i < pleft - left) {
    if (i < n / 4 * 2)
      l[size++] = right[i];
    insert(l, size, i < pright - right ? mapping[right[i]] : left[i]);
  }
}

void fordJohnson(int *l, int *r)
{
  int a[4], x[4], p = -1, q;
  if (l + 1 >= r) return;
  switch (r - l) {
  case 2:
    if (less(l[1], *l)) swap(*l, l[1]);
    break;
  case 3:
    Measure(*l, l[1], l[2], -1, &a[0], &a[1], &a[2], &a[3]);
    copy(l, l + 3, x);
    for (int i = 0; i < 3; i++)
      l[a[i] + 1] = x[i];
    break;
  case 4:
    Measure(*l, l[1], l[2], l[3], &a[0], &a[1], &a[2], &a[3]);
    copy(l, l + 4, x);
    for (int i = 0; i < 4; i++) {
      if (a[i] == -1) l[0] = x[i];
      else if (a[i] == 1) l[3] = x[i];
      else (p == -1 ? p : q) = x[i];
    }
    if (less(p, q)) l[1] = p, l[2] = q;
    else l[1] = q, l[2] = p;
    break;
  default:
    excess4(l, r);
    break;
  }
}

int main()
{
  int n;
  while ((n = GetNumOfOre()) > 0) {
    for (int i = 0; i < n; i++)
      a[i] = n-1-i;
    fordJohnson(a, a+n);
    for (int i = 0; i < n; i++)
      Report(a[i], n-1-i);
  }
}
