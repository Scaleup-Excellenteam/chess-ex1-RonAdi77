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


class ThreadPool {
public:
    explicit ThreadPool(size_t numThreads);
    ~ThreadPool();

    template<class F>
    void enqueue(F&& task);

    void wait();

    const int threshold = 100;

private:
    std::vector<std::thread> _workers;
    std::queue<std::function<void()>> _tasks;

    std::mutex _queueMutex;
    std::condition_variable _condition;
    std::condition_variable _doneCondition;

    std::atomic<bool> _stopFlag;
    std::atomic<int> _activeWorkers = 0;

    void workerLoop();
};


class ThreadManger{
public:
    static PriorityQueue<Move> minMaxManger(Board&, COLOR&, int, int);
    static void runThreads(Board&, COLOR&, int, std::vector<std::shared_ptr<Piece>>&, PriorityQueue<Move>&);

};
