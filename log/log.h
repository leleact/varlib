#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <time.h>
#include <sys/time.h>
#include <sys/timeb.h>

size_t log(FILE *fp, int log_level, char *format, ...);

