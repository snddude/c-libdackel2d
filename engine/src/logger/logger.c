#include "logger/logger.h"

#include <stdio.h>
#include <time.h>

const char *get_timestamp()
{
    time_t now = time(NULL);
    struct tm *time = localtime(&now);

    static char buffer[24];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time);

    return buffer;
}
