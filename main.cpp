#include "list.hpp"
#include <vector>
#include <algorithm>
#include <list>
int main (void) {

    // std::list <int> check {};
    // check.push_back (1);
    // check.push_back (2);

    // auto it = check.cend ();
    // --it;
    // *it = 1;
    // std::cerr <<*it;
    // std::terminate ();

    // Node <int> node (1);
    // std::cout << node;
    // int a = 5;
    list::List <int> first {};
    list::List <int> second {};

    // // // first = list::List <int> {};
    first.push_back (2);
    first.push_back (1);
    first.push_back (3);
    first.push_back (10);
    first.push_back (1);
    first.push_back (-2);


    second.push_back (4);
    second.push_back (1);
    second.push_back (2);
    second.push_back (1);
    
    // list::sort <list::List<int>::Iterator> (first.begin (), first.end ());
    // first.sort ();
    // auto it = first.begin ();
    // first.erase (it);
    // it = first.begin ();
    // ++it;
    // ++it;

    // first.erase (it);


    // *it = 10;
    // ++it;
    // ++it;
    // first.insert (it, 10);

    // first.insert (++ (++ (++first.begin ())), 11);
    
    // first.push_back (3);
    // first.push_back (4);
    // first.push_back (5);
    // first.push_back (6);
    
    // second.push_front (10);
    // second.push_front (20);
    // second.push_front (30);
    // second.push_front (40);


    // first.pop_back ();
    // first.pop_back ();
    // first.pop_back ();
    // first.pop_back ();
    // first.pop_back ();

    // first.push_back (2);
    // first.push_back (3);
    // first.pop_front ();
    auto third = first ^ second;

    // first.clear ();
/////////////////////////////////////////////////ULTIMATE TEST
    // list::List <list::List> mem {};

/////////////////////////////////////////////////
    // std::string aa = "123";
    // list::List <std::string> second {};
    // second.push_back (aa);
    // second.push_back (aa);
    // second.push_back (aa);


    // std::cout << first << '\n';

    for (list::List<int>::Iterator it = third.begin (); it != third.end (); ++it) {
        std::cout << *it << " ";
    }

    // for (int val : first) {
    //     std::cout << val << " ";
    // }

    // std::sort (first.begin (), first.end ());
    // std::cout << third << '\n';

}