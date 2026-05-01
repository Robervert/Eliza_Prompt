#pragma once
#include <iostream>
#include <windows.h>

static void GREETINGS()
{
    std::cout << "  Welcome to\n";
    std::cout << "          EEEEEE  LL      IIII  ZZZZZZZ   AAAAA\n";
    std::cout << "          EE      LL       II       ZZ   AA   AA\n";
    std::cout << "          EEEEEE  LL       II     ZZZ    AAAAAAA\n";
    std::cout << "          EE      LL       II    ZZ      AA   AA\n";
    std::cout << "          EEEEEE  LLLLLL  IIII  ZZZZZZZ  AA   AA\n\n";
    Sleep(100);
    std::cout << "  >>Eliza is a mock Rogerian psychotherapist.\n";
    std::cout << "  >>The original program was described by [Joseph Weizenbaum] in 1966.\n";
    std::cout << "  >>This implementation by [Chao Moyam] in 2026, 60 years after its first edition.\n\n\n" << std::endl;
}