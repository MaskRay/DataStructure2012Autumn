#include <stdio.h>

struct Stream
{
  bool evaluated;
  int car;
  union {
    Stream *cdr;
    Stream *f;
  };
  Stream *r, *s;
  void evaluate() {
    if (! evaluated) {
      r->evaluate();
      evaluated = true;
      if (f == NULL) {
        car = r->car;
        cdr = s;
      } else {
        f->evaluate();
        car = f->car;
        cdr = new Stream(f->cdr, r->cdr, new Stream(r->car, s));
      }
    }
  }
  Stream(int car, Stream *cdr) : car(car), cdr(cdr), evaluated(true) {}
  Stream(Stream *f, Stream *r, Stream *s) : f(f), r(r), s(s), evaluated(false) {}
};

class Queue
{
public:
  Queue() : f(NULL), r(NULL), s(NULL) {}
  bool empty() { return f == NULL; }
  int head() {
    f->evaluate();
    return f->car;
  }
  Queue pop() {
    f->evaluate();
    return make(f->cdr, r, s);
  }
  Queue push(int x) { return make(f, new Stream(x, r), s); }
private:
  Stream *f, *r, *s;
  Queue make(Stream *f, Stream *r, Stream *s) {
    Queue q;
    if (s == NULL) {
      Stream *f_ = new Stream(f, r, NULL);
      q.f = q.s = f_;
      q.r = NULL;
    } else {
      s->evaluate();
      q.f = f;
      q.r = r;
      q.s = s->cdr;
    }
    return q;
  }
};

int main()
{
  int n, m = 1;
  scanf("%d", &n);
  Queue *qs = new Queue[n+1];
  while (n--) {
    char op;
    int p, x;
    scanf(" %c%d", &op, &p);
    if (op == 'a') {
      scanf("%d", &x);
      qs[m++] = qs[p].push(x);
    } else if (qs[p].empty()) {
      puts("-1");
      m++;
    } else {
      printf("%d\n", qs[p].head());
      qs[m++] = qs[p].pop();
    }
  }
}
