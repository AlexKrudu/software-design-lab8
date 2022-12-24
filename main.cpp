#include <iostream>
#include "event_statistics_impl.h"
#include "real_clock.h"

int main() {
    auto clock = std::make_shared<utils::RealClock>();
    event_stats::EventsStatisticsImpl eventsStatistics{clock};

    eventsStatistics.incEvent("a");
    eventsStatistics.incEvent("b");

    eventsStatistics.printStatistic();

    return 0;
}
