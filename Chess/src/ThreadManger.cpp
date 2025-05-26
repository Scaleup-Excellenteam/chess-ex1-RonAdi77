#include "ThreadManger.h"

ThreadPool::ThreadPool(size_t numThreads): _stopFlag(false) {
    for (size_t i = 0; i < numThreads; ++i) {
        _workers.emplace_back([this](){
            this->workerLoop();
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::lock_guard<std::mutex> lock(_queueMutex);
        _stopFlag = true;
    }
    _condition.notify_all();
    for ( std::thread& worker : _workers){
        if (worker.joinable()){
            worker.join();
        }
    }
}

void ThreadPool::workerLoop() {
    while(true){
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(_queueMutex);
            _condition.wait(lock, [this](){
                return _stopFlag || !_tasks.empty();
            });

            if (_stopFlag && _tasks.empty())
                return;

            task = std::move(_tasks.front());
            _tasks.pop();

        }
        task();
        --_activeWorkers;

        if (_activeWorkers == 0){
            std::unique_lock<std::mutex> lock(_queueMutex);
            _doneCondition.notify_all();
        }
    }
}

void ThreadPool::wait() {
    std::unique_lock<std::mutex> lock(_queueMutex);
    _doneCondition.wait(lock, [this]() {
        return _tasks.empty() && _activeWorkers == 0;
    });
}

template<class F>
void ThreadPool::enqueue(F && task) {
    {
        std::lock_guard<std::mutex> lock(_queueMutex);
        _tasks.emplace(std::forward<F>(task));
    }
    ++_activeWorkers;
    _condition.notify_one();
}


PriorityQueue<Move> ThreadManger::minMaxManger(Board & board, COLOR & color, int depth, int numThreads) {
    PriorityQueue<Move> globalQueue;
    auto pieces = board.getPieces(color);
    std::vector<std::shared_ptr<Piece>> activeThreadsPiece;
    if (numThreads <= 0){
        while (!pieces.empty()) {
            activeThreadsPiece.push_back(pieces.back());
            pieces.pop_back();
            runThreads(board, color, depth, activeThreadsPiece, globalQueue);
            activeThreadsPiece.clear();
        }
    }
    else{
        while (!pieces.empty()){
            activeThreadsPiece.clear();
            for (int i = 0; i < numThreads && !pieces.empty(); ++i) {
                activeThreadsPiece.push_back(pieces.back());
                pieces.pop_back();
            }
            runThreads(board,color,depth,activeThreadsPiece,globalQueue);
        }
    }

    return globalQueue;
}

void ThreadManger::runThreads(Board & board, COLOR & color, int depth, std::vector<std::shared_ptr<Piece>> & pieces, PriorityQueue<Move> & globalQueue) {
    ThreadPool threadPool(pieces.size());
    std::mutex queueMutex;
    std::atomic<bool> stopFlag = false;

    for ( const auto& piece : pieces){
        threadPool.enqueue([&, piece](){
            auto potenMoves = piece->getPotenMoves();
            auto temBoard(board);

            for (auto & move : potenMoves){
                if (stopFlag.load()) return;

                auto dest = board.algoGetPiece(move._destination);
                if(dest){
                    dest = dest->pieceSharedPtr();
                }
                auto source = board.algoGetPiece(move._source)->pieceSharedPtr();
                move._score = miniMax( depth, move, temBoard, color, color, INT_MIN, INT_MAX);
                undoMove(move, temBoard, source, dest);

                if (move._score >= threadPool.threshold) {
                    stopFlag.store(true);
                }

                {
                    std::lock_guard<std::mutex> lock(queueMutex);
                    globalQueue.push(move);
                }
            }
        });
    }
    threadPool.wait();
}
