#include <iostream>
#include <string>
#include <algorithm>

#include "Vehicle.h"
#include "LinkedList.h"
#include "task_functions.h"

using namespace std;


int main() {
    LinkedList<Vehicle> list = fill_list();
    cout << "Enter \"help\" for list of commands." << endl;
    while (true) {
        string command; cin >> command;
        if (command == "terminate") return 0;
        else if (command == "help") {
            auto help = "print - prints current list.\n"
                        "rprint - prints current list in reverse oder.\n"
                        "terminate - close program.\n"
                        "insert - insert a new value to the list. Template: insert [model] [country] [year]\n"
                        "models - prints first nodes of model rows. \n"
                        "delete - deletes the model row. Template delete [model]";
            cout << help << endl;
        }
        else if (command == "print") {
            cout << "Current list:\n" << list << endl;
        }
        else if (command == "rprint") {
            list.reverse_list();
            cout << "Reverse list:\n" << list << endl;
            list.reverse_list();
        }
        else if (command == "insert") {
            int model, year;
            string country;
            cin >> model >> country >> year;
            insert_vehicle(list, {model, country, year});
            cout << "Done\n";
        }
        else if (command == "models") {
            auto models = get_models(list);
            cout << models << endl;
        }
        else if (command == "delete") {
            int model;
            cin >> model;
            delete_model(list, model);
        }
        else {
            cerr << "Unknown command" << endl;
        }
    }
}