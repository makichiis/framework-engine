#include "fe/err.h"
#include <fe/logger.h> 
#include <ansi/ansi-color-codes.h>

#include <stdarg.h> 
#include <stdlib.h> 
#include <string.h>
#include <stdio.h> 
#include <time.h>

#define LOGGING_PREFIX_INFO "[INFO]: "
#define LOGGING_PREFIX_WARNING "[WARNING]: "
#define LOGGING_PREFIX_ERROR "[ERROR]: "
#define LOGGING_PREFIX_FATAL "[FATAL]: "
#define LOGGING_PREFIX_DEBUG "[DEBUG]: "

void fe_log(enum LogLevel level, FILE* out, const char* fmt, ...) {
    printf(ANSI_COLOR_RESET);
    const char* logging_prefix = LOGGING_PREFIX_INFO;
    switch (level) {
        case LOG_LEVEL_WARNING:
            logging_prefix = LOGGING_PREFIX_WARNING;
            fprintf(out, ANSI_YEL);
            break;
        case LOG_LEVEL_ERROR:
            logging_prefix = LOGGING_PREFIX_ERROR;
            fprintf(out, ANSI_RED);
            break;
        case LOG_LEVEL_FATAL:
            logging_prefix = LOGGING_PREFIX_FATAL;
            fprintf(out, ANSI_BRED);
            break;
        case LOG_LEVEL_DEBUG:
            logging_prefix = LOGGING_PREFIX_DEBUG;
            fprintf(out, ANSI_BLU);
            break;
        default:
            break;
    }

    char localtime_buf[32];
    time_t now = time(NULL);
    size_t res = strftime(localtime_buf, sizeof localtime_buf, 
                          "%Y-%m-%d %H:%M:%S ", localtime(&now));

    if (res == 0) {
        // how do i log this lol 
        fprintf(stderr, "Logger failed to write.\n");
        exit(FE_ERR_LOGGER_FAIL);
    }

    size_t localtime_strlen = res;
    size_t logprefix_strlen = strlen(logging_prefix);

    char* log_fmt = malloc(strlen(fmt) 
                           + logprefix_strlen 
                           + localtime_strlen 
                           + 1);

    strcpy(log_fmt, localtime_buf);
    strcpy(log_fmt + localtime_strlen, logging_prefix);
    strcpy(log_fmt + localtime_strlen + logprefix_strlen, fmt);

    va_list args;
    va_start(args, fmt);

    vfprintf(out, log_fmt, args);
    va_end(args);

    fprintf(out, ANSI_COLOR_RESET);
    fprintf(out, "\n");
    free(log_fmt);
}

