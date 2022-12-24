#pragma once

#include <string>
#include <unordered_map>

namespace event_stats {

    class EventsStatistic {
    public:
        virtual void incEvent(const std::string &name) = 0;

        virtual double getEventStatisticByName(const std::string &name) = 0;

        virtual std::unordered_map<std::string, double> getAllEventStatistic() = 0;

        virtual void printStatistic() = 0;

        virtual ~EventsStatistic() = default;

    };

}