/* A Shell gives 4 KB of stack; libnix's startup sets this much up instead.
 * The AmiCradle Team. GPL 2 or later, like LTris. */
unsigned long __stack = 256 * 1024;
static const char version[] __attribute__((used)) = "$VER: LTris 2.0.4 Amiga (05.11.2026)";
