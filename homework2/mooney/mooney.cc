#include <stdio.h>

const int N = 500000, M = 1200000;
char line[N+1];

struct Edge { int v; Edge *next; } *e[N], pool[M];

int n;
int scc[N], nscc;
int dfn[N], tick;
int dp[N];

void gabow(int u)
{
  static int S[N], SS[N], nS = 0, nSS = 0;
  dfn[u] = tick++;
  S[nS++] = u;
  SS[nSS++] = u;
  for (Edge *i = e[u]; i; i = i->next)
    if (dfn[i->v] == -1)
      gabow(i->v);
    else if (scc[i->v] == -1)
      while (dfn[i->v] < dfn[SS[nSS-1]])
        nSS--;
  if (nSS && SS[nSS-1] == u) {
    int v, max_reach = -1;
    nSS--;
    dp[nscc] = 0;
    do {
      v = S[--nS];
      scc[v] = nscc;
      if (line[v] == 'm')
        dp[nscc]++;
      if (v == n-1)
        max_reach = 0;
      for (Edge *i = e[v]; i; i = i->next)
        if (scc[i->v] != -1 && scc[i->v] != scc[v] && dp[scc[i->v]] > max_reach)
          max_reach = dp[scc[i->v]];
    } while (v != u);
    if (max_reach == -1)
      dp[nscc] = -1;
    else
      dp[nscc] += max_reach;
    nscc++;
  }
}

int bfs()
{
  static int q[2*N], d[N];
  int *fore = q+N, *rear = q+N;
  for (int i = 0; i < n; i++)
    d[i] = -1;
  d[0] = line[0] == 'M';
  *rear++ = 0;
  for (int c = 0; fore < rear; ) {
    int u = *fore++;
    if (u == n-1) break;
    for (Edge *i = e[u]; i; i = i->next)
      if (d[i->v] == -1) {
        if (line[i->v] == 'M') {
          d[i->v] = d[u] + 1;
          *rear++ = i->v;
        } else {
          d[i->v] = d[u];
          *--fore = i->v;
        }
      }
  }
  return d[n-1];
}

int main()
{
  int m;
  scanf("%d%d%s", &n, &m, line);
  Edge *pit = pool;
  while (m--) {
    int u, v;
    scanf("%d%d", &u, &v);
    *pit = (Edge){v, e[u]};
    e[u] = pit++;
  }

  printf("%d\n", bfs());

  tick = nscc = 0;
  for (int i = 0; i < n; i++)
    dfn[i] = scc[i] = -1;
  for (int i = 0; i < n; i++)
    if (dfn[i] == -1)
      gabow(i);
  printf("%d\n", dp[scc[0]]);
}
