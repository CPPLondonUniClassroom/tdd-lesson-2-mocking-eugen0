#pragma once

#include "../catch.hpp"
#include "../catch2/trompeloeil.hpp"

#include "interface/ICustomer.h"

class MockCustomer : public ICustomer {
public:
    MAKE_CONST_MOCK0(Name, const std::string&(), override);
    MAKE_CONST_MOCK0(Address, const std::string&(), override);
    MAKE_CONST_MOCK0(Balance, Money(), override);
    MAKE_CONST_MOCK0(Rentals, const std::vector<std::unique_ptr<IRentable>>&(), override);

    MAKE_MOCK1(AdjustBalance, void(Money), override);
    MAKE_MOCK1(AssignRental, void(std::unique_ptr<IRentable>), override);
    MAKE_MOCK1(RemoveRental, std::unique_ptr<IRentable>(size_t), override);
};