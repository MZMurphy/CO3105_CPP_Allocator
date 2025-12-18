#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#define DEBUG 0

#if DEBUG
    #define DEBUG_PRINT(x) std::cout << x
#else
    #define DEBUG_PRINT(x)

#endif //DEBUG
#endif //DEBUG_H
