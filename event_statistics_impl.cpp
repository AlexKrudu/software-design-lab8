#include "event_statistics_impl.h"

#include <iostream>


namespace event_stats {

    namespace {
        constexpr time_t SECONDS_IN_HOUR = 3600;
        constexpr time_t MINUTES_IN_HOUR = 60;
    }

    EventsStatisticsImpl::EventsStatisticsImpl(const std::shared_ptr<utils::Clock>& clock) : clock_(clock) {}

    void EventsStatisticsImpl::incEvent(const std::string &name) {
        if (!events_.contains(name)) {
            events_.insert({name, std::list<time_t>{}});
        }
        trimExpiredEvents(name);
        events_[name].push_back(clock_->now());
    }

    double EventsStatisticsImpl::getEventStatisticByName(const std::string &name) {
        if (!events_.contains(name)) {
            return 0;
        }
        trimExpiredEvents(name);
        return static_cast<double>(events_[name].size()) / MINUTES_IN_HOUR;

    }

    std::unordered_map<std::string, double> EventsStatisticsImpl::getAllEventStatistic() {
        std::unordered_map<std::string, double> res;
        for (auto&[event_name, points]: events_) {
            trimExpiredEvents(event_name);
            res[event_name] = static_cast<double>(points.size()) / MINUTES_IN_HOUR;
        }
        return res;
    }

    void EventsStatisticsImpl::printStatistic() {
        const auto statistics = getAllEventStatistic();
        for (auto&[event_name, rpm]: statistics) {
            std::cout << "Event: " << event_name << ", rpm: " << rpm << std::endl;
        }
    }

    void EventsStatisticsImpl::trimExpiredEvents(const std::string &name) {
        if (!events_.contains(name)) return;
        while (!events_[name].empty() && *events_[name].begin() < clock_->now() - SECONDS_IN_HOUR) {
            events_[name].pop_front();
        }
    }

    EventsStatisticsImpl::~EventsStatisticsImpl() = default;
}