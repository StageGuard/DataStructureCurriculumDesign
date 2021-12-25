## DataStructureCurriculumDesign
### A Double-linked list.

Class definition

```c++
class DLinkedList<T> {
    bool isEmpty(); // return if empty
    bool add(T); // add element at the tail
    bool add(uint32_t, T); // add element at the specific index
    T set(uint32_t, T); // set element at the specific index
    T remove(uint32_t); // remove element at the specific index
    bool remove(T); // remove element that equals it
    T get(uint32_t); // get element at specific index
    clear(); // clear all elements
    traverse(Function); // traverse list with lambda
    traverse_reversed(Function); // traverse list reversed
    contains(T); // return if list contains it
    indexOf(T); // return first index of it or -1 if not exists
    lastIndexOf(T); // return last index of it or -1 if not exists
    size(); // return size
    class Iterator {
        Iterator begin(); // list head
        Iterator end(); // list tail
    };
    iter(); // return the iterator
    riter(); // return the reversed iterator
};

```

Because the `DLinkedList` implements `iterator`, so it supports some STL container operations.

```c++
auto iter = list -> iter();
// for each
for_each(iter.begin(), iter.end(), [&](int e) {
    cout << e << " ";
});
// sum
auto sum = accumulate(iter.begin(), iter.end(), 0);
```