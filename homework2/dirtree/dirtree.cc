#include <stdio.h>
#include <string.h>

const int N = 100000, M = 256;
char a[N][M];
size_t len[N], p[N], q[N];

void dfs(int d, int L, int R, int x)
{
  for (int j, i = L; i < R; i = j) {
    if (len[p[i]] < x) {
      j = i + 1;
      continue;
    }
    for (j = i; ++j < R; ) {
      int lcp = 0;
      while (a[p[i]][x+lcp] == a[p[j]][x+lcp] &&
          a[p[i]][x+lcp] && a[p[i]][x+lcp] != '/')
        lcp++;
      if (a[p[i]][x+lcp] && a[p[i]][x+lcp] != '/' ||
          a[p[j]][x+lcp] && a[p[j]][x+lcp] != '/')
        break;
    }
    int k = 0;
    printf("%*s", 2 * d, "");
    for (k = 0; a[p[i]][x+k] && a[p[i]][x+k] != '/'; k++)
      putchar(a[p[i]][x+k]);
    puts("");
    dfs(d + 1, i, j, x + k + 1);
  }
}

int main()
{
  int n;
  char path[256];
  scanf("%d%*c", &n);
  for (int i = 0; i < n; i++) {
    gets(a[i]);
    p[i] = i;
    len[i] = strlen(a[i]);
  }

  for (int k = 256; k--; ) {
    int c[256] = {};
#define f(x) (x == '/' ? 1 : x)
    for (int i = 0; i < n; i++)
      c[k < len[p[i]] ? f(a[p[i]][k]) : 0]++;
    for (int i = 1; i < 256; i++)
      c[i] += c[i-1];
    for (int i = n; i--; )
      q[--c[k < len[p[i]] ? f(a[p[i]][k]) : 0]] = p[i];
    memcpy(p, q, sizeof(*p) * n);
  }
  dfs(0, 0, n, 0);
}
