#ifndef FE_LOGGER_H
#define FE_LOGGER_H

#include <ansi/ansi-color-codes.h>

#include <stdio.h>

enum LogLevel {
    LOG_LEVEL_INFO = 0,
    LOG_LEVEL_WARNING = 1,
    LOG_LEVEL_ERROR = 2,
    LOG_LEVEL_FATAL = 3,
    LOG_LEVEL_DEBUG = 4,
};

void fe_log(enum LogLevel level, FILE* out, const char* fmt, ...);

#define FE_INFO(...) fe_log(LOG_LEVEL_INFO, stdout, __VA_ARGS__)

#define FE_WARNING(...) fe_log(LOG_LEVEL_WARNING, stderr, __VA_ARGS__)

/**
* @brief Write an error-formatted message to STDERR. Does not
* terminate the program. If terminating the program following
* a critical error, do so following a call to `err()`.
*/ 
#define FE_ERROR(...) fe_log(LOG_LEVEL_ERROR, stderr, __VA_ARGS__)
//void fe_err(const char* fmt, ...);

#define FE_FATAL(...) fe_log(LOG_LEVEL_FATAL, stderr, __VA_ARGS__)

#ifdef DEBUG
    #define FE_DEBUG(...)  fe_log(LOG_LEVEL_DEBUG, stdout, __VA_ARGS__);\
    printf(" %sCalled in \"%s\" at [L:%d]\n", ANSI_MAG, __FILE__, __LINE__)
#else
    #define FE_DEBUG(...) 
#endif 

#endif 
