#pragma once

#include "logger/colors.h"

#include <stdio.h>

#define log_info(fmt, ...) fprintf(stdout, "%sINFO: "fmt"%s\n", FG_WHITE, __VA_ARGS__, END)
#define log_error(fmt, ...) fprintf(stderr, "%sERROR: "fmt"%s\n", FG_RED, __VA_ARGS__, END)
#define log_warning(fmt, ...) fprintf(stderr, "%sWARNING: "fmt"%s\n", FG_YELLOW, __VA_ARGS__, END)
