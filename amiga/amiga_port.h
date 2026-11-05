/* What the Amiga build gives every LTris source file (-include).
 * The AmiCradle Team. GPL 2 or later, like LTris. */
#ifndef AMIGA_PORT_H
#define AMIGA_PORT_H
#include <stdarg.h>
#ifdef __cplusplus
extern "C" {
#endif
/* The full name of the program's drawer ("Work:Games/LTris"), without a
 * trailing slash, so that upstream's DATADIR "/themes" joins stay valid:
 * data, settings and highscores all live there. */
const char *amiga_progdir(void);
/* libnix has no vasprintf (tools.cpp's strprintf). */
int vasprintf(char **out, const char *fmt, va_list ap);
#ifdef __cplusplus
}
#endif
#endif
