#include <stdio.h>

#define READ_INT(_x)					\
  {							\
    int _tmp = 0;					\
    register int _ch = getchar_unlocked();		\
    while (_ch < 48 || _ch > 57)			\
      _ch = getchar_unlocked();				\
    while (48 <= _ch && _ch <= 57)			\
      {							\
	_tmp = (_tmp << 3) + (_tmp << 1) + _ch - 48;	\
	_ch = getchar_unlocked();			\
      }							\
    (_x) = _tmp;					\
  }							\

char _str[10];
#define WRITE_INT(_x)				\
  {						\
    register int _i = 0;			\
    long long _tmp = (_x);			\
    do						\
      {						\
	*(_str + _i++) = _tmp % 10 + 48;	\
	_tmp /= 10;				\
      } while (_tmp != 0);			\
    for (_i--; _i >= 0; _i--)			\
      putchar_unlocked(*(_str + _i));		\
  }						\

int main(void)
{
  int i, min, n, t, x;

  READ_INT(t);
  while (t--)
    {
      READ_INT(n);

      READ_INT(min);
      for (i = 1; i < n; i++)
	{
	  READ_INT(x);
	  if (x < min)
	    min = x;
	}

      WRITE_INT((n - 1) * (long long) min);
      putchar_unlocked('\n');
    }

  return 0;
}
