#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <atomic>
#include "PriorityAlgo.h"
#include "Common.h"
#include "Board.h"

/**
 * @brief ThreadPool class for managing a pool of worker threads to execute tasks in parallel.
 */
class ThreadPool {
public:
    /**
    * @brief Constructs a thread pool with a specified number of worker threads.
    * @param numThreads Number of threads to create in the pool.
    */
    explicit ThreadPool(size_t numThreads);
    /**
     * @brief Destroys the thread pool and joins all threads.
     */
    ~ThreadPool();

    /**
     * @brief Enqueues a task for execution by the thread pool.
     * @tparam F Callable type (e.g., lambda, function pointer).
     * @param task A callable task to execute.
     */
    template<class F>
    void enqueue(F&& task);

    /**
     * @brief Blocks until all tasks in the queue are completed.
     */
    void wait();

    /**
     * @brief Threshold value used to filter or stop evaluation early.
     */
    const int threshold = 100;

private:
    std::vector<std::thread> _workers;          ///< Worker threads.
    std::queue<std::function<void()>> _tasks;   ///< Task queue.

    std::mutex _queueMutex;                     ///< Mutex for synchronizing task queue access.
    std::condition_variable _condition;         ///< Condition variable for task availability.
    std::condition_variable _doneCondition;     ///< Condition variable to signal task completion.

    std::atomic<bool> _stopFlag;                ///< Flag to indicate shutdown.
    std::atomic<int> _activeWorkers = 0;        ///< Tracks number of workers currently executing tasks
    /**
     * @brief Main loop for each worker thread to fetch and execute tasks.
     */
    void workerLoop();
};

/**
 * @brief ThreadManager class for handling multithreaded Minimax execution and task distribution.
 */
class ThreadManger{
public:
    /**
     * @brief Manages parallelized Minimax evaluation on all pieces for the current player .
     * @param board Current board state.
     * @param color The color of the player to move.
     * @param depth Minimax search depth.
     * @param numThreads Number of threads to use. If 0, evaluates one piece at a time.
     * @return PriorityQueue containing all evaluated legal moves.
     */
    static PriorityQueue<Move> minMaxManger(Board&, COLOR&, int, int);
    /**
     * @brief Launches one thread per piece to evaluate its moves using Minimax.
     * @param board The current game board.
     * @param color The color of the player to move.
     * @param depth Depth to search in Minimax.
     * @param pieces List of pieces to evaluate.
     * @param globalQueue A shared priority queue to store all legal moves and their scores.
     */
    static void runThreads(Board&, COLOR&, int, std::vector<std::shared_ptr<Piece>>&, PriorityQueue<Move>&);

};
