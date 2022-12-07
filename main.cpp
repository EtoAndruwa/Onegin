#include "onegin.h"

int main()
{
    Onegin_type onegin = {};

    //onegin_debug_print(&onegin);

    FILE* onegin_file = check_onegin_for_openning();
    FILE* onegin_sorted_left_file = check_sorted_left_file_for_openning();
    FILE* onegin_sorted_right_file = check_sorted_right_file_for_openning();

    get_num_of_chars_in_file(onegin_file, &onegin);
    create_buffer_for_chars(&onegin);
    read_onegin_into_buf(onegin_file, &onegin);
    count_num_of_lines_in_buf(&onegin);
    create_array_strings(&onegin);
    fill_the_array(&onegin);

    //onegin_debug_print(&onegin);
    sort_strings(&onegin, onegin_sorted_left_file, onegin_sorted_right_file);

    onegin_dtor(&onegin, onegin_file, onegin_sorted_left_file, onegin_sorted_right_file);
    //onegin_debug_print(&onegin);


    return 0;
}
