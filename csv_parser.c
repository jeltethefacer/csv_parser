#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "csv_parser.h"

int read_first_column(char *file_name, column *column_to_read_into)
{
    FILE *f = fopen(file_name, "r");

    column_to_read_into->name = read_next_value(f);
    skip_to_next_line(f);
    char c;
    int n = 0;
    while ((c = getc(f)) != EOF)
    {
        column_to_read_into->values[n] = read_next_value(f);
        skip_to_next_line(f);
        n++;
    }

    fclose(f);
    return 0;
}

int parse_csv_file(char *file_name, csv_parser *parser)
{
    //inits the csvParser
    int column_amount = get_column_amount(file_name);

    parser->columns = malloc(column_amount * sizeof(column *));
    int row_amount = get_row_amount(file_name);

    FILE *f = fopen(file_name, "r");

    //first read all the names in the columns
    column *column_pointer = malloc(sizeof(column));
    column_pointer->name = read_next_value(f);

    column_pointer->values = malloc(row_amount * sizeof(char *));
    parser->columns[0] = column_pointer;
    parser->column_amount = 1;

    char c = getc(f);
    while (c != '\n' && c != EOF && parser->column_amount < column_amount)
    {
        column_pointer = malloc(sizeof(column));
        column_pointer->name = read_next_value(f);
        column_pointer->values = malloc(row_amount * sizeof(char *));
        parser->columns[parser->column_amount] = column_pointer;
        parser->column_amount++;
        c = getc(f);
    }

    parser->row_amount = 0;
    while (c != EOF && parser->row_amount < row_amount)
    {
        for (long x = 0; x < parser->column_amount; x++)
        {
            parser->columns[x]->values[parser->row_amount] = read_next_value(f);
            c = getc(f);
        }
        parser->row_amount++;
    }

    // skip_to_next_line(f);
    // char c;
    // int n = 0;
    // while ((c = getc(f)) != EOF)
    // {
    //     column_to_read_into->values[n] = read_next_value(f);
    //     skip_to_next_line(f);
    //     n++;
    // }

    fclose(f);
    return 0;
}

//skips to next newling or eof
//NOTE: keeps the last charcter it read in stream
int skip_to_next_line(FILE *f)
{
    char c = getc(f);
    while (c != '\n' && c != EOF)
    {
        c = getc(f);
    }
    ungetc(c, f);
    return 0;
}

//NOTE: keeps the last charcter it read in stream
char *read_next_value(FILE *f)
{
    int counter = 0;
    char *temp_value = calloc(MAX_COLUMN_NAME_LENGTH, sizeof(char));
    char c = getc(f);
    //gets column name
    //TODO MAKE FUNCTION??
    while (c != ',' && c != '\n' && c != EOF)
    {
        temp_value[counter] = c;
        counter++;
        if (counter >= MAX_COLUMN_NAME_LENGTH)
        {
            fprintf(stderr, "EXEEDED MAX COLUMN NAME LENGTH");
            //TODO should make this better and return -1 or prints warning and skips to next , or \n;
            break;
        }
        c = getc(f);
    }
    ungetc(c, f);

    char *trimmed_value = trim(temp_value);
    free(temp_value);
    return trimmed_value;
}

char *trim(char *string)
{
    int len = strlen(string);
    int start = 0, end = len;

    for (int x = 0; x < len; x++)
    {
        if (!isspace(string[x]))
        {
            start = x;
            break;
        }
    }

    //NOTE" len-1 to skip the string terminator
    for (int x = len - 1; x >= start; x--)
    {

        if (!isspace(string[x]))
        {
            end = x;
            break;
        }
    }
    // printf("start: %d, end: %d \n", start, end);
    return slice_string(string, start, end);
}

char *slice_string(char *string, int start, int end)
{
    int len = end - start;
    len++;
    char *temp_pointer = malloc(sizeof(char) * len);
    for (int x = 0; x < len; x++)
    {
        temp_pointer[x] = string[start + x];
    }
    // temp_pointer[len] = '\0';
    return temp_pointer;
}

int get_column_amount(char *file_name)
{
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
    {
        return -1;
    }
    int n = 0;

    char c = getc(f);
    while (c != '\n' && c != EOF)
    {
        read_next_value(f);
        c = getc(f);
        n++;
    }

    return n;
}

//NOTE: The last row not end with a \n
long get_row_amount(char *file_name)
{
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
    {
        return -1;
    }

    long n = 0;

    char c = getc(f);
    while (c != EOF)
    {
        if (c == '\n')
        {
            n++;
        }
        c = getc(f);
    }

    return n;
}

int main()
{
    csv_parser *test_file = malloc(sizeof(csv_parser));
    

    parse_csv_file("yvonne.csv", test_file);

    // for (long x = 0; x < test_file->column_amount; x++)
    // {
    //     printf("%20s", test_file->columns[x]->name);
    // }
    // printf("\n");
    // printf("%ld\n", test_file->row_amount);
    // for (long x = 0; x < test_file->row_amount; x++)
    // {
    //     for (long y = 0; y < test_file->column_amount; y++)
    //     {
    //         printf("%20s", test_file->columns[y]->values[x]);
    //     }
    //     printf("\n");
    // }
}