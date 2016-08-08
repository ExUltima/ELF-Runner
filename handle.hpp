#ifndef HANDLE_HPP_INCLUDED
#define HANDLE_HPP_INCLUDED

#include <windows.h>

class handle {
public:
    static void close(HANDLE h);
};

#endif
