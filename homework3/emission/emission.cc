#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

const int M = 10000+2;

struct Node *pit, *null;
extern struct Node pool[M];
struct Node
{
  int key, size;
  int64_t sum;
  Node *ch[2];
  void *operator new(size_t) { Node *p = pit; pit = pit->ch[0]; return p; }
  int cmp_by_rank(int k) { return ch[0]->size == k ? -1 : ch[0]->size < k; }
  int cmp_by_key(int k) { return key == k ? -1 : key < k; }
  Node() {}
  Node(int key) : key(key), size(1), sum(key) { ch[0] = ch[1] = null; }
  void update() {
    size = ch[0]->size + 1 + ch[1]->size;
    sum = ch[0]->sum + key + ch[1]->sum;
  }
} pool[M];

void zag(Node *&x, int d)
{
  Node *y = x->ch[!d];
  x->ch[!d] = y->ch[d];
  y->ch[d] = x;
  x->update();
  x = y;
}

void splay_by_rank(Node *&x, int k)
{
  Node *rch[2] = {null, null};
  for(;;) {
    int d = x->cmp_by_rank(k);
    if (d == -1) break;
    if (d == 1) k -= x->ch[0]->size+1;
    if (d == x->ch[d]->cmp_by_rank(k)) {
      if (d) k -= x->ch[1]->ch[0]->size+1;
      zag(x, !d);
    }
    Node *y = x->ch[d];
    x->ch[d] = rch[!d];
    rch[!d] = x;
    x = y;
  }
  for (int d = 0; d < 2; d++) {
    Node *z = x->ch[d];
    while (rch[d] != null) {
      Node *y = rch[d]->ch[!d];
      rch[d]->ch[!d] = z;
      rch[d]->update();
      z = rch[d];
      rch[d] = y;
    }
    x->ch[d] = z;
  }
  x->update();
}

void splay_by_key(Node *&x, int k)
{
  Node *rch[2] = {null, null};
  for(;;) {
    int d = x->cmp_by_key(k);
    if (d == -1) break;
    if (x->ch[d] != null && d == x->ch[d]->cmp_by_key(k)) zag(x, !d);
    if (x->ch[d] == null) break;
    Node *y = x->ch[d];
    x->ch[d] = rch[!d];
    rch[!d] = x;
    x = y;
  }
  for (int d = 0; d < 2; d++) {
    Node *z = x->ch[d];
    while (rch[d] != null) {
      Node *y = rch[d]->ch[!d];
      rch[d]->ch[!d] = z;
      rch[d]->update();
      z = rch[d];
      rch[d] = y;
    }
    x->ch[d] = z;
  }
  x->update();
}

void insert(Node *&x, int k)
{
  if (x == null) {
    x = new Node(k);
    return;
  }
  splay_by_key(x, k);
  Node *y = new Node(k);
  int d = x->key < k;
  y->ch[d] = x->ch[d];
  x->ch[d] = null;
  y->ch[!d] = x;
  x->update();
  y->update();
  x = y;
}

void removeMin(Node *&x)
{
  splay_by_rank(x, 0);
  x->ch[0] = pit;
  pit = x;
  x = x->ch[1];
  if (x != null) x->update();
}

int main()
{
  pit = 0;
  for (int i = 0; i < M; i++) {
    pool[i].ch[0] = pit;
    pit = &pool[i];
  }
  null = new Node(0); null->size = 0;
  Node *root = null;

  int n, q, m, t;
  scanf("%d%d%d", &n, &q, &m);
  for (n += q; n--; ) {
    scanf("%d", &t);
    if (t < 0) {
      if (root->size <= - t)
        printf("%"PRId64"\n", root->sum);
      else {
        splay_by_rank(root, root->size + t - 1);
        printf("%"PRId64"\n", root->ch[1]->sum);
      }
    } else {
      insert(root, t);
      if (root->size > m)
        removeMin(root);
    }
  }
}
