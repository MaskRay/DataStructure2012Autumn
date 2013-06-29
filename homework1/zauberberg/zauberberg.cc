#include <utility>
#include <stdio.h>
#include <stdlib.h>

const int N = 200000;

typedef std::pair<int, char> pic;
typedef long long ll;
pic a[N];
struct Q { int id, l, r, hit, fls; } b[N];

int cmpPic(const void* l, const void* r)
{
  return ((pic*)l)->first - ((pic*)r)->first;
}

int cmpHit(const void* l, const void* r)
{
  return ((Q*)l)->hit - ((Q*)r)->hit;
}

int cmpFls(const void* l, const void* r)
{
  return ((Q*)r)->fls - ((Q*)l)->fls;
}

int cmpId(const void* l, const void* r)
{
  return ((Q*)l)->id - ((Q*)r)->id;
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

  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    int p, q, r, s;
    scanf("%d.%d%d.%d", &p, &q, &r, &s);
    b[i].hit = p * 1000000 + q;
    b[i].fls = r * 1000000 + s;
    b[i].id = i;
    b[i].l = a[n].first + 1;
    b[i].r = -1;
  }

  qsort(b, m, sizeof *b, cmpHit);
  for (int c = 0, j = 0, i = n; i >= 0; i--) {
    c += a[i].second == '+';
    for (; j < m && ll(b[j].hit) * nsick <= c * 1000000LL; j++)
      b[j].r = a[i].first;
  }

  qsort(b, m, sizeof *b, cmpFls);
  for (int c = nhealth, j = 0, i = 0; i <= n; i++) {
    for (; j < m && ll(b[j].fls) * nhealth >= c * 1000000LL; j++)
      b[j].l = i == 0 ? 0 : a[i-1].first + 1;
    c -= a[i].second == '-';
  }

  qsort(b, m, sizeof *b, cmpId);
  for (int i = 0; i < m; i++) {
    if (b[i].l > b[i].r)
      puts("-1");
    else
      printf("%d %d\n", b[i].l, b[i].r);
  }
}
