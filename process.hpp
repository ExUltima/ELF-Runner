#ifndef PROCESS_HPP_INCLUDED
#define PROCESS_HPP_INCLUDED

#include <string>

#include <processthreadsapi.h>

class process final {
public:
    process(const std::wstring& file);
    process(const process&) = delete;
    ~process();

    process& operator=(const process&) = delete;
private:
    PROCESS_INFORMATION proc_;
};

#endif
