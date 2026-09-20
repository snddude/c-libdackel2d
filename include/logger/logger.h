#pragma once

#include "logger/colors.h"

#include <stdio.h>

#define log_info(fmt, ...) log_message(stdout, LogLevel_Info, "info", __FILE_NAME__, __LINE__, BFG_MAGENTA, fmt, ##__VA_ARGS__)
#define log_error(fmt, ...) log_message(stdout, LogLevel_Error, "error", __FILE_NAME__, __LINE__, BFG_RED, fmt, ##__VA_ARGS__)
#define log_warning(fmt, ...) log_message(stdout, LogLevel_Warning, "warning", __FILE_NAME__, __LINE__, BFG_YELLOW, fmt, ##__VA_ARGS__)

#define slog_info(fmt, ...) { log_info(fmt, ##__VA_ARGS__); store_message("info", __FILE_NAME__, __LINE__, fmt, ##__VA_ARGS__); }
#define slog_error(fmt, ...) { log_error(fmt, ##__VA_ARGS__); store_message("error", __FILE_NAME__, __LINE__, fmt, ##__VA_ARGS__); }
#define slog_warning(fmt, ...) { log_warning(fmt, ##__VA_ARGS__); store_message("warning", __FILE_NAME__, __LINE__, fmt, ##__VA_ARGS__); }

typedef enum
{
    LOG_LEVEL_NONE = 0,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
    LOG_LEVEL_COUNT, // Number of available log levels.
} log_level_t;

const char *get_timestamp();

void set_log_level(log_level_t value);
void log_message(FILE *stream, log_level_t log_level, const char *type, const char *file, int line, const char *color, const char *fmt, ...);
void store_message(const char *type, const char *file, int line, const char *fmt, ...);
