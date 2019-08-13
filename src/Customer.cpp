#include "Customer.h"

Customer::Customer(std::string name, std::string address) :
        name{std::move(name)}, address{std::move(address)} {
}

const std::string& Customer::Name() const {
    return name;
}

const std::string& Customer::Address() const {
    return address;
}

Money Customer::Balance() const {
    return balance;
}

const std::vector<std::unique_ptr<IRentable>>& Customer::Rentals() const {
    return rented;
}

void Customer::AssignRental(std::unique_ptr<IRentable> item) {
    rented.emplace_back(std::move(item));
}

std::unique_ptr<IRentable> Customer::RemoveRental(size_t i) {
    auto iter = rented.begin() + i;
    std::unique_ptr<IRentable> ret = std::move(*iter);
    rented.erase(iter);
    return ret;
}

void Customer::AdjustBalance(Money amount) {
    balance += amount;
}