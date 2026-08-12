#pragma once

#include "logger/colors.h"

#include <stdio.h>

#define log_info(fmt, ...) fprintf(stdout, "[%s] [Dackel2D] [%sinfo%s] [%s:%d]: "fmt"\n", get_timestamp(), BFG_MAGENTA, END, __FILE_NAME__, __LINE__, ##__VA_ARGS__)
#define log_error(fmt, ...) fprintf(stderr, "[%s] [Dackel2D] [%serror%s] [%s:%d]: "fmt"\n", get_timestamp(), BFG_RED, END, __FILE_NAME__, __LINE__, ##__VA_ARGS__)
#define log_warning(fmt, ...) fprintf(stderr, "[%s] [Dackel2D] [%swarning%s] [%s:%d]: "fmt"\n", get_timestamp(), BFG_YELLOW, END , __FILE_NAME__, __LINE__, ##__VA_ARGS__)

const char *get_timestamp();
