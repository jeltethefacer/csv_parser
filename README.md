A simple csv parser which you can use in your projects.

To parse a csv file you can use the function 
```
int parse_csv_file(char*, csv_parser*);
```
supplied with the file_name and a pointer to a csv parser object.
he reads the csv file into the csv_parser object it automaticly detects the needed file size 
it strips of the whitespaces on each side of the column value

It parser a csv file with 1500000 rows in about 3 second on a i5

The last row of the csv should not end with a \n

# Featerus to add:
* Option to supply the amount of rows you want
* Make it more user friendly (examples, documented)
* write to a file
* Makes it so it doesn't need to omit the \n on the last row


