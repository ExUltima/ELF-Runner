#include "process.hpp"
#include "handle.hpp"

#include <exception>
#include <iostream>
#include <system_error>

#include <cstdlib>

#include <windows.h>

process::process(const std::wstring& file)
{
    std::memset(&proc_, 0, sizeof(proc_));

    STARTUPINFOW launch = {0};
    launch.cb = sizeof(launch);

    auto res = CreateProcessW(
            file.c_str(),
            nullptr,
            nullptr,
            nullptr,
            FALSE,
            0,
            nullptr,
            nullptr,
            &launch,
            &proc_);

    if (!res) {
        throw std::system_error(GetLastError(), std::system_category());
    }
}

process::~process()
{
    try {
        if (proc_.hThread)
            handle::close(proc_.hThread);
    } catch (std::exception& e) {
        std::cerr << "failed to close handle: " << e.what() << std::endl;
    }

    try {
        if (proc_.hProcess)
            handle::close(proc_.hProcess);
    } catch (std::exception& e) {
        std::cerr << "failed to close handle: " << e.what() << std::endl;
    }
}
