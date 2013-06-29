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

void mergeSort(int *l, int *r);

void excess4(int *l, int *r)
{
  int rank[4], *p[4], *q[4], n = r - l, *seq = new int[n], *pseq = seq;
  int buf[4], *pbuf = buf;
  for (int i = 0; i < 4; i++) {
    p[i] = l + n * i / 4;
    q[i] = l + n * (i+1) / 4;
    mergeSort(p[i], q[i]);
  }
  for (; n > 4; n--) {
    Measure(*p[0], *p[1], *p[2], *p[3], &rank[0], &rank[1], &rank[2], &rank[3]);
    for (int i = 0; i < 4; i++)
      if (rank[i] == -1) {
        *pseq++ = *p[i]++;
        if (p[i] == q[i]) {
          int idx, maxl = 0;
          for (int j = 0; j < 4; j++)
            if (q[j]-p[j] > maxl)
              maxl = q[j]-p[j], idx = j;
          q[idx] = p[i] = p[idx] + maxl/2;
          q[i] = p[idx] + maxl;
        }
        break;
      }
  }
  for (int i = 0; i < 4; i++)
    while (p[i] < q[i])
      *pbuf++ = *p[i]++;
  mergeSort(buf, pbuf);
  copy(buf, pbuf, pseq);
  copy(seq, seq + (r-l), l);
}

void mergeSort(int *l, int *r)
{
  int rank[4], x[4], p = -1, q;
  if (l + 1 >= r) return;
  switch (r - l) {
  case 2:
    if (less(l[1], *l)) swap(*l, l[1]);
    break;
  case 3:
    Measure(*l, l[1], l[2], -1, &rank[0], &rank[1], &rank[2], &rank[3]);
    copy(l, l + 3, x);
    for (int i = 0; i < 3; i++)
      l[rank[i] + 1] = x[i];
    break;
  case 4:
    Measure(*l, l[1], l[2], l[3], &rank[0], &rank[1], &rank[2], &rank[3]);
    copy(l, l + 4, x);
    for (int i = 0; i < 4; i++) {
      if (rank[i] == -1) l[0] = x[i];
      else if (rank[i] == 1) l[3] = x[i];
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
    mergeSort(a, a+n);
    for (int i = 0; i < n; i++)
      Report(a[i], n-1-i);
  }
}
