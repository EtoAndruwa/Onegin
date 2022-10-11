#include <stdio.h>

int main()
    {

        int ch;// char

        FILE *fp_r;
        FILE *fp_w;

        if (fopen("Test_text_w.txt", "r") == 0)
            {
                printf("ERROR: unable to open file 1\n");
                return 1;
            }
        if (fopen("Test_text_w.txt", "r+") == 0)
            {
                printf("ERROR: unable to open file 2\n");
                return 1;
            }
        else
        {
            fp_r = fopen("Test_text_r.txt", "r");//opens file with text
            fp_w = fopen("Test_text_w.txt", "w");//opens empty file

            while((ch = getc(fp_r)) != EOF)//while reaches end of file
                {
                    putchar(ch);//prints one char
                    putc(ch, fp_w);//writes char into empty file
                }

            if (fclose(fp_r) != 0)
                printf("ERROR: unable to close file 1\n");

            if (fclose(fp_w) != 0)
                printf("ERROR: unable to close file 2\n");


            fp_w = fopen("Test_text_w.txt", "r+");//opens empty file
                printf("Text from empty file\n\n");

            while((ch = getc(fp_w)) != EOF)//while reaches end of file
                {
                    putchar(ch);//prints one char
                }


            if (fclose(fp_w) != 0)
                printf("ERROR: unable to close file 2\n");

            return 0;
        }
    }
