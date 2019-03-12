//author: Jelte Boelens
//date: 10-02-2019
#define MAX_COLUMN_NAME_LENGTH 100
#define MAX_ROWS 1500000
#define MAX_COLUMNS 14

typedef struct column
{
    char* name;
    char** values;
} column;

typedef struct csv_parser
{
    column** columns;
    long column_amount;
    long row_amount;
} csv_parser;


int read_first_column(char *, column*);
int skip_to_next_line(FILE*);
char* read_next_value(FILE *);
int parse_csv_file(char*, csv_parser*);
char* trim(char*);
char* slice_string(char*, int, int);
int get_column_amount(char *);
long get_row_amount(char *);