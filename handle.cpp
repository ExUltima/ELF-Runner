#include "handle.hpp"

#include <system_error>

#include <windows.h>

void handle::close(HANDLE h)
{
    if (!CloseHandle(h))
        throw std::system_error(GetLastError(), std::system_category());
}
