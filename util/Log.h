/**
 * @file Log.h
 * @Brief  Logging utilities functions
 * @author wu yangtao , w_y_tao@163.com
 * @version version 1.0
 * @date 2016-03-22
 */
#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>

/**
 *define LOG_OUTPUT
 *output of the log
 */ 
#define LOG_OUTPUT stderr

/**
 * @brief Log to the output defined in LOG_OUTPUT.
 * @param level log level.
 * @param ... va_args like in printf.
 * @see printf
 */
#define LOG(level, ...) \
{ \
    fprintf(LOG_OUTPUT, level); \
    fprintf(LOG_OUTPUT, "<%s in %s:%d> ", __FUNCTION__, __FILE__, __LINE__); \
    fprintf(LOG_OUTPUT, __VA_ARGS__); \
    fprintf(LOG_OUTPUT, "\n"); \
    fflush(LOG_OUTPUT); \
}

/**
 * @brief Logs a debug, error, warning, info level message at the log output.
 * @param ... va_args like in printf.
 * @see printf
 */ 
#define DEBUG(...)   LOG("DEBUG   ", __VA_ARGS__)
#define ERROR(...)   LOG("ERROR   ", __VA_ARGS__)
#define WARNING(...) LOG("WARNING ", __VA_ARGS__)
#define INFO(...)    LOG("INFO    ", __VA_ARGS__)

/**
 * redirecting stderr to a file
 */ 
#define LOG_FILE_OPEN(path) {\
    if(freopen(path, "a+", stderr) == NULL)\
    {\
	fprintf(stderr, "redirecting stderr error\n");\
	return 0;\
    }\
}

#define LOG_FILE_CLOSE() {fclose(stderr);}

#endif
