/*
 * FileUtils.h
 *
 *  Created on: Apr 8, 2019
 *
 */

#ifndef FILEUTILS_H_
#define FILEUTILS_H_
#include <string>
#include <vector>
#include "EventRegistry.h"

namespace license {

std::vector<std::string> filter_existing_files(const std::vector<std::string>& fileList,EventRegistry& registry,
											   const char* extraData);
std::string get_file_contents(const char *filename,size_t max_size);
std::string remove_extension(const std::string& path);

/**
 * read proc text files
 */
std::string read_text_file(const std::string &text_file_path, bool * const read_ok = nullptr);
std::vector<std::string> read_lines_text_file(const std::string &text_file_path, const std::string& separator = "\n",
											const bool keep_empty = true, bool * const read_ok = nullptr);
std::vector<std::string> filter_lines_text_file(const std::string& text_file_path, const std::string& filter_text,
												const std::string& lines_separator = "\n", bool * const read_ok = nullptr);
std::vector<std::string> filter_lines_text_file(const std::string& text_file_path, const std::vector<std::string>& filters,
												const std::string& lines_separator = "\n", bool * const read_ok = nullptr);

} /* namespace license */

#endif
