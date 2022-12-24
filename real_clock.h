#pragma once

#include "clock.h"

namespace utils{

    class RealClock : public Clock{
        time_t now() override{
            return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        }
    };
}