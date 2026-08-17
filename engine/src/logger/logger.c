#include "logger/logger.h"

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MSG_PFX_FMT "[%s] [Dackel2D] [%s%s%s] [%s:%d]: %s"
#define MSG_ARGS get_timestamp(), color, type, END, file, line, msg

static char *vfstrbufalloc(const char *fmt, va_list args)
{
    // vsnprintf() consumes the va_list.
    // Make a copy and work with that.
    va_list copy;
    va_copy(copy, args); 

    int size = vsnprintf(NULL, 0, fmt, copy);
    va_end(copy);

    // Alloc space the size of string + '\0'.
    return malloc(size + 1);
}

static char *fstrbufalloc(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char *buffer = vfstrbufalloc(fmt, args);
    va_end(args);

    return buffer;
}

const char *get_timestamp()
{
    time_t now = time(NULL);
    struct tm *time = localtime(&now);

    static char buffer[24];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time);

    return buffer;
}

void log_message(FILE *stream, const char *type, const char *file, int line, const char *color, const char *fmt, ...)
{
    va_list msg_args;
    va_start(msg_args, fmt);

    char *msg = vfstrbufalloc(fmt, msg_args);
    va_end(msg_args);

    vsprintf(msg, fmt, msg_args);

    char *ln = fstrbufalloc(MSG_PFX_FMT, MSG_ARGS);
    sprintf(ln, MSG_PFX_FMT, MSG_ARGS);

    fprintf(stream, "%s\n", ln);

    free(msg);
    free(ln);
}
