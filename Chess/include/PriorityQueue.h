#pragma once
#include <list>
#include <iostream>
#include <optional>
#include <mutex>

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
     * @brief Default constructor.
     */
    PriorityQueue() = default;
    /**
     * @brief Default destructor.
     */
    ~PriorityQueue() = default;
    /**
     * @brief Copy constructor (default).
     * Performs a shallow copy of the internal queue and mutex.
     * Safe only if you do not share the same queue instance across threads.
     * @param other The priority queue to copy.
     */
    PriorityQueue(PriorityQueue& other) = default;
    /**
     * @brief Move constructor.
     * @param other The queue to move from.
     */
    PriorityQueue(PriorityQueue&& other) noexcept;
    /**
     * @brief Move assignment operator.
     * @param other The queue to move from.
     * @return Reference to this priority queue.
     */
    PriorityQueue& operator=(PriorityQueue&& other) noexcept;

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
    std::optional<T> pull();
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
    std::list<T> _queue;            ///< Internal list storing elements in sorted order.
    MyComparator<T> _comparator;    ///< Comparator used for ordering elements.
    mutable std::mutex _mutex;      ///< Mutex to ensure thread-safe access.
};


template<typename T>
PriorityQueue<T> &PriorityQueue<T>::operator=(PriorityQueue &&other) noexcept {
    if (this != &other) {
        std::lock_guard<std::mutex> lock_this(_mutex);
        std::lock_guard<std::mutex> lock_other(other._mutex);
        _queue = std::move(other._queue);
    }
    return *this;
}

template<typename T>
PriorityQueue<T>::PriorityQueue(PriorityQueue &&other) noexcept {
    std::lock_guard<std::mutex> lock(other._mutex);
    _queue = std::move(other._queue);
}


template<typename T>
void PriorityQueue<T>::print() {
    std::lock_guard<std::mutex> lock(_mutex);
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
    if (this == &other) return *this;
    std::lock_guard<std::mutex> lock_this(_mutex);
    std::lock_guard<std::mutex> lock_other(other._mutex);
    _queue = other._queue;
    return *this;
}

template<typename T>
void PriorityQueue<T>::push(const T& t) {
    std::lock_guard<std::mutex> lock(_mutex);

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
std::optional<T> PriorityQueue<T>::pull() {
    std::lock_guard<std::mutex> lock(_mutex);
    if (_queue.empty()){
        return std::nullopt;
    }
    T back = _queue.back();
    _queue.pop_back();
    return back;
}
