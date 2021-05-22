//
// Created by Rodya on 01.04.2021.
//

#include "task_functions.h"

void insert_vehicle(LinkedList<Vehicle> &list, const Vehicle &vehicle) {
    //Поиск первого элемента нужной модели, год выпуска которого больше года выпуска нового элемента
    auto insert_node = list.find_first(vehicle, [](const Vehicle& lhs, const Vehicle& rhs) {
        return lhs.model == rhs.model && lhs.year < rhs.year;
    });
    //Если найти подходящий элемент не удалось, ищем первый элемент нужного модельного ряда
    if (insert_node == nullptr) insert_node = list.find_first(vehicle, [](const Vehicle& lhs, const Vehicle& rhs) {
            return lhs.model == rhs.model;
    });
    //Вставляем новый элемент перед найденным
    list.insert_before(insert_node, vehicle);
}

models_map get_models(LinkedList<Vehicle> &list) {
    //Создаем словарь, где ключ - целое число, а значение указатель на узел списка
    models_map result;
    //Заполняем словарь, парами ключ-значение, где ключ - номер модели, а значение - указатель на первый узел модельного ряда
    for (auto node = list.get_head(); node != nullptr; node = node->next)
        if (result.find(node->data.model) == result.end())
            result[node->data.model] = node;
    //Возвращаем словарь
    return result;
}

void delete_model(LinkedList<Vehicle> &list, const int &model) {
    //Берем словарь с указательями на начала модельных рядов
    auto models = get_models(list);
    //Если в словаре нет указателя на начало модельного ряда заданной модели, выводим сообщение об ошибке
    if (models.find(model) == models.end()) {
        std::cerr << "No such model.\n";
        return;
    }
    //Удаляем все элементы модельного ряда после первого
    list.remove_after_while(
            models[model],
            [](LinkedList<Vehicle>::Node* node){
                return node->data.model == node->next->data.model;
            }
    );
    //Удаляем первый элемент модельного ряда
    list.remove_after(models[model]->prev);
}

LinkedList<Vehicle> fill_list() {
    LinkedList<Vehicle> result;
    for (int model = 3; model > 0; model--)
        for (int year = 1998; year != 2002; year++)
            result.push_front({model, "GER", year});
    return result;
}

std::ostream &operator<<(std::ostream &stream, const models_map &data) {
    for (auto &[model, node_ptr] : data) {
        stream << "{Model: " << model << ", Node: " << node_ptr->data.to_string() << "}" << "\n";
    }
    return stream;
}