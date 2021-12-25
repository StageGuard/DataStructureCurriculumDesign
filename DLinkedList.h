//
// Created by 13554 on 2021/12/24.
//

#ifndef PROJECT_DLINKEDLIST_H
#define PROJECT_DLINKEDLIST_H


#include <cstdint>
#include <exception>

template<typename E>
struct DNode {
    E data;
    DNode *prev, *next;
};

template <typename T>
class DLinkedList {
protected:
    DNode<T> *head, *tail;
    uint32_t length;

private:

    ~DLinkedList() { clear(); }

    DNode<T>* createNode(T element) {
        auto *node = new DNode<T>;
        if (node == nullptr) return nullptr;

        node -> data = element;
        node -> next = nullptr;

        return node;
    }

    template <class Function>
    void traverse_with_blocking(Function f, bool reversed = false) {
        DNode<T> *current = reversed ? tail : head;
        bool continueTraverse;

        do {
            continueTraverse = f(current);
            current = reversed ? current -> prev : current -> next;
        } while (current != nullptr && continueTraverse);
    }

public:
    DLinkedList() {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    // low-level api
    bool isEmpty() {
        return (head == nullptr && tail == nullptr) || length == 0;
    }

    bool add(T element) {
        DNode<T> *node = createNode(element);
        if (node == nullptr) return false;

        if (head == nullptr) { // no element
            head = node;
            head -> prev = nullptr;
        } else if (tail == nullptr) { // 1 element
            node -> prev = head;
            head -> next = node;
            tail = node;
        } else { // 2 or more elements
            node -> prev = tail;
            tail -> next = node;
            tail = node;
        }

        length ++;

        return true;
    }

    bool add(uint32_t index, T element) {
        DNode<T> *node = createNode(element);
        if (node == nullptr) return false;

        if (length == 0) { // empty
            return add(element);
        } else if (length == 1) { // 1 element
            if (index == 0) {
                node -> next = head;
                node -> prev = nullptr;
                head -> prev = node;
                tail = head;
                head = node;
                length ++;
                return true;
            } else {
                return add(element);
            }
        } else { // more than 2 elements
            if (index == 0) { // add at the head
                node -> next = head;
                node -> prev = nullptr;
                head -> prev = node;
                head = node;
            } else if (index + 1 >= length) { // add at the tail
                node -> prev = tail;
                tail -> next = node;
                tail = node;
            } else {
                DNode<T> *target = head;
                uint32_t ptr = 0;
                do {
                    target = target -> next;
                    ptr ++;
                } while (ptr < index);

                node -> next = target;
                node -> prev = target -> prev;
                target -> prev -> next = node;
                target -> prev = node;
            }

            length ++;

            return true;
        }
    }

    T set(uint32_t index, T element) {
        if (length == 0 || index + 1 > length)
            throw std::exception();

        DNode<T> *target = head;
        uint32_t ptr = 0;

        do {
            target = target -> next;
            ptr ++;
        } while (ptr < index);

        T original = target -> data;
        target -> data = element;

        return original;
    }

    T remove(uint32_t index) {
        T data;
        if (length == 0) { // empty
            throw std::exception();
        } else if (length == 1) { // 1 element
            data = head -> data;
            clear();
            return data;
        } else { // more than 2 elements
            if (index == 0) { // remove at the head
                head -> next -> prev = nullptr;
                DNode<T> *second = head -> next;
                data = head -> data;
                delete head;
                head = second;
            } else if (index + 1 >= length) { // remove at the tail
                tail -> prev -> next = nullptr;
                DNode<T> *lastLast = tail -> prev;
                data = tail -> data;
                delete tail;
                tail = lastLast;
            } else {
                DNode<T> *target = head;
                uint32_t ptr = 0;
                do {
                    target = target -> next;
                    ptr ++;
                } while (ptr < index);

                target -> prev -> next = target -> next;
                target -> next -> prev = target -> prev;
                data = target -> data;
                delete target;
            }

            length --;

            return data;
        }
    }

    bool remove(T element) {
        if (length == 0) { // empty
            throw std::exception();
        } else if (length == 1) { // 1 element
            if (head -> data == element) {
                clear();
                return true;
            } else return false;
        } else { // more than 2 elements
            bool removed = false;
            if (head -> data == element) { // remove at the head
                head -> next -> prev = nullptr;
                DNode<T> *second = head -> next;
                delete head;
                head = second;
                removed = true;
            } else if (tail -> data == element) { // remove at the tail
                tail -> prev -> next = nullptr;
                DNode<T> *lastLast = tail -> prev;
                delete tail;
                tail = lastLast;
                removed = true;
            } else {
                DNode<T> *target = head;
                while (target -> next != nullptr) {
                    if (target -> data == element) {
                        target -> prev -> next = target -> next;
                        target -> next -> prev = target -> prev;
                        delete target;
                        removed = true;
                        break;
                    } else {
                        target = target -> next;
                    }
                }
            }
            if (removed) length --;
            return removed;
        }
    }

    T get(uint32_t index) {
        if (index + 1 >= length) throw std::exception();
        DNode<T> *current = head;
        uint32_t ptr = 0;
        do {
            current = current -> next;
            ptr ++;
        } while (current != nullptr && ptr < index);

        return current -> data;
    }

    void clear() {
        DNode<T> *current, *p = head -> next;
        while (p != nullptr) {
            current = p;
            p = p -> next;
            delete current;
        }
        length = 0;
        head = nullptr;
        tail = nullptr;
    }

    // streaming operations
    template <class Function>
    void traverse(Function f) {
        traverse_with_blocking([&](DNode<T> *node) {
            f(node -> data);
            return true;
        });
    }

    template <class Function>
    void traverse_reversed(Function f) {
        traverse_with_blocking([&](DNode<T> *node) {
            f(node -> data);
            return true;
        }, length != 1);
    }

    bool contains(T element) {
        bool found = false;
        traverse_with_blocking([&](DNode<T> *node) {
            bool eq = node -> data == element;
            found = eq;
            return !eq;
        });
        return found;
    }

    int32_t indexOf(T element) {
        int index = 0;
        bool found = false;
        traverse_with_blocking([&](DNode<T> *node) {
            if (node -> data == element) {
                found = true;
                return false;
            } else {
                index ++;
                return true;
            }
        });
        return found ? index : -1;
    }

    int32_t lastIndexOf(T element) {
        int index = length - 1;
        bool found = false;
        traverse_with_blocking([&](DNode<T> *node) {
            if (node -> data == element) {
                found = true;
                return false;
            } else {
                index --;
                return true;
            }
        }, true);
        return found ? index : -1;
    }

    uint32_t size() {
        return length;
    }

    // iterator
    class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
        friend class DLinkedList<T>;

    private:
        DNode<T>* curr_ptr;
        DLinkedList<T>* list;
        bool reversed;

        // iterator implementations
        explicit Iterator(DNode<T>* ptr, bool reversed) : curr_ptr(ptr), reversed(reversed) {}

    public:

        // public constructors
        explicit Iterator(DLinkedList<T>* list, bool reversed = false) : list(list), reversed(reversed) {}

        Iterator begin() { return Iterator(reversed ? list -> tail : list -> head, reversed); }
        Iterator end() { return Iterator(reversed ? list -> head : list -> tail, reversed); }

        T& operator*() const { return curr_ptr -> data; }

        Iterator& operator++ () {
            curr_ptr = reversed ? curr_ptr -> prev : curr_ptr -> next;
            return *this;
        }

        friend bool operator== (const Iterator& a, const Iterator& b) {
            return a.curr_ptr -> data == b.curr_ptr -> data;
        };

        friend bool operator!= (const Iterator& a, const Iterator& b) {
            return a.curr_ptr -> data != b.curr_ptr -> data;
        };
    };

    Iterator iter() { return Iterator(this, false); }
    Iterator riter() { return Iterator(this, length != 1); }
};



#endif //PROJECT_DLINKEDLIST_H
