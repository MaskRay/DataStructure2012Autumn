#include <stdio.h>
#include <string.h>

int main()
{
  char a[20000];
  int n, m;
  scanf("%s%d", a, &m);
  n = int(strlen(a));
  while (m--) {
    int x;
    scanf("%d", &x);
    memmove(a+x+1, a+x, n-x);
    n++;
    scanf(" %c", &a[x]);
    for(;;) {
      int l = x, r = x + 1;
      while (l && a[l-1] == a[x]) l--;
      while (r < n && a[r] == a[x]) r++;
      if (r-l < 3) break;
      memmove(a+l, a+r, n-r);
      n -= r-l;
      if (l == 0) break;
      x = l-1;
    }
    if (n == 0)
      puts("-");
    else {
      a[n] = '\0';
      puts(a);
    }
  }
}
