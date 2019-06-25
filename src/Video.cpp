#include "Video.h"

Video::Video(std::string title, std::string type) : title{std::move(title)}, type{std::move(type)} {
}

const std::string& Video::Title() const {
    return title;
}

const std::string& Video::Type() const {
    return type;
}

auto Video::RentalStart() const -> clock_time {
    return rentalStart;
}

auto Video::RentalEnd() const -> clock_time {
    return rentalEnd;
}

void Video::RentalStart(clock_time start) {
    rentalStart = start;
}

void Video::RentalEnd(clock_time end) {
    rentalEnd = end;
}
