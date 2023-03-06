#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include "log.hpp"
#include <stack>
#include <tuple>


namespace list {

    template <typename T>
    class List;

    template <typename T>
    class Node;

    template <typename List>
    class List_Iterator;

    template <typename List>
    class Const_List_Iterator;

    template <typename T>
    std::ostream& operator << (std::ostream &out, const Node <T>& node);

    template <typename T>
    std::ostream& operator << (std::ostream &out, const List <T>& list);

    template <typename T>
    List <T> operator | (const List <T>& first, const List <T>& second);

    template <typename T>
    List <T> operator ^ (const List <T>& first, const List <T>& second);

    template <typename T>
    class Node {

            ~Node () {
                LOG (__PF, "");
            }

            Node (const T& data) :
                data_ (data) 
            {
                LOG (__PF, "PARAM COPY CTOR");
            }

            Node (T && data) :
                data_ (data) 
            {
                LOG (__PF, "PARAM MOVE CTOR");
            }        

            Node &operator =  (const Node &second)  = delete;
            Node &operator =  (Node &&second)       = delete;

        private:
            Node *prev_ = nullptr;
            Node *next_ = nullptr;
            T data_ {};

            friend class List <T>;
            friend class List_Iterator <List <T>>;
            friend class Const_List_Iterator <List <T>>;

            friend std::ostream& operator << <T> (std::ostream &out, const Node <T>& node);
            friend std::ostream& operator << <T> (std::ostream &out, const List <T>& list);
            friend List <T> operator | <T> (const List <T>& first, const List <T>& second);
            friend List <T> operator ^ <T> (const List <T>& first, const List <T>& second);
    };


    template <typename List_Type>
    class List_Iterator {
        public:
            using Value_Type                = typename List_Type::Value_Type;
            using Pointer_Type              = Value_Type *;
            using Const_Pointer_Type        = const Value_Type *;
            using Reference_Type            = Value_Type &;
            using Const_Reference_Type      = const Value_Type &;

            List_Iterator (Node <Value_Type> * ptr, bool is_end) :
                ptr_ (ptr),
                is_end_ (is_end)
                {
                    LOG (__PF, "");
                }

            List_Iterator& operator ++ () {
                if (ptr_->next_ == nullptr)
                    is_end_ = true;
                else
                    ptr_ = ptr_->next_;
                return *this;
            }

            List_Iterator operator ++ (int) {

                List_Iterator iterator = *this;
                ++(*this);
                return iterator;
            }

            List_Iterator& operator -- () {
                if (is_end_) {
                    is_end_ = false;
                }
                else {
                    ptr_= ptr_->prev_;
                }
                return *this;
            }

            List_Iterator operator -- (int) {
                
                List_Iterator iterator = *this;
                --(*this);
                return iterator;
            }

            Reference_Type operator * () {
                return ptr_ -> data_;
            }

            bool operator == (const List_Iterator & other) {
                return (ptr_ == other.ptr_ && is_end_ == other.is_end_);
            }
            bool operator != (const List_Iterator & other) {
                return (ptr_ != other.ptr_ || is_end_ != other.is_end_);
            }
            bool operator < (const List_Iterator & other) {
                return ptr_->data_ < other.ptr_->data_;
            }

        private:
            Node <Value_Type> *ptr_ = nullptr; 
            bool is_end_ = false;

        friend class List <Value_Type>;
    };


    template <typename List_Type>
    class Const_List_Iterator {
        public:
            using Value_Type                = typename List_Type::Value_Type;
            using Pointer_Type              = Value_Type *;
            using Const_Pointer_Type        = const Value_Type *;
            using Reference_Type            = Value_Type &;
            using Const_Reference_Type      = const Value_Type &;

            Const_List_Iterator (Node <Value_Type> * ptr, bool is_end) :
                ptr_ (ptr),
                is_end_ (is_end)
                {
                    LOG (__PF, "");
                }

            Const_List_Iterator& operator ++ () {
                if (ptr_->next_ == nullptr)
                    is_end_ = true;
                else
                    ptr_ = ptr_->next_;
                return *this;
            }

            Const_List_Iterator operator ++ (int) {

                Const_List_Iterator iterator = *this;
                ++(*this);
                return iterator;
            }

            Const_List_Iterator& operator -- () {
                if (is_end_) {
                    is_end_ = false;
                }
                else {
                    ptr_= ptr_->prev_;
                }
                return *this;
            }

            Const_List_Iterator operator -- (int) {
                
                Const_List_Iterator iterator = *this;
                --(*this);
                return iterator;
            }

            Const_Reference_Type operator * () {
                return ptr_ -> data_;
            }            

            bool operator == (const Const_List_Iterator & other) {
                return (ptr_ == other.ptr_ && is_end_ == other.is_end_);
            }
            bool operator != (const Const_List_Iterator & other) {
                return (ptr_ != other.ptr_ || is_end_ != other.is_end_);
            }

