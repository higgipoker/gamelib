#include "log.h"
#include <iostream>
#include <sstream>
#include <stdarg.h>
#include <stdio.h>

namespace GameLib {

/**
 * @brief Log
 * @param args
 */
void Log(std::string args, ...) {
    std::ostringstream log;
    va_list vl;

    va_start(vl, args);

    // Step through the list.
    for (size_t i = 0; args[i] != '\0'; ++i) {

        switch (args[i]) { // Type to expect.
            case 'i': {
                int i = va_arg(vl, int);
                log << i;
            } break;

            case 'f': {
                double f = va_arg(vl, double);
                log << f;
            } break;

            case 'c': {
                char c = static_cast<char>(va_arg(vl, int));
                log << c;
            } break;

            case 's': {
                char *s = va_arg(vl, char *);
                log << s;
            } break;

            default:
                break;
        }
    }
    va_end(vl);
    std::cout << std::endl;
    std::cout << "============================" << std::endl;
    std::cout << log.str() << std::endl;
    std::cout << "============================" << std::endl;
    std::cout << std::endl;
}

} // namespace GameLib
