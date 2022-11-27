#ifndef ONEGIN_H
#define ONEGIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

enum error_list
{
    ERR_OPEN_FILE_ONEGIN_TEXT = 1,
    ERR_OPEN_FILE_SORTED_ONEGIN_TEXT = 2,
    ERR_EMPTY_FILE_ONEGIN_TEXT = 3,
    ERR_CLOSE_ONEGIN_TEXT = 4,
    ERR_CLOSE_SORTED_ONEGIN_TEXT = 5,
};

typedef struct Onegin_file_struct // for array of char * 
{
    char** strings = nullptr;
    char*  buffer_of_chars = nullptr; // the pointer to the buffer which is used in order to store all file's characters
    size_t current_line = 0; // 
    size_t number_of_lines = 0;
    size_t error_code = 0;
}Onegin_type;

typedef struct Onegin_string_struct // for single string
{
    char* string = nullptr;
    int   number_of_char = 0;
}String_type;


const char* Enum_to_string(size_t code); // converts an enum's int value to the enum's string value

// size_t count_num_of_lines(FILE* file_with_onegin, Struct* onegin_file_struct);

FILE* check_onegin_for_openning(); // checks the file for openning  with Onegin text

FILE* check_sorted_file_for_openning(); // checks for openning file with sorted Onegin text

void onegin_dump(Onegin_type* onegin, const char* FUNCTION_NAME, size_t FUNCTION_LINE); // OK

size_t get_num_of_chars_in_file(FILE* checked_file_onegin);

#endif