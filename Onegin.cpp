#include "onegin.h"

#define FUNC_NAME __func__
#define FUNC_LINE __LINE__ 

// int count_num_of_lines(FILE* file_with_onegin)
// {
//     int ch = 0;
//     int number_of_lines = 0;
//     while((ch = getc(fp_r)) != EOF)

//     if (ch == '\n')
//     {
//         number_of_lines++;
//     }
//     number_of_lines++;
//     printf("Number of lines = %d", number_of_lines);
//     return 0;
// }

FILE* check_onegin_for_openning() // checks the file with Onegin text for openning 
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
        printf("File Onegin was openned\n");
        return checked_file_onegin;
    }
}
 
FILE* check_sorted_file_for_openning() // checks the file with sorted Onegin text for openning 
{   
    FILE * checked_file_sorted_onegin = fopen("Sorted_Onegin_text.txt", "wb"); 
    if(checked_file_sorted_onegin == nullptr)
    {
        printf("ERROR: File with sorted Onegin text cannot be openned. Please, check file with sorted Onegin text.\n");
    }
    else
    {
        printf("File sorted Onegin was openned\n");
        return checked_file_sorted_onegin;
    }
}

void create_buffer_for_chars(size_t size_of_onegin, Onegin_type* onegin)
{
    onegin->buffer_of_chars = (char*)calloc(1, size_of_onegin * sizeof(char));
    printf("Onegin buffer address: %p\n\n", onegin->buffer_of_chars);
    // free(onegin->buffer_of_chars); //DELETE THIS
}



// void onegin_logic()
// {   

// }

// int count_num_of_strings(FILE * )
// {

// }

// void add_slash_n_to_string()
// {

// }


const char* enum_to_string(size_t code) // converts an enum's int value to the enum's string value
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
        // case 6:
        //     return "";
        //     break;
        default:
            return "STACK IS OK"; 
            break;
    }
}


void onegin_dump(Onegin_type* onegin, const char* FUNCTION_NAME, size_t FUNCTION_LINE) // OK
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

size_t get_num_of_chars_in_file(FILE* checked_file_onegin) // returns the sizeof(number of chars) onegin
{   
    fseek(checked_file_onegin, 0, SEEK_END); // puts pointer to the end of file 
    size_t size_of_onegin = ftell(checked_file_onegin); // returns total number of bytes (1 char = 1 byte) ->number of chars WITH \R!!!!!!!!!!
    printf("Length onegin = %ld\n", size_of_onegin);

    return size_of_onegin;
}

void onegin_dtor(Onegin_type* onegin, FILE* checked_file_onegin, FILE* checked_file_sorted_onegin)
{
    free(onegin->buffer_of_chars); // frees the buffer of chars
    // for(size_t num_of_line = 0; num_of_line < onegin->number_of_lines; num_of_line++) // frees every line in the array of strings
    // {
    //     free(onegin->strings[num_of_line]);
    //     onegin->strings[num_of_line] = nullptr;
    // }
    free(onegin->strings); // frees the pointer to the array of strings

    onegin->buffer_of_chars = nullptr;
    onegin->strings = nullptr;

    onegin->current_line = 0;
    onegin->error_code = 0;
    onegin->number_of_lines = 0;

    fclose(checked_file_onegin);
    fclose(checked_file_sorted_onegin);
}


// void onegin_logic()
// {

// }

void onegin_debug_print(Onegin_type* onegin) // for debug only
{
    printf("buffer_of_chars: %p\n", onegin->buffer_of_chars);
    printf("strings: %p\n", onegin->strings);
    printf("current_line: %ld\n", onegin->current_line);
    printf("error_code: %ld\n", onegin->error_code);
    printf("number_of_lines: %ld\n\n", onegin->number_of_lines);

}


