#ifndef ONEGIN_H
#define ONEGIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define FUNC_NAME __func__ // Defines the function name from which was called 
#define FUNC_LINE __LINE__ // Defines the number of line from which was called

enum error_list
{
    ERR_OPEN_FILE_ONEGIN_TEXT = 1,
    ERR_OPEN_FILE_SORTED_RIGHT_ONEGIN_TEXT = 2,
    ERR_OPEN_FILE_SORTED_LEFT_ONEGIN_TEXT = 3,
    ERR_EMPTY_FILE_ONEGIN_TEXT = 4,
    ERR_CLOSE_FILE_ONEGIN_TEXT = 5,
    ERR_CLOSE_FILE_SORTED_RIGHT_ONEGIN_TEXT = 6,
    ERR_CLOSE_FILE_SORTED_LEFT_ONEGIN_TEXT = 7,
    ERR_NULLPTR_BUFFER = 8,
    ERR_NULLPTR_STRINGS = 9,
    ERR_NULLPTR_STRING = 10
};

typedef struct Onegin_file_struct // for array of char* 
{
    char** strings = nullptr; // The pointer to the array of strings
    char*  buffer_of_chars = nullptr; // The pointer to the buffer which is used in order to store all file's characters
    FILE*  onegin_original = nullptr; // The pointer to the file with original onegin 
    FILE*  onegin_left_sorted = nullptr; // The pointer to the file with left sorted onegin
    FILE*  onegin_right_sorted = nullptr; // The pointer to the file with right sorted onegin
    size_t number_of_lines = 0; // Number of lines in the buffer
    size_t error_code = 0; // Error code of struct
    size_t position_of_line_in_buffer = 0; // Stores the current position of line
    size_t size_of_onegin = 0; // Number of chars in the buffer 

}Onegin_type;


void check_onegin_for_openning(Onegin_type* onegin); // Сhecks the file for openning with originalOnegin text
void check_sorted_left_file_for_openning(Onegin_type* onegin); // Сhecks for openning file with sorted left Onegin text
void check_sorted_right_file_for_openning(Onegin_type* onegin); // Сhecks for openning file with sorted right Onegin text


const char* enum_to_string(size_t code); // Converts an enum's int value to the enum's string value
char* strchr_slash_n_my(Onegin_type* onegin); // Searches the end of the next line
char* get_string(Onegin_type* onegin); // Gets the pointer to the string 


void onegin_dump(Onegin_type* onegin, const char* FUNCTION_NAME, size_t FUNCTION_LINE); // Outputs all information about the onegin stack into the LOG_FILE.txt
void get_num_of_chars_in_file(Onegin_type* onegin); // Returns the sizeof(number of chars) onegin
void fill_the_array (Onegin_type* onegin); // Fills the array with pointers to the string
void create_array_strings(Onegin_type* onegin); // Creates the array of strings
void onegin_debug_print(Onegin_type* onegin); // For debug print only
void onegin_dtor(Onegin_type* onegin); // Frees all pointers and deletes
                                       // all data about onegin struct                        
void create_buffer_for_chars(Onegin_type* onegin); // Allocates memory for the buffer of chars
void read_onegin_into_buf(Onegin_type* onegin); // Reads onegin text into the buffer
void fputs_my(char* string_to_fputs, FILE* check_sorted_file_for_openning); // Prints ONLY ONE STRING into the file Onegin_sorted_-----.txt
void print_strings_to_file(Onegin_type* onegin, FILE* check_sorted_file_for_openning); // Prints ALL ARRAY OF STRING into the file Onegin_sorted_-----.txt
void sort_strings(Onegin_type* onegin); // Sorts the array of strings


size_t count_num_of_lines_in_buf(Onegin_type* onegin); // Counts the number of lines
size_t strlen_slash_n_my(char* str); // Returns the length of the string with \n and without \r
size_t strlen_slash_n_my_no_spaces(char* str); // Returns the length of the string without \r, \n and spaces


int comparator_left_to_right(const void* string_a, const void* string_b); // Used in order to compare two strings (TO_THE_RIGHT_SORT)
int comparator_right_to_left(const void* string_a, const void* string_b); // Used in order to compare two strings (TO_THE_LEFT_SORT)
int strcmp_right_to_left(const char* string_a, const char* string_b); // Sorts the onegin from the right to the left
int strcmp_left_to_right(const char* string_a, const char* string_b); // Sorts the onegin from the left to the right

#endif