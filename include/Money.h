#pragma once

struct Money {
    long pounds;
    char pence;

    bool operator==(const Money& other) const noexcept {
        return pounds == other.pounds && pence == other.pence;
    }

    Money& operator+=(const Money& other) noexcept {
        pounds += other.pounds;
        pence += other.pence;
        return *this;
    }
};
