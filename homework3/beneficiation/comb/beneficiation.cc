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

void combSort(int *a, int n)
{
  int gap = n;
  bool flag = false;
  while (gap > 1 || flag) {
    gap = int(gap / 1.247330950103979);
    if (gap < 1) gap = 1;
    flag = false;
    int i;
    for (i = 0; i + gap < n; i++)
      if (less(a[i+gap], a[i])) {
        swap(a[i], a[i+gap]);
        flag = true;
      }
  }
}

int main()
{
  int n;
  while ((n = GetNumOfOre()) > 0) {
    for (int i = 0; i < n; i++)
      a[i] = n-1-i;
    combSort(a, n);
    for (int i = 0; i < n; i++)
      Report(a[i], n-1-i);
  }
}
