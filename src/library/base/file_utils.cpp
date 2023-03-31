/*
 * FileUtils.cpp
 *
 *  Created on: Oct 8, 2019
 *      Author: devel
 */

#include <fstream>
#include <string>
#include <cerrno>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <errno.h>
#include <cstring>

#include "file_utils.hpp"
#include "string_utils.h"


namespace license {
using namespace std;

vector<string> filter_existing_files(const vector<string> &fileList,
		EventRegistry& registry,const char* extraData) {
	vector<string> existingFiles;
	for (auto it = fileList.begin(); it != fileList.end(); it++) {
		registry.addEvent(LICENSE_SPECIFIED,it->c_str(), extraData);
		ifstream f(it->c_str());
		if (f.good()) {
			existingFiles.push_back(*it);
			registry.addEvent(LICENSE_FOUND,it->c_str(),extraData);
		} else {
			registry.addEvent(LICENSE_FILE_NOT_FOUND,it->c_str(), extraData);
		}
		f.close();
	}
	return existingFiles;
}

string get_file_contents(const char *filename, size_t max_size) {
	string contents;
	ifstream in(filename, std::ios::binary);
	if (in) {
		size_t index = (size_t)in.seekg(0, ios::end).tellg();
		size_t limited_size = min(index, max_size);
		contents.resize(limited_size);
		in.seekg(0, ios::beg);
		in.read(&contents[0], limited_size);
		in.close();
	} else {
		throw runtime_error(std::strerror(errno));
	}
	return contents;
}

string remove_extension(const string& path) {
	if (path == "." || path == "..") {
		return path;
	}
	size_t dotpos = path.find_last_of(".");
	//no dot
	if (dotpos == string::npos) {
		return path;
	}
	//find the last path separator
	size_t pathsep_pos = path.find_last_of("\\/");
	if (pathsep_pos == string::npos) {
		return (dotpos == 0 ? path : path.substr(0, dotpos));
	} else if(pathsep_pos >= dotpos +1) {
		return path;
	}
	return path.substr(0, dotpos);
}

string read_text_file(const std::string &file_path, bool * const read_ok)
{
	std::ifstream file(file_path);
	if (read_ok) {
		*read_ok = bool(file);
	}

	if (file) {
		std::stringstream buffer;
		buffer << file.rdbuf();
		const std::string file_contents = buffer.str();
		return file_contents;
	}
	return {};

}

std::vector<string> read_lines_text_file(const std::string &file_path, const std::string &separator,
										 const bool keep_empty, bool * const read_ok)
{
	const std::string file_text = read_text_file(file_path, read_ok);
	const std::vector<std::string> text_lines = split_string(file_text, separator, keep_empty);
	return text_lines;
}

std::vector<string> filter_lines_text_file(const std::string &text_file_path, const std::string &filter_text,
										   const std::string &lines_separator, bool * const read_ok)
{
	const std::string file_text = read_text_file(text_file_path, read_ok);
	const std::vector<std::string> text_lines = split_string(file_text, lines_separator);
	const std::vector<std::string> filtered_lines = filter_string_lines(text_lines, filter_text);
	return filtered_lines;
}

std::vector<string> filter_lines_text_file(const std::string &text_file_path, const std::vector<std::string> &filters,
										   const std::string &lines_separator, bool * const read_ok)
{
	const std::string file_text = read_text_file(text_file_path, read_ok);
	const std::vector<std::string> text_lines = split_string(file_text, lines_separator);
	const std::vector<std::string> filtered_lines = filter_string_lines(text_lines, filters);
	return filtered_lines;
}

}
