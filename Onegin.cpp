#include "onegin.h"

#define FUNC_NAME __func__
#define FUNC_LINE __LINE__ 

size_t count_num_of_lines_in_buf(Onegin_type* onegin) // OK
{
    size_t number_of_lines = 0;

    for(size_t i = 0; i < onegin->size_of_onegin; i++)
    {   
        if(onegin->buffer_of_chars[i] == '\n')
        {   
            number_of_lines++;
            //printf("onegin->buffer_of_chars[%ld] line %ld\n", i, number_of_lines);
        }
        if((onegin->buffer_of_chars[i] != '\n') && (i == (onegin->size_of_onegin - 1)))
        {
            onegin->buffer_of_chars[onegin->size_of_onegin] = '\n';
            onegin->size_of_onegin++;
            number_of_lines++;
            //printf("onegin->buffer_of_chars[%ld] line %ld\n", (i + 1), number_of_lines);
            break;
        }
    }
    onegin->number_of_lines = number_of_lines;
    //printf("Number of lines = %ld\n\n", onegin->number_of_lines);
    return 0;
}

FILE* check_onegin_for_openning() // OK checks the file with Onegin text for openning 
{
    FILE* checked_file_onegin = fopen("Onegin_text.txt", "rb");//opens for reading
    if(checked_file_onegin == nullptr)
    {   
        // onegin->error_code = 1;
        // onegin_dump(onegin, FUNCTION_NAME, FUNCTION_LINE);
        // onegin_dtor(onegin,);
        abort(); // DELETE THIS
        printf("ERROR: File with Onegin text cannot be openned. Please, check file with Onegin text.\n");
    }
    else
    {
        //printf("File Onegin was openned\n");
        return checked_file_onegin;
    }
}
 
FILE* check_sorted_left_file_for_openning() // OK checks the file with sorted Onegin text for openning 
{   
    FILE * checked_left_file_sorted_onegin = fopen("Sorted_Left_Onegin_text.txt", "wb"); 
    if(checked_left_file_sorted_onegin == nullptr)
    {
        printf("ERROR: File with sorted Onegin left text cannot be openned. Please, check file with sorted Onegin text.\n");
    }
    else
    {
        //printf("File sorted Onegin was openned\n");
        return checked_left_file_sorted_onegin;
    }
}

FILE* check_sorted_right_file_for_openning() // OK checks the file with sorted Onegin text for openning 
{   
    FILE * checked_right_file_sorted_onegin = fopen("Sorted_Right_Onegin_text.txt", "wb"); 
    if(checked_right_file_sorted_onegin == nullptr)
    {
        printf("ERROR: File with sorted Onegin right text cannot be openned. Please, check file with sorted Onegin text.\n");
    }
    else
    {
        //printf("File sorted Onegin was openned\n");
        return checked_right_file_sorted_onegin;
    }
}

void create_buffer_for_chars(Onegin_type* onegin) // OK allocates memory for buffer of chars
{
    onegin->buffer_of_chars = (char*)calloc(1, onegin->size_of_onegin * sizeof(char));
    //printf("Onegin buffer address: %p\n\n", onegin->buffer_of_chars);
}

const char* enum_to_string(size_t code) // OK converts an enum's int value to the enum's string value 
{
    switch(code)
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
        case 6:
            return "";
            break;
        default:
            return "STACK IS OK"; 
            break;
    }
}

void onegin_dump(Onegin_type* onegin, const char* FUNCTION_NAME, size_t FUNCTION_LINE) // CHECK
{
    FILE* logfile = fopen("LOG.txt", "a+");

    fprintf(logfile, "-------------------START OF LOG------------------------\n\n");
    fprintf(logfile, "Error code = %ld\n", onegin->error_code);
    fprintf(logfile, "Called from file: %s\n", __FILE__);
    fprintf(logfile, "Called error function name: %s\n", FUNC_NAME);
    fprintf(logfile, "Called from line: %d\n", FUNC_LINE);    
    fprintf(logfile, "Date when was called: %s\n", __DATE__);
    fprintf(logfile, "Time when was called: %s\n\n", __TIME__);

    fprintf(logfile, "Pointer to the array: %p\n", onegin->strings);
    fprintf(logfile, "Pointer to the buffer of chars: %p\n", onegin->buffer_of_chars);
    fprintf(logfile, "Current line: %ld\n", onegin->current_line);
    fprintf(logfile, "Total numver of lines: %ld\n", onegin->number_of_lines);
    fprintf(logfile, "--------------------END OF LOG--------------------------\n\n");

    fclose(logfile);
}

