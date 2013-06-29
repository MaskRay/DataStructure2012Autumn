#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

const int N = 100, M = 10000, K = 20, ANTS = 10;
const double phi = 0.03;
bool visited[N];
int score[N][K], demand[K], achieve[K];
double pheromone[N];
struct Edge { bool visited; double pheromone; int v, w, score[K]; Edge *next, *dual; } *e[N], edge[M*2], *pre[N];
struct Path { double len; int m, a[M*2]; } path, opt;

template<typename T> void fill_n(T *a, int n, T x)
{ for (int i = 0; i < n; i++) a[i] = x; }

bool satisfy(int k)
{
  for (int i = 0; i < k; i++)
    if (achieve[i] < demand[i])
      return false;
  return true;
}

bool walk(int n, int m, int k, int src, int sink)
{
  static double prob[M];
  bool satisfied;
  int u = src;

  path.m = 1;
  path.len = 0.0;
  path.a[0] = ~ u;
  fill_n(visited, n, false);
  visited[src] = visited[sink] = true;
  for (int i = 0; i < m*2; i++)
    edge[i].visited = false;
  fill_n(achieve, k, 0);

  while (! satisfy(k)) {
    Edge *i;
    double prob_sum = 0.0, rnd;
    int c = 0;
    for (i = e[u]; i; i = i->next) {
      prob[c] = ((! visited[i->v] ? pheromone[i->v] : 0) + (! i->visited ? i->pheromone : 0)) / (i->w + 1.0);
      prob_sum += prob[c++];
    }

    rnd = rand() / (RAND_MAX+1.0) * prob_sum;
    c = 0;
    for (i = e[u]; i; i = i->next) {
      rnd -= prob[c++];
      if (rnd <= 0 || ! i->next) break;
    }

L1:
    if (path.m + 2 > M * 2) return false;
    u = i->v;
    path.len += i->w;
    path.a[path.m++] = i-edge;
    path.a[path.m++] = ~ u;
    pheromone[u] = (1-phi) * pheromone[u] + phi;
    i->pheromone = (1-phi) * i->pheromone + phi;
    if (! visited[u]) {
      visited[u] = true;
      for (int j = 0; j < k; j++)
        achieve[j] += score[u][j];
    }
    if (! i->visited) {
      i->visited = i->dual->visited = true;
      for (int j = 0; j < k; j++)
        achieve[j] += i->score[j];
    }
  }

  while (u != sink) {
    if (path.m + 2 > M * 2) return false;
    Edge *i = pre[u];
    u = i->v;
    path.len += i->w;
    path.a[path.m++] = i-edge;
    path.a[path.m++] = ~ u;
    pheromone[u] = (1-phi) * pheromone[u] + phi;
    i->pheromone = (1-phi) * i->pheromone + phi;
  }
  return true;
}

void aco(int n, int m, int k, int src, int sink)
{
  struct timeval start, now;
  gettimeofday(&start, NULL);
  double calc_time = pow(n*m, 1.0/6) * 1e6 * 0.7;
  //calc_time = 1e6;

  opt.len = INT_MAX;
  fill_n(pheromone, n, 1.0);
  for (int i = 0; i < m * 2; i++)
  edge[i].pheromone = 0.0;
  for (int times = 0; ; ) {
    for (int ant = 0; ant < ANTS; ant++)
      if (walk(n, m, k, src, sink) && path.len < opt.len) {
        opt.len = path.len;
        opt.m = path.m;
        for (int i = 0; i < opt.m; i++)
          opt.a[i] = path.a[i];
      }
    const double Q = opt.len < INT_MAX ? opt.len / 3.0 : 100;
    for (int i = 0; i < opt.m; i++)
      if (i % 2)
        edge[opt.a[i] % m].pheromone += Q / opt.len;
      else
        pheromone[~ opt.a[i]] += Q / opt.len;
    fprintf(stderr, "v: ");
    for (int i = 0; i < n; i++)
      fprintf(stderr, "%.4lf%c", pheromone[i], i==n-1?'\n':' ');
    fprintf(stderr, "e: ");
    for (int i = 0; i < m*2; i++)
      fprintf(stderr, "%.4lf%c", edge[i].pheromone, i==m*2-1?'\n':' ');
    if (++times >= 5) {
      times = 0;
      gettimeofday(&now, NULL);
      if (now.tv_usec < start.tv_usec) {
        now.tv_usec += 1000000;
        now.tv_sec--;
      }
      if (now.tv_usec-start.tv_usec + (now.tv_sec-start.tv_sec)*1e6 > calc_time)
        break;
    }
  }
}

void dijkstra(int n, int sink)
{
  static int dist[N];
  fill_n(dist, n, INT_MAX);
  fill_n(visited, n, false);
  dist[sink] = 0;
  for(;;) {
    int u = -1, mind = INT_MAX;
    for (int v = 0; v < n; v++)
      if (! visited[v] && dist[v] < mind)
        mind = dist[u = v];
    if (u == -1) break;
    visited[u] = true;
    for (Edge *i = e[u]; i; i = i->next)
      if (dist[u] + i->w < dist[i->v]) {
        dist[i->v] = dist[u] + i->w;
        pre[i->v] = i->dual;
      }
  }
}

int main()
{
  int n, m, k, src, sink;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < k; j++)
      scanf("%d", &score[i][j]);
  for (int i = 0; i < m; i++) {
    int w, u, v;
    scanf("%d%d%d", &w, &u, &v);
    for (int j = 0; j < k; j++) {
      scanf("%d", &edge[i].score[j]);
      edge[m+i].score[j] = edge[i].score[j];
    }
    edge[i].v = v;
    edge[i].w = w;
    edge[i].next = e[u];
    edge[i].dual = &edge[m+i];
    e[u] = &edge[i];
    edge[m+i].v = u;
    edge[m+i].w = w;
    edge[m+i].next = e[v];
    edge[m+i].dual = &edge[i];
    e[v] = &edge[m+i];
  }
  scanf("%d%d", &src, &sink);
  for (int i = 0; i < k; i++)
    scanf("%d", &demand[i]);

  dijkstra(n, sink);
  aco(n, m, k, src, sink);
  for (int i = 0; i < opt.m; i++) {
    if (opt.a[i] < 0)
      printf("C%d", ~ opt.a[i]);
    else
      printf("R%d", opt.a[i] % m);
    putchar(i == opt.m - 1 ? '\n' : ' ');
  }
}
