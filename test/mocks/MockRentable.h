#pragma once

#include "../catch.hpp"
#include "../catch2/trompeloeil.hpp"

#include "interface/IRentable.h"

class MockRentable : public IRentable {
    MAKE_CONST_MOCK0(Title, const std::string&(), override);
    MAKE_CONST_MOCK0(Type, const std::string&(), override);
    MAKE_CONST_MOCK0(RentalStart, clock_time(), override);
    MAKE_CONST_MOCK0(RentalEnd, clock_time(), override);
    MAKE_CONST_MOCK0(CostPerDay, Money(), override);
    MAKE_CONST_MOCK0(PenaltyPerDay, Money(), override);

    MAKE_MOCK1(RentalStart, void(clock_time), override);
    MAKE_MOCK1(RentalEnd, void(clock_time), override);
};