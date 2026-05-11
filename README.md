# Multi-Threaded File Searcher (C++17)

A high-performance command-line tool built to search for specific strings across multiple files and directories using a custom **Thread Pool** implementation.

## Performance
The core of this project is a custom-built Thread Pool that efficiently distributes file-scanning tasks across all available CPU cores.

* **Sequential Search:** ~12.0 ms
* **Multi-threaded Search:** ~3.0 ms
* **Speedup:** **~4x faster** (tested on an 8-thread CPU)

## Key Features
* **Custom ThreadPool:** Uses a task queue and worker threads to eliminate thread creation overhead.
* **Smart Filtering:** Automatically skips binary files (`.exe`, `.pdf`, `.jpg`, etc.) to optimize search speed.
* **Thread Safety:** Implements `std::atomic` for result counting and `std::condition_variable` for synchronization.
* **Modern C++:** Built with C++17 using the `std::filesystem` library.

## Build & Usage

### Prerequisites
* GCC/G++ compiler with C++17 support
* `make` utility

### Compilation
Run the Makefile from the root directory:
```bash
make
```
### Running the program
The executable is generated in the `build/` directory:
```bash
./build/searcher <directory_path> <search_query>
```
### 📂 Project Structure
*   `src/`: Source code (`.cpp` and `.hpp` files).
*   `build/`: Target directory for the compiled binary (ignored by Git).
*   `Makefile`: Build automation script.

### 🧠 How it Works
*   **Discovery**: Uses `recursive_directory_iterator` to find all valid text files.
*   **Task Queue**: Files are pushed as tasks into the **Thread Pool**.
*   **Parallel Search**: Worker threads scan files simultaneously and update an **atomic counter**.
*   **RAII Cleanup**: The Thread Pool's destructor ensures all threads join safely before the program exits.
