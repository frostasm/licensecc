/*
 * StringUtils.h
 *
 *  Created on: Apr 8, 2014
 *
 */

#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

#include <cstring>
#include <string>
#include <vector>

namespace license {

/**
 * Eliminate whitespace from both sides of a string and returns a copy
 * of the string itself.
 * @param string_to_trim
 * @return the trimmed string
 */
std::string trim_copy(const std::string& string_to_trim);

std::string toupper_copy(const std::string& lowercase);

time_t seconds_from_epoch(const std::string& timeString);

/**
 * Split a string on a given character
 */
const std::vector<std::string> split_string(const std::string& stringToBeSplit, const char splitchar);

/**
 * Split a string on a given string separator
 */
std::vector<std::string> split_string(const std::string& text, const std::string& separator,
									  const bool keep_empty = true);

/**
 * returns strings that contain a case-sensitive filter_pattern (regex not supported)
 */
std::vector<std::string> filter_string_lines(const std::vector<std::string>& string_lines,
											 const std::string& filter_pattern);

/**
 * replace first "from" substring with "to" value
 */
bool replace_string(std::string& str, const std::string& from, const std::string& to);

/**
 * pretty print vector of strings to std::out
 */
void print_string_vector(const std::vector<std::string>& vec, const std::string &description = {});

// strnln_s is not well supported and strlen is marked unsafe..
size_t mstrnlen_s(const char* szptr, size_t maxsize);

// strlcpy is not a standard function but it's the safest way to copy to c strings...
// let's provide a custom implementation
size_t mstrlcpy(char* dst, const char* src, size_t n);
typedef enum {
	INI, BASE64, UNKNOWN
} FILE_FORMAT;

FILE_FORMAT identify_format(const std::string& license);

template<typename T, size_t C_ARRAY_SIZE>
bool copy_string_to_c_array(const std::string& src, T (&dst)[C_ARRAY_SIZE])
{
	static_assert(std::is_same<T, char>::value || std::is_same<T, unsigned char>::value,
				"dst must be an array of char or unsigned char");

	const size_t src_len = src.length();
	const size_t dst_len = C_ARRAY_SIZE - 1; // leave space for the null terminator
	const size_t copy_len = src_len > dst_len ? dst_len : src_len;
	std::strncpy(reinterpret_cast<char*>(dst), src.c_str(), copy_len);
	dst[copy_len] = '\0';
	return copy_len == src_len;
}
}

/* namespace license */

#endif /* STRINGUTILS_H_ */
