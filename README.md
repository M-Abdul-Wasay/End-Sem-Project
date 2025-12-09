# ⌨️ Code Flow (CLI)

## 📖 Description
**Code Flow** is a C++ program that runs in the **command-line interface (CLI)**.  
It allows users to practice **touch typing** while measuring their **speed**, **accuracy**, and includes a **dedicated Timer Mode** inspired by platforms like Monkeytype.

---

## 🎯 What the Program Does
- Provides an interactive typing practice environment.  
- Tracks typing speed (**words per minute**) and accuracy (**percentage of correct characters**).  
- Offers a **Timer Mode** for time-bound challenges.  
- Helps users improve typing skills through progressive difficulty levels.  

---

## ⚙️ Features
### 📝 Typing Practice
- **Three Levels of Difficulty**
  - Level 1: Easy word bank, simple speed/accuracy requirements.  
  - Level 2: Moderate difficulty with stricter requirements.  
  - Level 3: Hardest level with challenging word bank and high accuracy demands.  

- **Progression System**
  - Fail a level → pushed back to the previous one.  
  - Clear all three levels → receive a congratulatory message 🎉.  

---

### ⏱️ Timer Mode (Separate Feature)
- Functions like Monkeytype’s timed tests.  
- Choose a countdown duration (e.g., 15s, 30s, 60s).  
- Measures typing speed and accuracy **within the time limit**.  
- Adds pressure and competitiveness to practice sessions.  
- Perfect for users who want to simulate real typing test conditions.  

---

## 🚀 How to Run
1. Compile the program:
   ```bash
   g++ typing_game.cpp -o typing_game
