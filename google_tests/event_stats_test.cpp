#include "gtest/gtest.h"
#include "../event_statistics_impl.h"
#include "../mockable_clock.h"


TEST(EventsStatsTest, simple_test) {
    auto clock = std::make_shared<utils::MockableClock>();
    event_stats::EventsStatisticsImpl eventsStatistics{clock};

    clock->setNow(10000);
    eventsStatistics.incEvent("a");
    eventsStatistics.incEvent("b");

    ASSERT_DOUBLE_EQ(eventsStatistics.getEventStatisticByName("a"), 1.0 / 60);
    ASSERT_DOUBLE_EQ(eventsStatistics.getEventStatisticByName("b"), 1.0 / 60);
}

TEST(EventsStatsTest, event_expires) {
    const auto start = 10000;
    auto clock = std::make_shared<utils::MockableClock>();
    event_stats::EventsStatisticsImpl eventsStatistics{clock};

    clock->setNow(start);
    eventsStatistics.incEvent("a");
    clock->setNow(start + 7200);

    ASSERT_DOUBLE_EQ(eventsStatistics.getEventStatisticByName("a"), 0);
}

TEST(EventsStatsTest, n_events_nth_hour) {
    const auto start = 10000;
    auto clock = std::make_shared<utils::MockableClock>();
    event_stats::EventsStatisticsImpl eventsStatistics{clock};

    for (int i = 0; i < 100; i++) {
        clock->setNow(start + 3601 * i);
        for (int j = 0; j < i + 1; j++) {
            eventsStatistics.incEvent("a");
        }
        ASSERT_DOUBLE_EQ(eventsStatistics.getEventStatisticByName("a"), static_cast<double>(i + 1) / 60);
    }
    clock->setNow(100000000);
    ASSERT_DOUBLE_EQ(eventsStatistics.getEventStatisticByName("a"), 0);
    ASSERT_EQ(eventsStatistics.getAllEventStatistic().at("a"), 0);
}