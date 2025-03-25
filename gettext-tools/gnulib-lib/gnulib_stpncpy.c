#include <config.h>

/* Specification.  */
#include <string.h>

/* Copy no more than N bytes of SRC to DST, returning a pointer past the
   last non-NUL byte written into DST.  */
char *
gnulib_stpncpy (char *dest, const char *src, size_t n)
{
  char c;
  char *s = dest;

  if (n >= 4)
    {
      size_t n4 = n >> 2;

      for (;;)
	{
	  c = *src++;
	  *dest++ = c;
	  if (c == '\0')
	    break;
	  c = *src++;
	  *dest++ = c;
	  if (c == '\0')
	    break;
	  c = *src++;
	  *dest++ = c;
	  if (c == '\0')
	    break;
	  c = *src++;
	  *dest++ = c;
	  if (c == '\0')
	    break;
	  if (--n4 == 0)
	    goto last_chars;
	}
      n -= dest - s;
      goto zero_fill;
    }

 last_chars:
  n &= 3;
  if (n == 0)
    return dest;

  for (;;)
    {
      c = *src++;
      --n;
      *dest++ = c;
      if (c == '\0')
	break;
      if (n == 0)
	return dest;
    }

 zero_fill:
  while (n-- > 0)
    dest[n] = '\0';

  return dest - 1;
}   