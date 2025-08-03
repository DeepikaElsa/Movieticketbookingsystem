# 🎬 Multi-threaded Movie Ticket Booking System in C

This project is a **multi-threaded console application** in C that simulates a movie ticket booking system for multiple customers. Each customer runs in a separate thread, and ticket availability is controlled using mutex locks to avoid race conditions.

---

## 🧠 Features

- Supports concurrent booking using POSIX threads (`pthread`)
- Ensures **thread-safe access** to shared ticket resources
- Dynamically handles user input for multiple customers
- Generates individual **invoices** for each customer
- Tracks **ticket availability** for each of 5 movies

---

## 🎞️ Movie List

| Movie Number | Movie Name   |
|--------------|--------------|
| 1            | Leo          |
| 2            | Frozen       |
| 3            | Loki         |
| 4            | One Piece    |
| 5            | Home Alone   |

---

## 🧰 Requirements

- GCC or any C compiler supporting pthreads
- Linux or WSL (recommended), or use MinGW on Windows

---

## 🔧 Compilation

To compile the code:

```bash
gcc movie_ticket_booking.c -o booking -lpthread
```
## ▶️ How to Run

```bash
./booking
```
## 🚨 Notes
- pthread_join() is called inside the loop, meaning threads run sequentially, not in parallel. For true concurrency, move pthread_join() outside the loop.
- fflush(stdin) is undefined behavior in some compilers. You may consider using getchar() to clear the buffer in a portable way.
- Input validation is minimal — production systems should include more robust error handling.

## 🧾 Structure

- Invoice struct — Stores customer ID, movie choice, and number of tickets purchased
- tickets_available[5] — Shared array for remaining tickets per movie
- ticket_mutex — Ensures atomic access to ticket data
