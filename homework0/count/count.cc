#include <ctype.h>
#include <stdio.h>

int main()
{
  char line[4096 + 1];
  int c[26] = {};
  gets(line);
  for (char* p = line; *p; p++)
    if (islower(*p))
      c[*p - 'a']++;
    else if (isupper(*p))
      c[*p - 'A']++;
  for (char i = 'A'; i <= 'Z'; i++)
    if (c[i - 'A'] > 0)
      printf("%c: %d\n", i, c[i - 'A']);
}
