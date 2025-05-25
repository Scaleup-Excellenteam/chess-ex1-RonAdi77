## 🚀 Chess Part 3 – Multithreading, Synchronization & Performance Benchmarking

### 🧵 Thread Pool Based Parallelism

To enhance the performance of the Minimax algorithm, we implemented **parallel move evaluation** using a custom `ThreadPool` class.

#### ✅ Work Division

- Each thread is responsible for evaluating the potential moves of **one chess piece**.
- For thread safety, the `Board` is cloned per thread (`Board tempBoard = board`).
- If there are **more pieces than threads**, the evaluation is split into batches.

### 🔐 Synchronization

- Access to the **global `PriorityQueue<Move>`** is synchronized using a `std::mutex`.
- An **early-stopping mechanism** is employed:
  - If a thread finds a move with a score exceeding a certain threshold (e.g., `100`), it sets an atomic flag: `std::atomic<bool> stopFlag = true`.
  - All other threads periodically check this flag and terminate early if it is set.

---

### 📊 Performance Comparison

To evaluate the effectiveness of our parallel implementation, we ran an 8-move auto-play game at **depth 2**, comparing runtime across different thread counts:

| Threads | Runtime (seconds) |
|---------|-------------------|
| 0       | 67s               |
| 2       | 46s               |
| 4       | 31s               |
| 8       | 22s               |

---

### 💡 Analysis

- **Single-threaded mode (0 threads)** is the slowest, as all move evaluations are computed sequentially.
- With **2 threads**, we see a noticeable speedup due to basic parallelization.
- **4 threads** achieves nearly 2× improvement over 2 threads, highlighting efficient workload distribution.
- **8 threads** offers the fastest result, but with diminishing returns due to:
  - Overhead from thread management.
  - Some threads becoming idle when fewer pieces remain to evaluate.
  - **Early stopping** (via `stopFlag`) reducing total computation but not always evenly across threads.

---

### 🧠 Conclusion

Our parallel Minimax engine scales well up to **4–8 threads** for depth 2. For deeper searches, the performance gap will likely grow even more significantly in favor of **multithreading**.