            bool operator < (const Const_List_Iterator & other) {
                return ptr_->data_ < other.ptr_->data_;
            }

            bool operator > (const Const_List_Iterator & other) {
                return ptr_->data_ > other.ptr_->data_;
            }

        private:
            Node <Value_Type> *ptr_ = nullptr; 
            bool is_end_ = false;

        friend class List <Value_Type>;
    };

    template <typename T>
    class List {

        public:

            using Value_Type     = T;
            using Iterator       = List_Iterator <List<T>>;
            using Const_Iterator = Const_List_Iterator <List<T>>;

            Iterator begin () {
                return Iterator (head_, head_ == nullptr);
            }
            Iterator end () {
                return Iterator (tail_, true);
            }

            Const_Iterator cbegin () {
                return Const_Iterator (head_, false);
            }

            Const_Iterator cend () {
                return Const_Iterator (tail_, true);
            }

            List () {
                LOG(__PF, "");                
            }

            List (const List& list) {
                LOG (__PF, "COPY CTOR");
            
                auto tmp = list.head_;
                while (tmp != nullptr) {
                    push_back (tmp->data_);
                    tmp = tmp -> next_;
                }
            }

            List (List&& list) {
                LOG (__PF, "MOVE CTOR");

                head_ = list.head_;
                tail_ = list.tail_;
                size_ = list.size_;

                list.size_ = 0;
                list.head_ = nullptr;
                list.tail_ = nullptr;
            }

            ~List () {
                LOG (__PF, "");

                auto tmp = head_;
                while (head_ != nullptr) {
                    tmp = head_->next_;
                    delete head_;
                    head_ = tmp;
                }
            }

/////////////////////////////////////////////////MODIFIERS
        Iterator erase (Iterator pos) {
            LOG (__PF, "");
            
            if (size_ == 0)
                return pos;

            --size_;
            if (pos.ptr_ -> next_ == nullptr) {

                if (size_ + 1 == 1) {
                    head_ = nullptr;
                    tail_ = nullptr;
                    delete pos.ptr_;

                    return end ();
                }

                pos.ptr_->prev_->next_ = nullptr;
                tail_ = pos.ptr_->prev_;
                delete pos.ptr_;

                return end ();
            }

            if (pos != begin ()) {
                auto it = pos;
                --it;
                it.ptr_->next_ = pos.ptr_ ->next_;
                pos.ptr_->next_ -> prev_ = it.ptr_;
                it = pos;
                ++it;
                delete pos.ptr_;

                return it;
            }
            
            pos.ptr_->next_->prev_ = nullptr;
            head_ = pos.ptr_->next_;
            delete pos.ptr_;

            return begin();
        }        

        Iterator insert (Iterator pos, const T& val) {
            ++size_;           

            Node <Value_Type> *node = new Node <Value_Type> (val);
            
            if (pos == end ()) {
                tail_ = node;
                node->next_ = nullptr;
                node->prev_ = pos.ptr_;
                pos.ptr_->next_ = node;
                
                return Iterator (node, true);
            }

            Iterator it = pos;
            --it;

            node->next_ = pos.ptr_;
            pos.ptr_->prev_ = node;

            if (pos != begin ()) {
                it.ptr_->next_ = node;
                node -> prev_ = it.ptr_;
            }
            else {
                head_ = node;
            }

            return Iterator (node, false);
        }

        Iterator insert (Iterator pos, T&& val) {
            ++size_;           

            Node <Value_Type> *node = new Node <Value_Type> (std::move (val));
            
            if (pos == end ()) {
                tail_ = node;
                node->next_ = nullptr;
                node->prev_ = pos.ptr_;
                pos.ptr_->next_ = node;

                return Iterator (node, true);
            }

            Iterator it = pos;
            --it;

            node->next_ = pos.ptr_;
            pos.ptr_->prev_ = node;

            if (pos != begin ()) {
                it.ptr_->next_ = node;
                node -> prev_ = it.ptr_;
            }
            else {
                head_ = node;
            }

            return Iterator (node, false);                
        }

        void push_back (const Value_Type& val) { 
            ++size_;           

            if (tail_ == nullptr) {
                tail_ = new Node <Value_Type> (val);
                head_ = tail_;
            }
            else {
                Node <Value_Type> *tmp = new Node <Value_Type> (val);
                tail_->next_ = tmp;
                tmp->prev_ = tail_;
                tail_ = tmp;
            }
        }
        

        void push_back (Value_Type&& val) {
            ++size_;

            if (tail_ == nullptr) {
                tail_ = new Node <Value_Type> (std::move (val));
                head_ = tail_;
            }
            else {
                Node <Value_Type> *tmp = new Node <Value_Type> (std::move (val));
                tail_->next_ = tmp;
                tmp->prev_ = tail_;
                tail_ = tmp;
            }
        }

