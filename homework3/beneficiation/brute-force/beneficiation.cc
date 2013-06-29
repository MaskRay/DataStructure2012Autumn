#include <stdio.h>
#include <stdlib.h>
#include "beneficiation.h"

const int N = 10000;
int a[N];

bool less(int i, int j)
{
  int a, b, c, d;
  Measure(i, j, -1, -1, &a, &b, &c, &d);
  return a < b;
}

void quickSort(int *l, int *r)
{
  if (l + 1 >= r) return;
  int *i = l, *j = r-1, x = l[(r-l)/2];
  while (i < j) {
    while (less(*i, x)) i++;
    while (less(x, *j)) j--;
    if (i <= j) {
      int t = *i;
      *i++ = *j;
      *j-- = t;
    }
  }
  quickSort(l, j+1);
  quickSort(i, r);
}

int main()
{
  int n;
  while ((n = GetNumOfOre()) > 0) {
    for (int i = 0; i < n; i++)
      a[i] = i;
    quickSort(a, a+n);
    for (int i = 0; i < n; i++)
      Report(a[i], n-1-i);
  }
}
