#pragma once

#include "interface/IRentable.h"

#include <memory>
#include <string>
#include <vector>

class ICustomer {
public:
    virtual const std::string& Name() const = 0;
    virtual const std::string& Address() const = 0;
    virtual Money Balance() const = 0;
    virtual const std::vector<std::unique_ptr<IRentable>>& Rentals() const = 0;

    virtual void AdjustBalance(Money) = 0;
    virtual void AssignRental(std::unique_ptr<IRentable>) = 0;
    virtual std::unique_ptr<IRentable> RemoveRental(size_t) = 0;

    virtual ~ICustomer() = default;
};