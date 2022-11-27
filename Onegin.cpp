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
        get_num_of_chars_in_file(checked_file_onegin);
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

// void create_buffer_for_chars(FILE* checked_file_onegin, Onegin_type* onegin_file_struct)
// {
    
// }



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

size_t get_num_of_chars_in_file(FILE* checked_file_onegin)
{   
    size_t number_of_chars = 0;

    fseek(checked_file_onegin, 0, SEEK_END); // puts pointer to the end of file 
    size_t onegin_length = ftell(checked_file_onegin); // returns total number of bytes (1 char = 1 byte) ->number of chars WITH \R!!!!!!!!!!
    printf("Length onegin = %ld\n", onegin_length);

    return number_of_chars;
}

// void onegin_dtor()
// {




// }


// void onegin_logic()
// {

// }

// void onegin_print()
// {


// }


