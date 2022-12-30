#include "onegin.h"

#define FUNC_NAME __func__ // Defines the function name from which was called 
#define FUNC_LINE __LINE__ // Defines the number of line from which was called

size_t count_num_of_lines_in_buf(Onegin_type* onegin) // (OK) Counts the number of lines
{
    size_t number_of_lines = 0;

    for(size_t i = 0; i < onegin->size_of_onegin; i++)
    {       
        if(onegin->buffer_of_chars[i] == '\n')
        {  
            number_of_lines++;
        }
        if((onegin->buffer_of_chars[i] != '\n') && (i == (onegin->size_of_onegin - 1))) // If it is the last line without \n
        {
            onegin->buffer_of_chars[onegin->size_of_onegin] = '\n';
            onegin->size_of_onegin++;
            number_of_lines++;
            break;
        }
    }
    onegin->number_of_lines = number_of_lines;
    return 0;
}

FILE* check_onegin_for_openning() // Checks the file with original Onegin for openning 
{
    FILE* checked_file_onegin = fopen("Onegin_original.txt", "rb"); // Opens for reading original file 
    if(checked_file_onegin == nullptr)
    {   
        printf("ERROR: File with original Onegin text cannot be openned. Please, check file with original Onegin text.\n");
        // onegin_dump(onegin, FUNC_NAME, FUNC_LINE);
        // onegin_dtor(onegin,);
    }
    else
    {
        printf("File \"Onegin_original.txt\" was openned\n");
        return checked_file_onegin;
    }
}
 
FILE* check_sorted_left_file_for_openning() // Checks the file with sorted Onegin text for openning 
{   
    FILE * checked_left_file_sorted_onegin = fopen("Onegin_sorted_left.txt", "wb"); 
    if(checked_left_file_sorted_onegin == nullptr)
    {
        printf("ERROR: File with sorted Onegin left text cannot be openned. Please, check file with sorted Onegin text.\n");
        // onegin_dump(onegin, FUNC_NAME, FUNC_LINE);
        // onegin_dtor(onegin,);
    }
    else
    {
        printf("File \"Onegin_sorted_right.txt\" was openned\n");
        return checked_left_file_sorted_onegin;
    }
}

FILE* check_sorted_right_file_for_openning() // Checks the file with sorted Onegin text for openning 
{   
    FILE * checked_right_file_sorted_onegin = fopen("Onegin_sorted_right.txt", "wb"); 
    if(checked_right_file_sorted_onegin == nullptr)
    {
        printf("ERROR: File with sorted Onegin right text cannot be openned. Please, check file with sorted Onegin text.\n");
        // onegin_dump(onegin, FUNC_NAME, FUNC_LINE);
        // onegin_dtor(onegin,);
    }
    else
    {
        printf("File \"Onegin_sorted_left.txt\" was openned\n");
        return checked_right_file_sorted_onegin;
    }
}

void create_buffer_for_chars(Onegin_type* onegin) // (OK) Allocates memory for the buffer of chars
{
    onegin->buffer_of_chars = (char*)calloc(1, onegin->size_of_onegin * sizeof(char));
}

const char* enum_to_string(size_t error_code) // (OK) Converts an enum's int value to the enum's string value 
{
    switch(error_code)
    {
        case 1:
            return "ERR_OPEN_FILE_ONEGIN_TEXT";
            break;
        case 2:
            return "ERR_OPEN_FILE_SORTED_ONEGIN_TEXT";
            break;
        case 3:
            return "ERR_EMPTY_FILE_ONEGIN_TEXT";
            break;
        case 4:
            return "ERR_CLOSE_ONEGIN_TEXT";
            break;
        case 5:
            return "ERR_CLOSE_SORTED_ONEGIN_TEXT";
            break;
        default:
            return "STACK IS OK"; 
            break;
    }
}

