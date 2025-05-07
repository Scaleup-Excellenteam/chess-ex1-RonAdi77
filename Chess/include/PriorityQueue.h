#pragma once
#include <list>
#include <iostream>

template <typename T>
struct MyComparator {
    /**
     * @brief Compares two elements using subtraction.
     * @param a First element.
     * @param b Second element.
     * @return Negative if a < b, zero if a == b, positive if a > b.
     */
    int operator()(const T& a, const T& b) const {
        return a - b;
    };
};
/**
 * @brief A fixed-size (top-5) priority queue that stores elements in ascending order using a comparator.
 * Keeps only the 5 best elements at any time.
 * @tparam T The type of elements stored in the priority queue.
 */
template <typename T>
class PriorityQueue{
public:
    /**
     * @brief Inserts an element into the priority queue in sorted order.
     * If the size exceeds 5, the least relevant (first) item is discarded.
     * @param t The element to insert.
     */
    void push(const T&);
    /**
     * @brief Removes and returns the element with the highest priority (last in the list).
     * @return The element with the highest priority.
     */
    T pull();
    /**
    * @brief Assigns another priority queue to this one.
    * @param other The priority queue to copy from.
    * @return Reference to this priority queue.
    */
    PriorityQueue<T>& operator=(const PriorityQueue<T>&);
    /**
     * @brief Prints the top 3 elements from the queue in descending order of priority.
     */
    void print();

private:
    std::list<T> _queue;
    MyComparator<T> _comparator;
};

template<typename T>
void PriorityQueue<T>::print() {

    int cnt = 1;
    auto it = _queue.end();
      // Skip the first (size - 3) elements
    while (it-- != _queue.begin()) {
        std::cout << cnt <<". Recommended move: " << *it << std::endl;
        cnt++;
        if (cnt > 3){
            break;
        }
    }
}

template<typename T>
PriorityQueue<T> &PriorityQueue<T>::operator=(const PriorityQueue<T> & other) {
    _queue = other._queue;
    return *this;
}

template<typename T>
void PriorityQueue<T>::push(const T& t) {
    for (auto it = _queue.begin() ; it != _queue.end() ; it++ ){
        if (_comparator(t,*it) < 0){
           _queue.insert(it,t);
           if ( _queue.size() > 5){
               _queue.pop_front();
           }
            return;
        }
    }
    _queue.push_back(t);
    if ( _queue.size() > 5){
        _queue.pop_front();
    }
}

template<typename T>
T PriorityQueue<T>::pull() {
    T back = _queue.back();
    _queue.pop_back();
    return back;
}