        void push_front (const Value_Type& val) {
            ++size_;

            if (head_ == nullptr) {
                head_ = new Node <Value_Type> (val);
                tail_ = head_;
            }
            else {
                Node <Value_Type> *tmp = new Node <Value_Type> (val);
                head_->prev_ = tmp;
                tmp->next_ = head_;
                head_ = tmp;
            }
        }
        

        void push_front (Value_Type&& val) {
            ++size_;

            if (head_ == nullptr) {
                head_ = new Node <Value_Type> (std::move (val));
                tail_ = head_;
            }
            else {
                Node <Value_Type> *tmp = new Node <Value_Type> (std::move (val));
                head_->prev_ = tmp;
                tmp->next_ = head_;
                head_ = tmp;
            }
        }


        void pop_back () {
            if (tail_ == nullptr)
                return;
            
            --size_;

            auto tmp = tail_->prev_;
            if (tmp != nullptr) {
                tmp->next_ = nullptr;
            }
            else {
                head_ = tmp;
            }

            delete tail_;
            tail_ = tmp;
        }

        void pop_front () {

            if (head_ == nullptr)
                return;
            
            --size_;

            auto tmp = head_->next_;
            if (tmp != nullptr) {
                tmp->prev_ = nullptr;
            }
            else {
                tail_ = tmp;
            }

            delete head_;
            
            head_ = tmp;
        }

// SIMPLE BUBBLE SORT
        void sort () {
            auto cur = tail_;

            while (cur != head_) {
                auto tmp = head_;

                while (tmp != cur) {
                    if (tmp->data_ > tmp->next_->data_)
                        std::swap (tmp->data_, tmp->next_->data_);
                    tmp = tmp -> next_;
                }

                cur = cur -> prev_;
            }

        }
/////////////////////////////////////////////////
        void clear () {
            while (head_ != nullptr) {
                pop_back ();
            }
        }
/////////////////////////////////////////////////CAPACITY
        size_t size () const {
            return size_;
        }
        bool empty () const {
            return !size_;
        }
/////////////////////////////////////////////////OPERATORS

        List <Value_Type>& operator = (const List <Value_Type>& list) {
            LOG (__PF, "COPY =");

            clear ();

            auto tmp = list.head_;
            while (tmp != nullptr) {
                push_back (tmp->data_);
                tmp = tmp -> next_;
            }
            return *this;
        }

        List <Value_Type>& operator = (List <Value_Type>&& list) {
            LOG (__PF, "MOVE =");
            clear ();

            head_ = list.head_;
            tail_ = list.tail_;
            size_ = list.size_;

            list.size_ = 0;
            list.head_ = nullptr;
            list.tail_ = nullptr;
            
            return *this;
        }

        private:
            size_t size_ = 0;
            Node <Value_Type> *head_ {};
            Node <Value_Type> *tail_ {};

        friend std::ostream& operator << <Value_Type> (std::ostream &out, const List <Value_Type> &list);
        friend List <Value_Type> operator | <Value_Type> (const List <Value_Type>& first, const List <Value_Type>& second);
        friend List <Value_Type> operator ^ <Value_Type> (const List <Value_Type>& first, const List <Value_Type>& second);
    };


// merge 2 lists
        template <typename T>
        List <T> operator | (const List <T>& first, const List <T>& second) {
            LOG (__PF, "");

            List <T> first_half  (first);
            List <T> second_half (second);
            if (first_half.tail_ != nullptr)
                first_half.tail_->next_  = second_half.head_;
            if (second_half.head_ != nullptr)
                second_half.head_->prev_ = first_half.tail_;

            second_half.head_ = nullptr;
            second_half.tail_ = nullptr;
            second_half.size_ = 0;

            return first_half;
        }


// intersect 2 lists
        template <typename T>
        List <T> operator ^ (const List <T>& first, const List <T>& second) {
            LOG (__PF, "");

            List <T> ans {};

            List <T> sort1 (first);
            sort1.sort ();

            List <T> sort2 (second);
            sort2.sort ();

            auto it1 = sort1.begin ();
            auto it2 = sort2.begin ();

            while (1) {
                if (it1 == sort1.end () || it2 == sort2.end ())
                    break;

                if (*it1 < *it2) {
                    // ans.push_back (*it1);
                    ++it1;
                }
                else if (*it1 > *it2) {
                    // ans.push_back (*it2);
                    ++it2;
                }
                else {
                    ans.push_back (*it1);
                    ++it1;
                    ++it2;
                }
            }
            return ans;
        }

        template <typename T>
        std::ostream& operator << (std::ostream &out, const Node <T> & node) {
            out << node.data_;
            return out;
        }

        template <typename T>
        std::ostream& operator << (std::ostream &out, const List <T> &list) {
            Node <T> *tmp = list.head_;
            while (tmp != nullptr) {
                out << *tmp << " ";
                tmp = tmp -> next_;
            }
            out << "\n";
            return out;
        }


}

#endif