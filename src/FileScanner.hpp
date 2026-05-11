#ifndef FILE_SCANNER_HPP
#define FILE_SCANNER_HPP

#include <string>
#include <vector>

bool find_files(const std::string& target_path, std::vector<std::string>& file_list);
int search_in_file(const std::string& file_path, const std::string& query);

#endif