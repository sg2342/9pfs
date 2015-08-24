#include <sys/types.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <err.h>
#include <errno.h>

void*
emalloc(size_t size)
{
	void	*v;

	if((v = malloc(size)) == NULL)
		err(1, "emalloc: out of memory");
	memset(v, 0, size);
	return v;
}


void*
erealloc(void *p, size_t size)
{
	void	*v;

	if((v = realloc(p, size)) == NULL)
		err(1, "emalloc: out of memory");
	return v;
}

void*
ecalloc(size_t nmemb, size_t size)
{
	void 	*v;

	if((v = calloc(nmemb, size)) == NULL)
		err(1, "ecalloc: out of memory");
	return v;
}

#define MUL_NO_OVERFLOW	((size_t)1 << (sizeof(size_t) * 4))

void*
ereallocarray(void *optr, size_t nmemb, size_t size)
{
	if ((nmemb >= MUL_NO_OVERFLOW || size >= MUL_NO_OVERFLOW) &&
	    nmemb > 0 && SIZE_MAX / nmemb < size) {
		errno = ENOMEM;
		err(1, "erallocarray: out of memory");
	}
	return erealloc(optr, size * nmemb);
}

/*
 *void*
 *ereallocarray(void *ptr, size_t nmemb, size_t size)
 *{
 *	void	*v;
 *
 *	if((v = reallocarray(ptr, nmemb, size)) == NULL)
 *		err(1, "ereallocarray: out of memory");
 *	return v;
 *}
 */

char*
estrdup(const char *s)
{
	char	*r;

	if((r = strdup(s)) == NULL)
		err(1, "estrdup: out of memory");
	return r;
}

void
dprint(char *fmt, ...)
{
	char	*s;
	va_list	va;

	if(debug == 0)
		return;
	va_start(va, fmt);
	vasprintf(&s, fmt, va);
	va_end(va);
	fprintf(logfile, "%s\n", s);
	free(s);
	return;
}
