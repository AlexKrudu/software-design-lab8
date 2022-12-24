#pragma once

#include <chrono>
#include <ctime>

namespace utils {

    class Clock {
    public:
        virtual time_t now() = 0;
    };

}