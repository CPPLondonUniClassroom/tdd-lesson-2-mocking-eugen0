#pragma once
#include <cstdint>

struct Money {
private:
    long pounds = 0;
    int16_t pence = 0;

    void NormalizeValue() {
        if (pence > 100) {
            pounds += pence / 100;
            pence = pence % 100;
        } else if (pounds > 0 && pence < 0) {
            pounds -= pence / 100;
            pence = pence % 100;
            if (pence < 0)
                pounds -= 1;
            pence += 100;
        }
    }
public:

    Money() = default;

    Money(long pounds, int8_t pence) : pounds{pounds}, pence{pence} {
        NormalizeValue();
    }

    long Pounds() const noexcept {
        return pounds;
    }

    int16_t Pence() const noexcept {
        return pence;
    }

    bool operator==(const Money &other) const noexcept {
        return pounds == other.pounds && pence == other.pence;
    }

    Money& operator+=(const Money &other) noexcept {
        pounds += other.pounds;
        pence += other.pence;
        NormalizeValue();
        return *this;
    }
};
