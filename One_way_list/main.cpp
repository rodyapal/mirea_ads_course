#include <iostream>
#include <vector>

using namespace std;

template<typename Type>
class LinkedList {
public:
    struct Node {
        Type value;
        Node* next = nullptr;
    };

    ~LinkedList() {
        clear();
    }

    void push_front(const Type& value) {
        auto node = new Node{value};
        node->next = head;
        head = node;
    }

    void push_front(Node* node) {
        if (node->next == nullptr) {
            push_front(node->value);
        } else {
            auto item = node;
            while (item->next != nullptr) item = item->next;
            item->next = head;
            head = node;
        }
    }

    void insert_after(Node* node, const Type& value) {
        if (node) {
            auto new_node = new Node{value};
            new_node->next = node->next;
            node->next = new_node;
        } else {
            push_front(value);
        }
    }

    void remove_after(Node* node) {
        if (!node) {
            pop_front();
        } else if (node->next) {
            auto removing_node = node->next;
            node->next = removing_node->next;
            delete removing_node;
        }
    }

    template<class Predicate>
    void remove_after_while(Node* node, Predicate predicate) {
        while (predicate(node)) remove_after(node);
    }

    void pop_front() {
        if (head) {
            Node* new_head = head->next;
            delete head;
            head = new_head;
        }
    }

    Node* get_previous(Node* node) const {
        auto item = head;
        while (item->next != node) item = item->next;
        return item;
    }

    [[nodiscard]]
    Node* find_last(const Type& value) const {
        Node* last_item = nullptr;
        for (auto item = head; item != nullptr; item = item->next)
            if (item->value == value) last_item = item;
        return last_item;
    }

    [[nodiscard]]
    Node* find_first(const Type& value, Node* start = nullptr) const {
        for (auto item = start != nullptr ? start : head; item != nullptr; item = item->next)
            if (item->value == value) return item;
        return nullptr;
    }

    Node* find_ordinal(const Type& value, const size_t& ordinal) {
        Node* item = nullptr;
        for (int index = 0; index < ordinal; index++) {
            item = find_first(value, item != nullptr ? item->next : item);
        }
        return item;
    }

    [[nodiscard]]
    Node* get_back() const {
        auto item = head;
        while (item->next != nullptr) item = item->next;
        return item;
    }

    [[nodiscard]]
    Node* get_head() const {
        return head;
    }

    void reverse_list() {
        vector<Type> values;
        for (auto item = head; item != nullptr; item = item->next)
            values.push_back(item->value);
        clear();
        for(const auto& item : values) {
            push_front(item);
        }
    }

private:
    void clear() {
        while (head) {
            pop_front();
        }
    }

    Node* head = nullptr;
};

template<class Type>
ostream& operator<<(ostream& stream, const LinkedList<Type>& list) {
    for (auto item = list.get_head(); item != nullptr; item = item->next)
        stream << item->value;
    return stream;
}

LinkedList<char> createWords() {
    LinkedList<char> list;
    for (int word = 0; word < 10; word++) {
        if (word != 0) list.push_front(' ');
        for (int letter = 0; letter < 5; letter++) {
            list.push_front('a' + word);
        }
    }
    return list;
}

LinkedList<char> createAnotherWords() {
    LinkedList<char> list;
    for (int word = 0; word < 3; word++) {
        if (word != 0) list.push_front(' ');
        for (int letter = 0; letter < 4; letter++) {
            list.push_front('2' + letter);
        }
    }
    return list;
}

void last_word_to_front(LinkedList<char>& words) {
    auto last_word_start = words.find_last(' ')->next;
    words.insert_after(words.get_back(), ' ');
    words.get_previous(last_word_start)->next = nullptr;
    words.push_front(last_word_start);
}

void erase_second_word(LinkedList<char>& words) {
    auto second_word_start = words.find_ordinal(' ', 1);
    words.remove_after_while(
            second_word_start,
            [](LinkedList<char>::Node* node) {
                return node->next->value != ' ';
            });
    words.remove_after(second_word_start);
}

void replace_word(
        LinkedList<char>& words,
        LinkedList<char> to_insert,
        const size_t& replace_word_index
) {
    auto word_start = words.find_ordinal(' ', replace_word_index);
    words.remove_after_while(
            word_start,
            [](LinkedList<char>::Node* node) {
                return node->next->value != ' ';
            });
    words.remove_after(word_start);
    to_insert.reverse_list();
    words.insert_after(word_start, ' ');
    for (
            auto insert_letter = to_insert.get_head();
            insert_letter != nullptr;
            insert_letter = insert_letter->next
        )
            words.insert_after(word_start, insert_letter->value);
}

int main() {
    LinkedList<char> words = createWords();
    LinkedList<char> to_insert = createAnotherWords();
    cout << "List:\n" << words << endl;
    cout << "Replace words:\n" << to_insert << endl;
    last_word_to_front(words);
    erase_second_word(words);
    replace_word(words, to_insert, 3);
    cout << "List after replace_word:\n" << words << endl;
    return 0;
}