void onegin_dump(Onegin_type* onegin, const char* FUNCTION_NAME, size_t FUNCTION_LINE) // (OK) Outputs all information about the onegin stack into the LOG_FILE.txt
{
    FILE* logfile = fopen("LOG_FILE.txt", "a+");

    fprintf(logfile, "-------------------START OF LOG_SESSION------------------------\n\n");
    fprintf(logfile, "Error code = %ld\n", onegin->error_code);
    fprintf(logfile, "Called from file: %s\n", __FILE__);
    fprintf(logfile, "Called error function name: %s\n", FUNCTION_NAME);
    fprintf(logfile, "Called from line: %ld\n", FUNCTION_LINE);    
    fprintf(logfile, "Date when was called: %s\n", __DATE__);
    fprintf(logfile, "Time when was called: %s\n\n", __TIME__);

    fprintf(logfile, "Pointer to the array: %p\n", onegin->strings);
    fprintf(logfile, "Pointer to the buffer of chars: %p\n", onegin->buffer_of_chars);
    fprintf(logfile, "Current line: %ld\n", onegin->current_line);
    fprintf(logfile, "Total numver of lines: %ld\n", onegin->number_of_lines);
    fprintf(logfile, "--------------------END OF LOG_SESSION--------------------------\n\n");

    fclose(logfile);
}

void get_num_of_chars_in_file(FILE* checked_file_onegin, Onegin_type* onegin) // (OK) Returns the sizeof(number of chars) onegin 
{   
    rewind(checked_file_onegin); // Returns the pointer inside the file to the initial position

    fseek(checked_file_onegin, 0, SEEK_END); // Puts the pointer to the end of file 
    onegin->size_of_onegin = ftell(checked_file_onegin); // Returns the total number of bytes (1 char = 1 byte) -> number of chars WITH \R and without EOF
   
    rewind(checked_file_onegin); // Returns the pointer inside the file to the initial position
}

void onegin_dtor(Onegin_type* onegin, FILE* checked_file_onegin, FILE* checked_file_left_sorted_onegin, FILE* checked_file_right_sorted_onegin) // (OK) Frees all pointers and deletes 
{                                                                                                                                               // all data about onegin struct
    free(onegin->buffer_of_chars); // Frees the buffer of chars
    for(size_t i = 0; i < onegin->number_of_lines; i++) // Frees every string in the array of strings
    {
        free(onegin->strings[i]);
        onegin->strings[i] = nullptr;
    }
    free(onegin->strings); // Frees the pointer to the array of strings

    onegin->buffer_of_chars = nullptr; 
    onegin->strings = nullptr;

    onegin->current_line = 0;
    onegin->error_code = 0;
    onegin->number_of_lines = 0;
    onegin->position_of_line_in_buffer = 0 ;

    fclose(checked_file_onegin);
    fclose(checked_file_left_sorted_onegin);
    fclose(checked_file_right_sorted_onegin);
}

void onegin_debug_print(Onegin_type* onegin) // (OK) For debug print only
{
    printf("buffer_of_chars: %p\n", onegin->buffer_of_chars);
    printf("strings: %p\n", onegin->strings);
    printf("current_line: %ld\n", onegin->current_line);
    printf("error_code: %ld\n", onegin->error_code);
    printf("number_of_lines: %ld\n\n", onegin->number_of_lines);

    for(size_t i = 0; i < onegin->number_of_lines; i++)
    {
        printf("Strings[%ld] = %p\n", i, onegin->strings[i]);
    }
}

void read_onegin_into_buf(FILE* checked_file_onegin, Onegin_type* onegin) // (OK) Reads onegin text into the buffer
{   
    rewind(checked_file_onegin); // Returns the pointer inside the file to the initial position
    onegin->size_of_onegin = fread(onegin->buffer_of_chars, sizeof(char), onegin->size_of_onegin, checked_file_onegin);
    rewind(checked_file_onegin); // Returns the pointer inside the file to the initial position
}

