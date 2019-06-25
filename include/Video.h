#pragma once

#include "interface/IRentable.h"

class Video : public IRentable {
public:
    Video(std::string title, std::string type);

    const std::string& Title() const override;
    const std::string& Type() const override;
    clock_time RentalStart() const override;
    clock_time RentalEnd() const override;

    void RentalStart(clock_time) override;
    void RentalEnd(clock_time) override;

private:
    std::string title;
    std::string type;
    clock_time rentalStart;
    clock_time rentalEnd;
};