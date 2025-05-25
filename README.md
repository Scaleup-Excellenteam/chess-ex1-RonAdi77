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

## 📊 Performance Comparison

To evaluate the effectiveness of our parallel implementation, we ran an 8-move auto-play game at **depth 2**, comparing runtime across different thread counts:

| Threads | Runtime (seconds) |
|---------|-------------------|
| 0       | 32s               |
| 2       | 22s               |
| 4       | 15s               |
| 8       | 12s               |

---

### 📸 Example Output

Below is an example run showing the system output for each thread count (0, 2, 4, 8):

![F349DCD9-D3C7-4284-859D-6ADE3EAF7D8A](https://github.com/user-attachments/assets/ec328e34-b3f8-4524-acf4-95578a6ad4c1)

---

### 💡 Analysis

- **Single-threaded mode (0 threads)** is the slowest, as all move evaluations are performed sequentially.
- **2 threads** already achieves a noticeable performance boost through parallelism.
- **4 threads** provides a significant speedup over 2 threads, efficiently distributing the workload across typical piece counts.
- **8 threads** gives the best time, though gains taper off due to:
  - **Thread management overhead**
  - **Idle threads** when fewer pieces are left to evaluate
  - The **early-stopping** mechanism (`stopFlag`) halting computations once a winning move is detected—this does not always distribute work evenly.

---

### 🧠 Conclusion

Our parallel Minimax engine shows strong scalability up to 8 threads for shallow searches (depth 2). For deeper searches or more complex positions, we expect even greater relative gains from multithreading.

