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

void heapDown(int *a, int n, int x)
{
  int r[4], key = a[x];
  for (int y; y = x*3+1, y < n; x = y) {
    Measure(key, a[y], y+1 < n ? a[y+1] : -1, y+2 < n ? a[y+2] : -1,
        &r[0], &r[1], &r[2], &r[3]);
    if (r[0] == 1) break;
    y = r[1] == 1 ? y : r[2] == 1 ? y+1 : y+2;
    a[x] = a[y];
  }
  a[x] = key;
}

void heapSort(int *a, int n)
{
  for (int i = (n-1)/3; i >= 0; i--)
    heapDown(a, n, i);
  while (n > 1) {
    swap(a[--n], a[0]);
    heapDown(a, n, 0);
  }
}

int main()
{
  int n;
  while ((n = GetNumOfOre()) > 0) {
    for (int i = 0; i < n; i++)
      a[i] = n-1-i;
    heapSort(a, n);
    for (int i = 0; i < n; i++)
      Report(a[i], n-1-i);
  }
}
