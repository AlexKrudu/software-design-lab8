#pragma once

#include "clock.h"

#include <string>

namespace utils {

    class MockableClock : public Clock {
    public:
        void setNow(time_t now) {
            mocked_now = now;
        }

        time_t now() override {
            return mocked_now;
        }

    private:
        time_t mocked_now = 0;
    };

}