#include "logger/logger.h"

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static char *vmakefstr(const char *fmt, va_list args)
{
    // vsnprintf() consumes the va_list - make a copy 
    // and calculate formatted string length with that.
    va_list copy;
    va_copy(copy, args);

    // Length of formatted string is equal to the 
    // total number of characters plus one more 
    // for the null terminator ('\0').
    int strsize = vsnprintf(NULL, 0, fmt, copy) + 1;
    va_end(copy);

    char *fstr = malloc(strsize);
    vsnprintf(fstr, strsize, fmt, args);

    return fstr;
}

static char *makefstr(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char *fstr = vmakefstr(fmt, args);
    va_end(args);

    return fstr;
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
    va_list args;
    va_start(args, fmt);

    char *desc = vmakefstr(fmt, args);
    va_end(args);
    
    char *msg = makefstr("[%s] [Dackel2D] [%s%s%s] [%s:%d]: %s", get_timestamp(), color, type, END, file, line, desc);
    fprintf(stream, "%s\n", msg);

    free(desc);
    free(msg);
}

void store_message(const char *type, const char *file, int line, const char *fmt, ...)
{
    FILE* log = fopen("log.txt", "a+");
    if (log == NULL)
    {
        log_error("Failed to open log file! %s", strerror(errno));
        return;
    }

    va_list args;
    va_start(args, fmt);

    char *desc = vmakefstr(fmt, args);
    va_end(args);

    char *msg = makefstr("[%s] [Dackel2D] [%s] [%s:%d]: %s", get_timestamp(), type, file, line, desc);
    fprintf(log, "%s\n", msg);

    if (fclose(log) != 0)
        log_error("Failed to close log file! %s", strerror(errno));

    free(desc);
    free(msg);
}
