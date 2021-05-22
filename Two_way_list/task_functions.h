//
// Created by Rodya on 01.04.2021.
//
#pragma once

#include "Vehicle.h"
#include "LinkedList.h"
#include <map>

using models_map = std::map<int, LinkedList<Vehicle>::Node*>;

void insert_vehicle(LinkedList<Vehicle>& list, const Vehicle& vehicle);

models_map get_models(LinkedList<Vehicle>& list);

void delete_model(LinkedList<Vehicle>& list, const int& model);

LinkedList<Vehicle> fill_list();

std::ostream& operator<<(std::ostream& stream, const models_map& data);
