#include "ThreadPool.hpp"
#include "FileScanner.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>

namespace ch = std::chrono;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Use: ./build/searcher <path> <query>" << std::endl;
        return 1;
    }
    std::string path = argv[1];
    std::string query = argv[2];

    if (query.empty())
    {
        std::cout << "Query is empty." << std::endl;
        return 1;
    }

    std::vector<std::string> file_list;

    try
    {
        if (!find_files(path, file_list))
        {
            std::cout << "Error: Invalid path or directory not found." << std::endl;
            return 1;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Critical filesystem error: " << e.what() << '\n';
        return 1;
    }

    std::atomic<int> total_matches(0);
    auto start_time = ch::high_resolution_clock::now();

    {
        ThreadPool pool(std::thread::hardware_concurrency());

        for (const auto& file : file_list)
        {
            pool.enqueue([&total_matches, file, query]() {
                total_matches += search_in_file(file, query);
            });
        }
    }
    
    auto end_time = ch::high_resolution_clock::now();
    ch::duration<double, std::milli> duration = end_time - start_time;

    std::cout << "Found " << total_matches << " occurrences in " 
              << std::fixed << std::setprecision(3)
              << duration.count() << " ms." << std::endl;

    return 0;
}