void create_array_strings(Onegin_type* onegin) // (OK) Creates the array of strings 
{
    onegin->strings = (char**)calloc(1, onegin->number_of_lines * sizeof(char*));   
}

char* get_string(Onegin_type* onegin) // (OK) Gets the pointer to the string
{
    char* string = nullptr;
    char* start_of_string = &(onegin->buffer_of_chars[onegin->position_of_line_in_buffer]); // Stores the old position of start 
    char* end_of_string = strchr_slash_n_my(onegin); // Stores position of the end of the string
    
    string = (char*)calloc(1, ((end_of_string - start_of_string) + 1) * sizeof(char)); 
    string = strncpy(string, start_of_string, (end_of_string - start_of_string) + 1); // Copies characters from the buffer to the allocated memory cell
    return string;
}

void fill_the_array (Onegin_type* onegin) // (OK) Fills the array with pointers to the string
{
    for(size_t i = 0; i < onegin->number_of_lines; i++)
    {
        onegin->strings[i] = get_string(onegin); // Gets the pointer to the next string form the buffer
    }
}

char* strchr_slash_n_my(Onegin_type* onegin) // (OK) Searches the end of the next line 
{    
    char* position = nullptr;

    while(onegin->position_of_line_in_buffer < onegin->size_of_onegin)     
    {
        if(onegin->buffer_of_chars[onegin->position_of_line_in_buffer] == '\n')
        {   
            position = &(onegin->buffer_of_chars[onegin->position_of_line_in_buffer]); // Makes the end of the previous line into start of the new one
            onegin->position_of_line_in_buffer++;
            return position;
        }
        else
        {
            onegin->position_of_line_in_buffer++;
        }
    }                                                                            
}

void print_strings_to_file(Onegin_type* onegin, FILE* check_sorted_file_for_openning) // (OK) Prints ALL ARRAY OF STRING into the file Onegin_sorted_-----.txt
{   
    for(size_t i = 0; i < onegin->number_of_lines; i++)
    {
        fputs_my(onegin->strings[i], check_sorted_file_for_openning);
    }
}

void fputs_my(char* string_to_fputs, FILE* check_sorted_file_for_openning) // (OK) Prints ONLY ONE STRING into the file Onegin_sorted_-----.txt
{   
    size_t length = strlen_slash_n_my(string_to_fputs);

    for(size_t i = 0; i < length; i++)
    {
        fputc(string_to_fputs[i], check_sorted_file_for_openning);
    }
}

size_t strlen_slash_n_my(char* str) // (OK) Returns the length of the string with \n and without \r
{
    size_t length = 0;

    while (str[length] != '\n')
    {
        length++;
    }

    return length;
}

int comparator_left_to_right(const void* string_a, const void* string_b) // (OK) Used in order to compare two strings (TI_THE_RIGHT_SORT)
{
    return strcmp_left_to_right(*(const char **)string_a, *(const char **)string_b);
}

int comparator_right_to_left(const void* string_a, const void* string_b) // (OK) Used in order to compare two strings (TO_THE_LEFT_SORT)
{
    return strcmp_right_to_left(*(const char **)string_a, *(const char **)string_b);
}

void sort_strings(Onegin_type* onegin, FILE* check_sorted_file_left_for_openning, FILE* check_sorted_file_right_for_openning) // (OK) Sorts the array of strings
{   
    qsort(onegin->strings, onegin->number_of_lines, sizeof(char*), comparator_left_to_right);
    print_strings_to_file(onegin, check_sorted_file_left_for_openning);

    qsort(onegin->strings, onegin->number_of_lines, sizeof(char*), comparator_right_to_left);
    print_strings_to_file(onegin, check_sorted_file_right_for_openning);  
}

