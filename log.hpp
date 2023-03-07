#ifndef LOG_HPP
#define LOG_HPP


#include <iostream>
#include <fstream>

FILE *out;

#define __PF __PRETTY_FUNCTION__

#define LOG(func_name, msg) do {                                                    \
                    fprintf (out, "[INFO] %s %s\n", func_name, msg);                \
                } while (0)

#define ERROR(func_name, msg) do {                                                                              \
                        fprintf (stderr, "\x1b[31m[FATAL] \x1b[92m%s \x1b[31m%s\x1b[0m\n", func_name, msg);     \
                    } while (0)

void init_log () {
    out = fopen ("log.txt", "w");    
    if (out == nullptr) {
        ERROR (__PF, "Couldn't open file log\n");
        out = stderr;
    }
}

void clear_log () {
    if (fclose (out)) {
        ERROR (__PF, "Couldn't close the log file\n");
    }
}
#endif