#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

const int M = 10000;
int size, a[M];

void heap_down(int x)
{
  int key = a[x];
  for (int y; y = 2*x+1, y < size; ) {
    if (y+1 < size && a[y+1] < a[y]) y++;
    if (!(a[y] < key)) break;
    a[x] = a[y];
    x = y;
  }
  a[x] = key;
}

void heap_push(int key)
{
  int x = size++;
  for (int y; y = (x-1)/2, x && key < a[y]; x = y)
    a[x] = a[y];
  a[x] = key;
}

int main()
{
  int n, q, m, t;
  scanf("%d%d%d", &n, &q, &m);
  for (n += q; n--; ) {
    scanf("%d", &t);
    if (t < 0) {
      int64_t s = 0;
      int size2 = size;
      while (size > 1) {
        q = a[0];
        a[0] = a[--size];
        a[size] = q;
        heap_down(0);
      }
      size = size2;
      for (t = -t < size ? -t : size; t > 0; )
        s += a[--t];
      for (int i = 0, j = size; i < --j; i++) {
        q = a[i];
        a[i] = a[j];
        a[j] = q;
      }
      printf("%"PRId64"\n", s);
    } else {
      if (size < m)
        heap_push(t);
      else if (t > a[0]) {
        a[0] = t;
        heap_down(0);
      }
    }
  }
}
