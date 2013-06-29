#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node { int ch[2], sg; };

int main()
{
  char line[64+1];
  int n, last = 0, last_res = -1, pit = 1, size, bs[64];
  scanf("%d%*c", &n);
  size = n;
  Node *a = (Node *)malloc(sizeof(Node) * size);
  a[0].ch[0] = a[0].ch[1] = -1;
  for (int w = 0; w < n; w++) {
    gets(line);
    int i, p = 0;
    for (i = 0; line[i]; i++) {
      bs[i] = p;
      if (a[p].ch[line[i]-'0'] == -1) {
        if (pit == size) {
          size *= 2;
          a = (Node *)realloc(a, sizeof(Node) * size);
        }
        a[pit].sg = 0;
        a[pit].ch[0] = a[pit].ch[1] = -1;
        a[p].ch[line[i]-'0'] = pit++;
      }
      p = a[p].ch[line[i]-'0'];
    }
    while (i--) {
      a[bs[i]].sg = 0;
      for (int j = 0; j < 2; j++)
        if (a[bs[i]].ch[j] != -1 && ! a[a[bs[i]].ch[j]].sg)
          a[bs[i]].sg = 1;
    }
    if (last_res == -1)
      last_res = a->sg;
    if (a->sg != last_res) {
      printf("%s %d %d\n", last_res ? "Adam" : "Eve", last + 1, w);
      last = w;
      last_res = a->sg;
    }
  }
  printf("%s %d %d\n", last_res ? "Adam" : "Eve", last + 1, n);
  free(a);
}
