#pragma once

#include "event_statistics.h"

#include <memory>
#include <list>
#include "clock.h"

namespace event_stats {

    class EventsStatisticsImpl : public EventsStatistic {
    public:

        explicit EventsStatisticsImpl(const std::shared_ptr<utils::Clock> &clock);

        void incEvent(const std::string &name) override;

        double getEventStatisticByName(const std::string &name) override;

        std::unordered_map<std::string, double> getAllEventStatistic() override;

        void printStatistic() override;


        ~EventsStatisticsImpl();

    private:

        void trimExpiredEvents(const std::string &name);

        std::shared_ptr<utils::Clock> clock_;
        std::unordered_map<std::string, std::list<time_t>> events_;
    };
}