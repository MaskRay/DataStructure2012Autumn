#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <utility>

const int N = 100000;

typedef std::pair<int, char> pic;
pic a[N + 1];
int hit[N + 1], fault[N + 1];

int cmpPic(const void* l, const void* r)
{
  return ((pic*)l)->first - ((pic*)r)->first;
}

int searchHit(int n, int cnt)
{
  if (hit[0] < cnt) return -1;
  int l = 0, h = n;
  while (l < h) {
    int m = l + h + 1 >> 1;
    if (hit[m] >= cnt) l = m;
    else h = m - 1;
  }
  return a[l].first;
}

int searchFault(int n, int cnt)
{
  int l = 0, h = n;
  while (l < h) {
    int m = l + h >> 1;
    if (fault[m] > cnt) l = m + 1;
    else h = m;
  }
  return l == 0 ? 0 : a[l-1].first + 1;
}

int main()
{
  int n, m, nhealth = 0, nsick = 0;
  scanf("%d", &n);
  scanf("%d", &a[n].first);
  for (int i = 0; i < n; i++) {
    scanf("%d %c", &a[i].first, &a[i].second);
    if (a[i].second == '-')
      nhealth++;
    else
      nsick++;
  }
  qsort(a, n, sizeof *a, cmpPic);

  hit[n] = 0;
  fault[n] = 0;
  for (int i = n; i--; ) {
    hit[i] = hit[i+1] + (a[i].second == '+');
    fault[i] = fault[i+1] + (a[i].second == '-');
  }

  scanf("%d", &m);
  while (m--) {
    double hit_rate, fault_rate;
    scanf("%lf%lf", &hit_rate, &fault_rate);
    int hit_cnt = ceil(hit_rate * nsick),
        fault_cnt = floor(fault_rate * nhealth);
    int r = searchHit(n, hit_cnt),
        l = searchFault(n, fault_cnt);
    if (l > r)
      puts("-1");
    else
      printf("%d %d\n", l, r);
  }
}
