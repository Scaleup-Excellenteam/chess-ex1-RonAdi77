# Chess Engine Project

## 🧠 Project Overview
This is a C++ implementation of a command-line chess engine that supports both human vs. human and human vs. computer play. The computer player uses a Minimax-based algorithm with multithreaded move evaluation to determine the best possible move at each turn.

## 🛠️ Build & Run Instructions

```bash
mkdir build
cd build
cmake ..
make
./<script-name>
```

When running the program, you will be prompted to select a game mode:

```text
choose mode: (0 = manual, 1 = computer): 1
Enter search depth: 3
```

- **0** – Manual mode (user vs. user)
- **1** – Computer mode (user vs computer)

## 📁 Project Structure

The project is organized into two main directories:
- `include/`: Contains all header (`.h`) files.
- `src/`: Contains all implementation (`.cpp`) files.

Additional implementation structure:
- Each chess piece has its own dedicated implementation.
- There is a dedicated module for the `PriorityQueue` used to evaluate and rank moves.
- Multithreading logic is implemented to allow concurrent move evaluation.
- The best-move algorithm (Minimax) has its own dedicated implementation for clarity and performance separation.

## ♟️ Implemented Features

### ✅ Chess Rules Implemented

We implemented all three required rules:

1. **Check & Checkmate**
2. **Castling**
   - All types of castling (short and long, both colors) are fully supported.
3. **Draw Conditions**, including:
   - **Stalemate**
   - **Threefold repetition**
   - **Insufficient material**

## 🤖 Computer Player Logic

- The human always plays **White** and starts the game.
- After the user's move, the computer calculates its move using a **Minimax-based algorithm**.
- All possible moves are evaluated using a **Priority Queue**, and the best move is selected.
- The evaluation considers material value, threats, and board control.

## 🧪 Testing

- Manual testing was done using various board setups.
- Extensive use of **print statements** helped trace behavior and debug logic.
- Edge cases were specifically tested, including:
  - Castling validation
  - Stalemate detection
  - Checkmate logic
  - Repetition and draw scenarios

## 🚧 Biggest Challenge

The most challenging part of this project was implementing the **best-move calculation algorithm** (Minimax), especially ensuring performance and correctness in multithreaded evaluation.

## 🌟 Future Improvements

Given more time, here are features we would consider adding:

- **Undo/Redo** functionality
- **Save/Load** game state
- **Timers** for each player
- **GUI** interface 
