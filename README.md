# LRU & LFU Cache Simulator (C++)

This project simulates two of the most common cache replacement strategies: Least Recently Used (LRU) and Least Frequently Used (LFU), both implemented in C++ with a simple command-line interface for user interaction.

---

## 🔍 What It Does

- Stores key-value pairs in a fixed-capacity cache.
- Automatically removes the least-used or least-recent item when the cache is full.
- Allows user to:
  - Add (put) key-value pairs
  - Retrieve (get) values by key
  - View current state of the cache

---

## 📚 Concepts Used

- Hash Maps (`unordered_map`)
- Doubly Linked Lists (for LRU ordering)
- Frequency Maps (for LFU logic)
- STL Containers (`list`, `map`)
- Basic OOP in C++

---

## 💡 Why I Built This

While practicing DSA, I came across cache-related problems (like LRU on LeetCode). Instead of just solving them, I wanted to simulate a full cache system and understand how memory management works in real-world systems like browsers, Redis, or databases.

So, I built this CLI-based project as part of my internship prep (esp. for firms like D. E. Shaw that focus on problem-solving and systems thinking).

---

## 🛠️ How to Run

Make sure you have `g++` installed (C++ compiler).

### 📦 Compile:
For LRU:

g++ lru_user_friendly.cpp -o lru
./lru

For LFU:

g++ lfu_user_friendly.cpp -o lfu
./lfu
