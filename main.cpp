#include "onegin.h"

int main()
{
    Onegin_type onegin = {}; // Creates empty struct for onegin

    //onegin_debug_print(&onegin);

    FILE* onegin_original = check_onegin_for_openning(); // Returns the pointer to the original file with onegin text 
    FILE* onegin_sorted_left = check_sorted_left_file_for_openning(); // Returns the pointer to the left sorted onegin      
    FILE* onegin_sorted_right = check_sorted_right_file_for_openning(); // Returns the pointer to the right sorted onegin

    get_num_of_chars_in_file(onegin_original, &onegin); // Returns the sizeof(number of chars) onegin
    create_buffer_for_chars(&onegin); // Allocates memory for the buffer of chars
    read_onegin_into_buf(onegin_original, &onegin); // Reads onegin text into the buffer
    count_num_of_lines_in_buf(&onegin); // Counts the number of lines
    create_array_strings(&onegin); // Creates the array of strings
    fill_the_array(&onegin); // Fills the array with pointers to the string

    //onegin_debug_print(&onegin);
    sort_strings(&onegin, onegin_sorted_left, onegin_sorted_right); // Sorts the text with Onegin   

    onegin_dtor(&onegin, onegin_original, onegin_sorted_left, onegin_sorted_right); // Deletes the onegin struct
    //onegin_debug_print(&onegin);

    return 0;
}
