#ifndef FUNCS_H
#define FUNCS_H

// Importing standard libraries' headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Importing user-defined headers (homepage and add)
#include "add.h"


// Macros to define the maximum number of columns, rows and string length
#define MAX_COLUMNS 100
#define MAX_ROWS 1000
#define MAX_STRING_LENGTH 100

// 0. SET UP
char path[] = "/Users/javierdominguezsegura/Programming/No Python/C/Programming principles/Database Management System/data/MUSIC - DATASET - Sheet1 (1) (1).csv";


// 1. DATABASE STRUCTURE
typedef struct {

    // Dimensions
    int num_columns; 
    int num_rows;

    // Headers
    char column_names[MAX_COLUMNS][MAX_STRING_LENGTH]; 

    // Records
    char data[MAX_ROWS][MAX_COLUMNS][MAX_STRING_LENGTH];

} Database;


Database db;


// 2. LOADING DATABASE
void load_csv(char* path) { 

    /*
    
    Description: this function reads a CSV file and stores its content in a database structure.
    Paramters: 
        - path: the path to the CSV file.
    
    
    */

    FILE* fp = fopen(path, "r");

    if (fp == NULL) {
        printf("Error opening file. Please make sure the link is correct.\n");
        return;
    }

    // Read header row
    char header[MAX_STRING_LENGTH];
    fgets(header, MAX_STRING_LENGTH, fp); // Read the first line of the file and store it in the header variable (prints a string of the first (header) row)
    char* token = strtok(header, ","); // Separate the stored str of the header with comman as a separator

    // Create columns from the tokens of the header
    db.num_columns = 0;
    while (token != NULL) {
        strncpy(db.column_names[db.num_columns], token, MAX_STRING_LENGTH - 1); 
        db.num_columns++;
        token = strtok(NULL, ",");
    }

    // Read data rows
    db.num_rows = 0;
    while (fgets(header, MAX_STRING_LENGTH, fp) != NULL) {

        token = strtok(header, ",");
        for (int i = 0; i < db.num_columns; i++) {
            strncpy(db.data[db.num_rows][i], token, MAX_STRING_LENGTH - 1); // First dimension is row, second dimension is column
            token = strtok(NULL, ","); // Move to the next token
        }

        db.num_rows++;
    }

    fclose(fp);
}


// 3. READING DATABASE

void complete_db_read() { // FINISHED


    /*

    Description: this function reads the entire database and prints it to the console.

    */

    system("clear");

    load_csv(path);      

    // Header 
    printf("----------------\n");
    for (int i = 0; i < db.num_columns; i++) {
        printf("%s", db.column_names[i]);
        if (i < db.num_columns - 1) { // Print a comma separator if it is not the last element in the row
            printf(" , ");
        }
    }
    printf("---------------\n\n");

    // Records
    for (int i = 0; i < db.num_rows; i++) {
        for (int j = 0; j < db.num_columns; j++) {
            printf("%s", db.data[i][j]);
            if (j < db.num_columns - 1) {
                printf(",");
            }
        }
    }

    printf("\nTotal records: %d\n", db.num_rows);
    printf(" - ");
}



#endif