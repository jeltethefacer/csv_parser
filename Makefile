CC = gcc

make: csv_parser.c
	${CC} csv_parser.c -o csv_parcer