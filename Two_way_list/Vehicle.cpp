//
// Created by Rodya on 01.04.2021.
//

#include "Vehicle.h"

bool Vehicle::operator==(const Vehicle &other) const {
    return model == other.model;
}

std::string Vehicle::to_string() const {
    return "{Model: " + std::to_string(model) + ", Country: " + country + ", Year: " + std::to_string(year) + "}";
}

bool Vehicle::operator<(const Vehicle &other) const {
    return year < other.year;
}

std::ostream &operator<<(std::ostream &stream, const Vehicle &vehicle) {
    stream << vehicle.to_string();
    return stream;
}