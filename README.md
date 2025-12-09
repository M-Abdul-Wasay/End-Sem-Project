# ⌨️ Code Flow (CLI)

## 📖 Description
**Code Flow** is a C++ program that runs in the **command-line interface (CLI)**.  
It allows users to practice **touch typing** while measuring their **speed**, **accuracy**, and now includes a **⏱️ timer feature** to add time-based challenges.

---

## 🎯 What the Program Does
- Provides an interactive typing practice environment.  
- Tracks typing speed (**words per minute**) and accuracy (**percentage of correct characters**).  
- Introduces a **timer challenge** to test consistency under pressure.  
- Helps users improve typing skills through progressive challenges.  

---

## ⚙️ Features
- **Three Levels of Difficulty**
  - Level 1: Easy word bank, simple speed/accuracy requirements.  
  - Level 2: Moderate difficulty with stricter requirements.  
  - Level 3: Hardest level with challenging word bank and high accuracy demands.  

- **Progression System**
  - Fail a level → pushed back to the previous one.  
  - Clear all three levels → receive a congratulatory message 🎉.  

- **⏱️ Timer Feature**
  - Each session runs against a countdown timer.  
  - Encourages faster typing while maintaining accuracy.  
  - Adds a competitive edge to practice.  

---

## 🚀 How to Run
1. Compile the program:
   ```bash
   g++ typing_game.cpp -o typing_game

