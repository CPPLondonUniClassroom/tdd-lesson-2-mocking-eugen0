#pragma once

#include "Money.h"

#include <chrono>
#include <string>

class IRentable {
public:
    using clock_time = std::chrono::system_clock::time_point;
    virtual const std::string& Title() const = 0;
    virtual const std::string& Type() const = 0;
    virtual clock_time RentalStart() const = 0;
    virtual clock_time RentalEnd() const = 0;
    virtual Money CostPerDay() const = 0;
    virtual Money PenaltyPerDay() const = 0;

    virtual void RentalStart(clock_time) = 0;
    virtual void RentalEnd(clock_time) = 0;

    virtual ~IRentable() = default;
};
