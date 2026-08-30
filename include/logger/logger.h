#pragma once

#include "logger/colors.h"

#include <stdio.h>

#define log_info(fmt, ...) log_message(stdout, "info", __FILE_NAME__, __LINE__, BFG_MAGENTA, fmt, ##__VA_ARGS__)
#define log_error(fmt, ...) log_message(stdout, "error", __FILE_NAME__, __LINE__, BFG_RED, fmt, ##__VA_ARGS__)
#define log_warning(fmt, ...) log_message(stdout, "warning", __FILE_NAME__, __LINE__, BFG_YELLOW, fmt, ##__VA_ARGS__)

#define slog_info(fmt, ...) { log_info(fmt, ##__VA_ARGS__); store_message("info", __FILE_NAME__, __LINE__, fmt, ##__VA_ARGS__); }
#define slog_error(fmt, ...) { log_error(fmt, ##__VA_ARGS__); store_message("error", __FILE_NAME__, __LINE__, fmt, ##__VA_ARGS__); }
#define slog_warning(fmt, ...) { log_warning(fmt, ##__VA_ARGS__); store_message("warning", __FILE_NAME__, __LINE__, fmt, ##__VA_ARGS__); }

const char *get_timestamp();

void log_message(FILE *stream, const char *type, const char *file, int line, const char *color, const char *fmt, ...);
void store_message(const char *type, const char *file, int line, const char *fmt, ...);
