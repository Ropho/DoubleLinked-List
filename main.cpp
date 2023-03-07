#include "list.hpp"
#include <vector>
#include <algorithm>
#include <list>

int main (void) {
    init_log ();
/////////////////////////////////////////////////КОНСТРУКТОР ДЕФОЛТНЫЙ
    list::List <int> first {};
    list::List <int> second {};

/////////////////////////////////////////////////Добавление в конец элемента
    first.push_back (2);
    first.push_back (1);
    first.push_back (3);
    first.push_back (10);
    first.push_back (1);
    first.push_front (-2);

/////////////////////////////////////////////////Вставка в середину/начало/конец
    list::List<int>::Iterator it = second.begin ();
    second.insert (it, 1);
    it = second.begin ();
    ++it;
    second.insert (it, 2);
    it = second.end ();
    second.insert (it, 3);
/////////////////////////////////////////////////Удаление элемента
    it = second.end ();
    second.erase (it);

/////////////////////////////////////////////////пересечение элементов

    auto third = first ^ second;

/////////////////////////////////////////////////объединение элементов
    auto fourth = first | second;

/////////////////////////////////////////////////Сортировка
    auto fifth = fourth;
    fifth.sort ();
/////////////////////////////////////////////////friend std
    std::cout << "FIRST LIST: "<< first;

    /////////////////////////////////////////////Печать всего списка
    std::cout << "SECOND LIST: ";
    for (list::List<int>::Iterator it = second.begin (); it != second.end (); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
/////////////////////////////////////////////////Range-based for
    std::cout << "THIRD LIST (INTERSECTED LIST): ";
    for (int val : third) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

/////////////////////////////////////////////////
    std::cout << "FOURTH LIST (UNITED): " << fourth;
    std::cout << "FIFTH LIST (SORTED UNITED): " << fifth;

    clear_log ();
}