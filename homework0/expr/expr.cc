#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main()
{
  int a, b;
  char op;
  scanf("%d %c%d", &a, &op, &b);
  switch (op) {
  case '+':
    printf("%d\n", a + b);
    break;
  case '-':
    printf("%d\n", a - b);
    break;
  case '*':
    printf("%"PRId64"\n", (int64_t)a * b);
    break;
  }
}
