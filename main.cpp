#include "process.hpp"

#include <exception>
#include <iostream>
#include <string>

#include <cstdlib>

static void run_elf(const std::wstring& file)
{
    process proc(file);
}

int wmain(int argc, wchar_t *argv[])
{
    if (argc != 2) {
        std::wcerr << L"usage: " << argv[0] << L" FILE" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        std::wstring file = argv[1];

        std::wcout << L"running " << file << std::endl;

        run_elf(file);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
