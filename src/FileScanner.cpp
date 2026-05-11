#include "FileScanner.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

bool find_files(const std::string& target_path, std::vector<std::string>& file_list) {
    try 
    {
        if (fs::exists(target_path) && fs::is_directory(target_path)) 
        {
            for (const auto& entry : fs::recursive_directory_iterator(target_path)) 
            {
                if (fs::is_regular_file(entry.path())) 
                {
                    file_list.push_back(entry.path().string());
                }
            }
            return true;
        }
        return false;
    } 
    catch (const fs::filesystem_error& e) 
    {
        throw;
    }
}

int search_in_file(const std::string& file_path, const std::string& query) {
    std::ifstream file(file_path);
    if (!file.is_open()) return 0;

    std::string line;
    int count = 0;
    while (std::getline(file, line)) 
    {
        size_t position = line.find(query);
        while (position != std::string::npos) 
        {
            count++;
            position = line.find(query, position + query.length());
        }
        
    }
    return count;
}