int strcmp_right_to_left(const char* string_a, const char* string_b) // (OK) Sorts the onegin from the right to the left 
{   
    size_t length_string_a = strlen_slash_n_my((char*)string_a);
    size_t length_string_b = strlen_slash_n_my((char*)string_b);
    size_t length_string_a_no_spaces = strlen_slash_n_my_no_spaces((char*)string_a); 
    size_t length_string_b_no_spaces = strlen_slash_n_my_no_spaces((char*)string_b); 

    char* right_position_of_string_a = (char*)string_a + length_string_a;
    char* right_position_of_string_b = (char*)string_b + length_string_b;

    if((length_string_a_no_spaces == 0) && (length_string_b_no_spaces == 0))
    {
        return 0;
    }
    else if((length_string_a_no_spaces == 0) && (length_string_b_no_spaces != 0))
    {
        return 1;
    }
    else if((length_string_a_no_spaces != 0) && (length_string_b_no_spaces == 0))
    {
        return -1;
    }
    else
    {  
        while(((char*)string_a != right_position_of_string_a) || ((char*)string_b != right_position_of_string_b))
        {
            if((isalpha(right_position_of_string_a[0]) != 0) && (isalpha(right_position_of_string_b[0]) != 0))
            {
                if(tolower(right_position_of_string_a[0]) == tolower(right_position_of_string_b[0]))
                {
                    right_position_of_string_a--;
                    right_position_of_string_b--;
                } 
                else
                {
                    return (tolower(right_position_of_string_a[0]) - tolower(right_position_of_string_b[0]));
                }
            }
            else if((isalpha(right_position_of_string_a[0]) != 0) && (isalpha(right_position_of_string_b[0]) == 0))
            {   
                right_position_of_string_b--;
            }
            else if((isalpha(right_position_of_string_a[0]) == 0) && (isalpha(right_position_of_string_b[0]) != 0))
            {
                right_position_of_string_a--;
            }
            else
            {
                right_position_of_string_a--;
                right_position_of_string_b--;
            }
        }
    }
}

int strcmp_left_to_right(const char* string_a, const char* string_b) // (OK) Sorts the onegin from the left to the right 
{   
    size_t length_string_a = strlen_slash_n_my((char*)string_a);
    size_t length_string_b = strlen_slash_n_my((char*)string_b);
    size_t length_string_a_no_spaces = strlen_slash_n_my_no_spaces((char*)string_a);
    size_t length_string_b_no_spaces = strlen_slash_n_my_no_spaces((char*)string_b);

    char* right_position_of_string_a = (char*)string_a + length_string_a;
    char* right_position_of_string_b = (char*)string_b + length_string_b;

    if((length_string_a_no_spaces == 0) && (right_position_of_string_b == 0))
    {
        return 0;
    }
    else if((length_string_a_no_spaces == 0) && (right_position_of_string_b != 0))
    {
        return 1;
    }
    else if((length_string_a_no_spaces != 0) && (right_position_of_string_b == 0))
    {
        return -1;
    }
    else
    {   
        while((string_a != right_position_of_string_a) || (string_b != right_position_of_string_b))
        {   
            if((isalpha(string_a[0]) != 0) && (isalpha(string_b[0]) != 0))
            {
                if(tolower(string_a[0]) == tolower(string_b[0]))
                {
                    string_a++;
                    string_b++;
                } 
                else
                {
                    return (tolower(string_a[0]) - tolower(string_b[0]));
                }   
            }
            else if((isalpha(string_a[0]) != 0) && (isalpha(string_b[0]) == 0))
            {
                string_b++;
            }
            else if((isalpha(string_a[0]) == 0) && (isalpha(string_b[0]) != 0))
            {
                string_a++;
            }
            else
            {
                string_a++;
                string_b++;
            }
        }
    }   
}

size_t strlen_slash_n_my_no_spaces(char* str) // (OK) Returns the length of the string without \r, \n and spaces
{
    size_t i = 0;
    size_t count_chars = 0;
    while (str[i] != '\n')
    {
        if((isspace(str[i]) == 0) && (str[i] != '\r'))
        {
            count_chars++;
        }
        i++;
    }
    return count_chars;
}

 