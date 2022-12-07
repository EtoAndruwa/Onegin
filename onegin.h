#ifndef ONEGIN_H
#define ONEGIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

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
    size_t position_of_line_in_buffer = 0;
    size_t size_of_onegin = 0;
}Onegin_type;



const char* enum_to_string(size_t code); // converts an enum's int value to the enum's string value

FILE* check_onegin_for_openning(); // checks the file for openning  with Onegin text

FILE* check_sorted_file_for_openning(); // checks for openning file with sorted Onegin text

void onegin_dump(Onegin_type* onegin, const char* FUNCTION_NAME, size_t FUNCTION_LINE); // OK

void get_num_of_chars_in_file(FILE* checked_file_onegin, Onegin_type* onegin);

char* strchr_slash_n_my(Onegin_type* onegin);

void fill_the_array (Onegin_type* onegin);

char* get_string(Onegin_type* onegin);

void create_array_strings(Onegin_type* onegin);

void onegin_debug_print(Onegin_type* onegin); // for debug only

void onegin_dtor(Onegin_type* onegin, FILE* checked_file_onegin, FILE* checked_file_sorted_onegin);

void create_buffer_for_chars(Onegin_type* onegin);

void read_onegin_into_buf(FILE* checked_file_onegin, Onegin_type* onegin);

size_t count_num_of_lines_in_buf(Onegin_type* onegin);

size_t strlen_slash_n_my(char* str);

void fputs_my(char* string_to_fputs, FILE* check_sorted_file_for_openning);

void print_strings_to_file(Onegin_type* onegin, FILE* check_sorted_file_for_openning);

void sort_strings(Onegin_type* onegin);

int comparator(const void* string_a, const void* string_b);

int check_for_spaces(char* start_of_string, char* end_of_string);

#endif