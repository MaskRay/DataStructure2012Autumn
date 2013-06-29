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
  y->update();
  x = y;
}

void maintain(Node *&x, int d)
{
  if (x == null) return;
  if (x->ch[d]->ch[d]->size > x->ch[!d]->size)
    zag(x, !d);
  else if (x->ch[d]->ch[!d]->size > x->ch[!d]->size)
    zag(x->ch[d], d), zag(x, !d);
  else
    return;
  maintain(x->ch[0], 0);
  maintain(x->ch[1], 1);
  maintain(x, 0);
  maintain(x, 1);
}

bool check(Node *x)
{
  if (x == null)
    return x->size == 0;
  return x->size == x->ch[0]->size + 1 + x->ch[1]->size;
}

void insert(Node *&x, int key)
{
  if (x == null)
    x = new Node(key);
  else {
    int d = x->key < key;
    x->size++;
    x->sum += key;
    insert(x->ch[d], key);
    maintain(x, d);
  }
}

void removeMin(Node *&x)
{
  if (x->ch[0] == null) {
    x->ch[0] = pit;
    pit = x;
    x = x->ch[1];
  } else {
    removeMin(x->ch[0]);
    x->update();
  }
}

int64_t suffixSum(Node *x, int k)
{
  if (x == null) return 0;
  int64_t s = 0;
  if (x->ch[0]->size < k)
    s += suffixSum(x->ch[1], k - x->ch[0]->size - 1);
  else {
    s += x->key + x->ch[1]->sum;
    s += suffixSum(x->ch[0], k);
  }
  return s;
}

int main()
{
  pit = 0;
  for (int i = 0; i < M; i++) {
    pool[i].ch[0] = pit;
    pit = &pool[i];
  }
  null = new Node(0);
  null->size = 0;
  null->ch[0] = null->ch[1] = null;
  Node *root = null;

  int n, q, m, t;
  scanf("%d%d%d", &n, &q, &m);
  for (n += q; n--; ) {
    scanf("%d", &t);
    if (t < 0) {
      if (root->size <= - t)
        printf("%"PRId64"\n", root->sum);
      else
        printf("%"PRId64"\n", suffixSum(root, root->size + t));
    } else {
      insert(root, t);
      if (root->size > m)
        removeMin(root);
    }
  }
}
