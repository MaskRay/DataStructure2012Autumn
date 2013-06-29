#include <inttypes.h>
#include <stdio.h>

typedef int64_t ll;

int main()
{
  int n, m ;
  scanf("%d%d", &n, &m);

  int a = 0, b = 1, c = 1,
      p = 1, q = 1;
  for (; n; n /= 2) {
    if (n%2) {
      int pp = (ll(a)*p+ll(b)*q) % m,
          qq = (ll(b)*p+ll(c)*q) % m;
      p = pp;
      q = qq;
    }
    int aa = (ll(a)*a+ll(b)*b) % m,
        bb = ll(a+c)*b % m,
        cc = (ll(b)*b+ll(c)*c) % m;
    a = aa;
    b = bb;
    c = cc;
  }
  printf("%d\n", p);
}
