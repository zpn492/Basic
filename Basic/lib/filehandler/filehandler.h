#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#include "..\Logger\logger.h" // filehandler
#include <string>   // filehandler
#include <fstream>  // filehandler
#include <cerrno>   // filehandler
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

namespace filehandler
    {
    extern bool exists_file(const char *filename, Logger &logger);
    
    /* Read an entire file into a string */
    extern std::string get_file_contents(const char *filename, Logger &logger);

    extern bool create_file(const char *filename, Logger &logger);

    extern bool delete_file(const char *filename, Logger &logger);
	
	/* Split a string by charator fx '\n' newline */
    extern std::vector<std::string> split_string(std::string &s, char delimeter);

	/* Divide a string into chunks
	 * Make sure dividing wont create more rows or columns
	 * strings below a length of 10.000 wont be divided.
     */
    extern std::vector<std::string> divide_string(std::string s1, int times);

	/* Write a string into a file
     * If the file already exists, it will be erased before insertion.
     */
    extern void write_file(const char *filename, std::string text);

    extern void print_file(const char *filename, Logger &logger);

    extern std::string int_to_string(int value);
	
	extern void replace(std::string &s, char before, char after);
	
    };
#endif