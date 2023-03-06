#ifndef LOG_HPP
#define LOG_HPP


#include <iostream>

#define __PF __PRETTY_FUNCTION__

#define LOG(func_name, msg) do {                                                   \
                    fprintf (stderr, "\x1b[33m[INFO] \x1b[92m%s \x1b[33m%s\x1b[0m\n", func_name, msg);       \
                } while (0)

#define ERROR(func_name, msg) do {                                                                         \
                        int error = errno;                                                      \
                        fprintf (stderr, "\x1b[31m[FATAL] \x1b[92m%s \x1b[31m%s: %s\x1b[0m\n", func_name, message, strerror (error));     \
                        exit (1);                                                               \
                    } while (0)

#endif