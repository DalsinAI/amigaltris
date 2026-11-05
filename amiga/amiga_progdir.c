/* PROGDIR: itself can't take upstream's "/name" joins ("PROGDIR:/x" is the
 * parent drawer), and a name handed to another process (SDL's modules, the
 * decoders) must be a full path anyway, so the drawer's full name is taken
 * once with NameFromLock().
 * The AmiCradle Team. GPL 2 or later, like LTris. */
#include <exec/types.h>
#include <dos/dos.h>
#include <proto/dos.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "amiga_port.h"

static char dir[512];

const char *amiga_progdir(void)
{
	if (!dir[0]) {
		BPTR lock = GetProgramDir();
		size_t n;
		if (!lock || !NameFromLock(lock, (STRPTR)dir, sizeof(dir) - 1))
			strcpy(dir, "PROGDIR:");
		n = strlen(dir);
		if (n > 1 && dir[n - 1] == '/')
			dir[n - 1] = 0;
	}
	return dir;
}

int vasprintf(char **out, const char *fmt, va_list ap)
{
	char small[256];
	va_list again;
	int n;

	va_copy(again, ap);
	n = vsnprintf(small, sizeof(small), fmt, ap);
	*out = NULL;
	if (n < 0) {
		va_end(again);
		return -1;
	}
	*out = malloc(n + 1);
	if (!*out) {
		va_end(again);
		return -1;
	}
	if ((size_t)n < sizeof(small))
		memcpy(*out, small, n + 1);
	else
		vsnprintf(*out, n + 1, fmt, again);
	va_end(again);
	return n;
}
