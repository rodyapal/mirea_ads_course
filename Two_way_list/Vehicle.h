//
// Created by Rodya on 01.04.2021.
//
#pragma once
#include <string>
#include <iostream>

struct Vehicle {
    int model;
    std::string country;
    int year;

    bool operator==(const Vehicle& other) const;

    bool operator<(const Vehicle& other) const;

    [[nodiscard]]
    std::string to_string() const;
};

std::ostream& operator<<(std::ostream& stream, const Vehicle& vehicle);
