# ♟️ Chess Part2 – Exception Handling & Minimax Algorithm

## 📌 Custom Exceptions

This project defines two custom exception classes used for robust error handling in specific chess scenarios:

### 1. `WrongPromotionInput`
- **Thrown when**: A player inputs an invalid choice during pawn promotion.
- **Use case**:  
  When a pawn reaches the last rank, the player is prompted to choose a promotion (1–4).  
  If the input is invalid (e.g., not 1–4), this exception is triggered with a descriptive error message.

### 2. `EmptyPiece`
- **Thrown when**: An operation is attempted on a square without a piece.
- **Use case**:  
  Helps catch logical errors where code mistakenly tries to interact with an empty square as if it holds a piece.

---

## 🧠 Minimax Algorithm with Alpha-Beta Pruning

This project uses a classic **Minimax algorithm** enhanced with **Alpha-Beta pruning** to evaluate and rank potential moves intelligently.

### 🔄 How It Works

- The function `miniMaxMain()` scans all legal moves for the current player.
- Each move is simulated and evaluated recursively by the `miniMax()` function, which:
  - Analyzes board control (e.g., center control, threat zones).
  - Adjusts score based on:
    - Piece captures
    - Threats
    - Positional danger/safety
  - Recursively explores future moves up to a given depth.
- **Alpha-Beta pruning** is used to eliminate unnecessary branches and improve performance.
- The **top 5 moves** are stored in a priority queue, sorted by their evaluation scores.

### ⏱️ Time Complexity

- **b** = average branching factor (number of legal moves per turn)  
- **d** = search depth (how many layers deep the algorithm looks)  
- **Time complexity**: `O(b^d)`