void get_num_of_chars_in_file(FILE* checked_file_onegin, Onegin_type* onegin) // OK returns the sizeof(number of chars) onegin 
{   
    rewind(checked_file_onegin);

    fseek(checked_file_onegin, 0, SEEK_END); // puts pointer to the end of file 
    onegin->size_of_onegin = ftell(checked_file_onegin); // returns total number of bytes (1 char = 1 byte) ->number of chars WITH \R!!!!!!!!!!

    rewind(checked_file_onegin);
    //printf("Length onegin = %ld\n", onegin->size_of_onegin);
}

void onegin_dtor(Onegin_type* onegin, FILE* checked_file_onegin, FILE* checked_file_left_sorted_onegin, FILE* checked_file_right_sorted_onegin) // frees all pointers and deletes 
{                                                                                                  // all data about onegin struct
    free(onegin->buffer_of_chars); // frees the buffer of chars
    for(size_t i = 0; i < onegin->number_of_lines; i++) // frees every line in the array of strings
    {
        free(onegin->strings[i]);
        onegin->strings[i] = nullptr;
    }
    free(onegin->strings); // frees the pointer to the array of strings

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

void onegin_debug_print(Onegin_type* onegin) // for debug only
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

void read_onegin_into_buf(FILE* checked_file_onegin, Onegin_type* onegin)
{   
    rewind(checked_file_onegin);

    //printf("Buf address: %p\n", onegin->buffer_of_chars);
    //printf("Onegin size: %ld\n", onegin->size_of_onegin);
    onegin->size_of_onegin = fread(onegin->buffer_of_chars, sizeof(char), onegin->size_of_onegin, checked_file_onegin);

    rewind(checked_file_onegin);
    //printf("Returned value of fread: %ld\n\n", onegin->size_of_onegin);
}

// void onegin_struct_check(Onegin_type* onegin, const char * FUNCTION_NAME, size_t FUNCTION_LINE)
// {
//     if(onegin->buffer_of_chars == nullptr)
//     {
//         onegin->error_code = ERR_NULLPTR_BUFFER;
//         onegin_dump(onegin, FUNCTION_NAME, FUNCTION_LINE);
//         onegin_dtor(onegin, checked_file_onegin, checked_file_sorted_onegin);
//         abort();
//     }
//     else if(onegin->strings == nullptr)
//     {
//         onegin->error_code = ERR_NULLPTR_STRINGS;
//         onegin_dump(onegin, FUNCTION_NAME, FUNCTION_LINE);
//         onegin_dtor(onegin, checked_file_onegin, checked_file_sorted_onegin);
//         abort();
//     }
//     else if(onegin->current_line < 0)
//     {
//         onegin->error_code = ERR_NEGATIVE_CUR_LINE;
//         onegin_dump(onegin, FUNCTION_NAME, FUNCTION_LINE);
//         onegin_dtor(onegin, checked_file_onegin, checked_file_sorted_onegin);
//         abort();
//     }
//     else if(onegin->number_of_lines < 0)
//     {
//         onegin->error_code = ERR_NEGATIVE_NUM_LINES;
//         onegin_dump(onegin, FUNCTION_NAME, FUNCTION_LINE);
//         onegin_dtor(onegin, checked_file_onegin, checked_file_sorted_onegin);
//         abort();
//     }
//     else if(onegin->size_of_onegin == 0)
//     {   
//         onegin->error_code = ERR_EMPTY_FILE_ONEGIN_TEXT;
//         onegin_dump(onegin, FUNCTION_NAME, FUNCTION_LINE);
//         onegin_dtor(onegin, checked_file_onegin, checked_file_sorted_onegin);
//         abort();
//     }
//     else if()
//     {
//         onegin_dump(onegin, FUNCTION_NAME, FUNCTION_LINE);
//         onegin_dtor(onegin, checked_file_onegin, checked_file_sorted_onegin);
//         abort();
//     }
//     else if()
//     {
//         onegin_dump(onegin, FUNCTION_NAME, FUNCTION_LINE);
//         onegin_dtor(onegin, checked_file_onegin, checked_file_sorted_onegin);
//         abort();
//     }
//     else if()
//     {
//         onegin_dump(onegin, FUNCTION_NAME, FUNCTION_LINE);
//         onegin_dtor(onegin, checked_file_onegin, checked_file_sorted_onegin);
//         abort();
//     }

void create_array_strings(Onegin_type* onegin)
{
    onegin->strings = (char**)calloc(1, onegin->number_of_lines * sizeof(char*));   
    //printf("Address of array of pointer to strings: %p\n", onegin->strings);
}

char* get_string(Onegin_type* onegin) // gets pointer to the string
{
    char* string = nullptr;

    char* start_of_string = &(onegin->buffer_of_chars[onegin->position_of_line_in_buffer]); // stores old position of start
    char* end_of_string = strchr_slash_n_my(onegin); // stores position of the end of the string

    // if(check_for_spaces == 0)
    // {
    //     printf("Start of new line %ld, Start %p, End %p, length %ld\n", onegin->position_of_line_in_buffer, start_of_string,end_of_string, (end_of_string - start_of_string)+1);
    //     string = (char*)calloc(1, ((end_of_string - start_of_string) + 1) * sizeof(char)); 
    //     string = strncpy(string, start_of_string, (end_of_string - start_of_string) + 1); // copies characters from the buffer to the allocated memory cell
    //     return string;
    // }
    // else
    // {
    //     onegin->position_of_line_in_buffer = onegin->position_of_line_in_buffer + (end_of_string - start_of_string);
    //     return string;
    // }

    //printf("Start of new line %ld, Start %p, End %p, length %ld\n", onegin->position_of_line_in_buffer, start_of_string,end_of_string, (end_of_string - start_of_string)+1);
    string = (char*)calloc(1, ((end_of_string - start_of_string) + 1) * sizeof(char)); 
    string = strncpy(string, start_of_string, (end_of_string - start_of_string) + 1); // copies characters from the buffer to the allocated memory cell
    return string;
}

void fill_the_array (Onegin_type* onegin) // fills the array with pointers to the string
{
    for(size_t i = 0; i < onegin->number_of_lines; i++)
    {
        onegin->strings[i] = get_string(onegin); // gets pointer to the next string form the buffer
    }
}

char* strchr_slash_n_my(Onegin_type* onegin)  // modified to search the character from specified position
{    
    char* position = nullptr;
    while(onegin->position_of_line_in_buffer < onegin->size_of_onegin)     
    {
        if(onegin->buffer_of_chars[onegin->position_of_line_in_buffer] == '\n')
        {   
            position = &(onegin->buffer_of_chars[onegin->position_of_line_in_buffer]);
            onegin->position_of_line_in_buffer++;
            return position;
        }
        else
        {
            onegin->position_of_line_in_buffer++;
        }
    }                                                                            
}

void print_strings_to_file(Onegin_type* onegin, FILE* check_sorted_file_for_openning) // prints all array of strings into the file Sorted_Onegin_text.txt
{   
    for(size_t i = 0; i < onegin->number_of_lines; i++)
    {
        fputs_my(onegin->strings[i], check_sorted_file_for_openning);
    }
}

void fputs_my(char* string_to_fputs, FILE* check_sorted_file_for_openning) // prints string into the file Sorted_Onegin_text.txt
{   
    //printf("%p", string_to_fputs);
    size_t length = strlen_slash_n_my(string_to_fputs);
    //printf("%ld\n", length);
    for(size_t i = 0; i < length; i++)
    {
        fputc(string_to_fputs[i], check_sorted_file_for_openning);
    }
}

size_t strlen_slash_n_my(char* str) // returns the length of the string
{
    size_t i = 0;
    while (str[i] != '\n')
    {
        i++;
    }
    return i;
}

int comparator_left_to_right(const void* string_a, const void* string_b) // used in order to compare two strings
{
    return strcmp(*(const char **)string_a, *(const char **)string_b);
}

void sort_strings(Onegin_type* onegin, FILE* check_sorted_file_left_for_openning, FILE* check_sorted_file_right_for_openning) // sorts array of strings
{   
    qsort(onegin->strings, onegin->number_of_lines, sizeof(char*), comparator_left_to_right);
    print_strings_to_file(onegin, check_sorted_file_left_for_openning);
    qsort(onegin->strings, onegin->number_of_lines, sizeof(char*), comparator_right_to_left);
    print_strings_to_file(onegin, check_sorted_file_right_for_openning);  
}

// int check_for_spaces(char* start_of_string, char* end_of_string) // checks for empty strings
// {
//     int flag = 0;
//     size_t i = 0;
//     while(i < end_of_string - start_of_string)
//     {
//         if(isspace((int)start_of_string[i]))
//         {
//             flag = 1;
//         }
//         else
//         {
//             flag = 0;
//             break;
//         }
//         i++;
//     }
//     return flag;
// }

int comparator_right_to_left(const void* string_a, const void* string_b) // used in order to compare two strings
{   
    size_t length_string_a = strlen_slash_n_my(*(char**)string_a);
    size_t length_string_b = strlen_slash_n_my(*(char**)string_b);

    char* right_position_of_string_a = *(char**)string_a + length_string_a;
    char* right_position_of_string_b = *(char**)string_b + length_string_b;

    while((*(char**)string_a != right_position_of_string_a) || (*(char**)string_b != right_position_of_string_b))
    {
        if(right_position_of_string_a[0] == right_position_of_string_b[0])
        {
            right_position_of_string_a--;
            right_position_of_string_b--;
        } 
        else
        {
            return (right_position_of_string_a[0]-right_position_of_string_b[0]);
        }
    }
}

 