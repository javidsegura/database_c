 // AVOID DEFINING HEADER TWICE
#ifndef FUNCS_H
#define FUNCS_H

// Importing standard libraries' headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Importing user-defined headers 
#include "interface.h"
#include "add.h" // Used from main.c

// Defining macros
#define MAX_COLUMNS 100
#define MAX_ROWS 1000
#define MAX_STRING_LENGTH 100

//Functions prototypes from other headers 
void end_request(int mode);
void record_prior_next_read(int user_record, int direction);
void end_request_prior_record(int current_record_index);

//Function prototype from local functions
void headers_only_read();
void records_only_read(int mode, int upper_bound);



// ~ 0. SET UP
char path[256] = "/Users/javierdominguezsegura/Programming/No Python/C/Programming principles/Database Management System/data/MUSIC - DATASET.csv";


// ~ 1. DATABASE STRUCTURE
typedef struct {

    // Dimensions
    int num_columns; 
    int num_records;

    // Headers
    char column_names[MAX_COLUMNS][MAX_STRING_LENGTH]; 

    // Records
    char records[MAX_ROWS][MAX_COLUMNS][MAX_STRING_LENGTH];

} Database;

Database db;



// ~ 2. LOADING DATABASE
void load_csv(char* path) { 

    /*
    
    Description: this function reads a CSV file and stores its content in a database structure.
    Paramters: 
        - path: path to CSV file.
    
    */

    FILE* fp = fopen(path, "r");

    if (fp == NULL) {
        printf("Error opening file. Please make sure the link is correct.\n");
        return;
    }

    // Read header row
    char header[MAX_STRING_LENGTH];
    fgets(header, MAX_STRING_LENGTH, fp); 
    char* token = strtok(header, ","); // Separate the stored str of the header with comman as a divider

    // Create columns from the tokens of the header
    db.num_columns = 0;
    while (token != NULL) {
        strncpy(db.column_names[db.num_columns], token, MAX_STRING_LENGTH - 1); 
        db.num_columns++;
        token = strtok(NULL, ",");
    }

    // Read data rows
    db.num_records = 0;
    while (fgets(header, MAX_STRING_LENGTH, fp) != NULL) {

        token = strtok(header, ",");
        for (int i = 0; i < db.num_columns; i++) {
            strncpy(db.records[db.num_records][i], token, MAX_STRING_LENGTH - 1); 
            token = strtok(NULL, ","); // Move to the next token
        }

        db.num_records++;
    }
    fclose(fp);
}



void headers_only_read(){

    /*
    
    Description: the purpose of this function is to avoid redundancy for the common task to print the header of the database
    
    */

    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    for (int i = 0; i < db.num_columns; i++) {
        if (i == 0){
            printf("    %s", db.column_names[i]);
        }
        else{
        printf("%s", db.column_names[i]);
        }
        if (i < db.num_columns - 1) { 
            printf(" , ");
        }
    }
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
}



void records_only_read(int mode, int upper_bound){

    /*
    
    Description: the purpose of this function is to avoid redundancy for the common task to print the records of the database. It adapts to the different approaches taken toward printing the database.
    Parameters:
        - mode: distinguish between fixed and non-fixed record iteration
           - 1: non-fixed record iteration
           - 2: fixed record iteration
    
    */

   if (mode == 1){
    for (int i = 0; i < upper_bound; i++) {
            printf("\n");
            for (int j = 0; j < db.num_columns; j++) {
                if (j == 0){
                    printf("|%d| %s",i, db.records[i][j]);
                }
                else{
                printf("%s", db.records[i][j]);
                }

                if (j < db.num_columns - 1) {
                    printf(", ");
                }
            
            }
        }

   }
   else if (mode == 2){
        for (int i = 0; i < db.num_columns; i++){
        if (i == 0){
            printf("\t|%d| %s",upper_bound, db.records[upper_bound][i]);
        }
        else{
        printf("%s", db.records[upper_bound][i]);
        }
        if (i < db.num_columns - 1) {
                printf(", ");
            }
    }
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
   }
}



// ~ 3. READING DATABASE
void complete_db_read() { 

    /*

    Description: this function reads the entire database and prints it to the console.

    */

    ui_header_element(); // import UI component

    // Header     
    printf("\n\n\n DATABASE DATA:");
    headers_only_read();

    // Records
    records_only_read(1, db.num_records);
    
    printf("\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -");
    printf("\n\nTotal records in the database: %d\n", db.num_records);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ");

    end_request(1);
}



void partial_db_read(int mode) { 

    /*

    Description: this function reads the entire database and prints it to the console.
    Parameters: 
        - mode: used to distinguish between parts of the code that have a large amount of similar code with slight variations
            - 1: show first five records
            - 2: show complete database

    */

    // Header 
    printf("\n\n\n DATABASE DATA (REDUCED):");
    headers_only_read();

    // Records
    records_only_read(1, 5);


    if (mode == 1){
    printf("\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -");
    printf("\n\nTotal records: %d\n", 5);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n");
    end_request(2);

    }
    else if (mode == 2){
        printf("\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -");
        printf("\n\nTotal records in the database: %d\n", db.num_records - 1);
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");

    }
    else{
        printf("You have selected a mode that does not exist.");
        sleep(2);
       
    }
}



// ~ 4. READ SUBSCRIPTING (ROWS AND COLUMNS)
void subscripts_record_read(){

    /*
    
    Description: this function reads a record for a selected index 
    
    */

    ui_header_element();

    unsigned int user_decision_index; // We only expect positive indeces

    partial_db_read(2); // Display compacted data to assist selecting an index

    printf("\n\n\n(*) Provide index of record: \n");
    printf("==> ");
    scanf("%d", &user_decision_index);

    if (user_decision_index > db.num_records - 1 || user_decision_index < 0){
        ui_header_element();

        printf("\n\nERROR: You have selected an empty record. Please try again.\n");
        fflush(stdout); // Flush the output buffer of the stdout to allow display the error message before 'sleeping' execution
        sleep(2);

        subscripts_record_read();
    }
    else
    {

    ui_header_element();

    printf("\n\n\n DATABASE DATA (record: %d):", user_decision_index);
    headers_only_read();

    // Records
    records_only_read(2,user_decision_index);
    }

    // Call specific function to handle end of page
    end_request_prior_record(user_decision_index);
}



void record_prior_next_read(int current_record, int direction){

    /*
    
    Description: this functions is called after subscripting a record. It allows to navigate to the prior or coming record.
    Parameters:
        - current_record: current position within the spreadsheet
        - direction: backwards (-1) or forward (+1)
    
    */

    
    unsigned int adjusted_record = current_record + direction;

    if (adjusted_record > db.num_records - 1 || adjusted_record < 0){  // XXX => IS NOT WORKING
        ui_header_element();
        printf("\nERROR: You have selected an empty record. Please try again.\n\n\n");
        fflush(stdout);
        sleep(2);
        subscripts_record_read();
    }
    else
    {

    ui_header_element();

    // Headers
    printf("\n\n\n DATABASE DATA (record: %d):", adjusted_record);
    headers_only_read();

    // Records
    records_only_read(2, adjusted_record);
    }

    end_request_prior_record(adjusted_record);
    //Code developed by Javi DS and Anze Zgnoc
}



void subscripts_column_read(){

    /*
     
    Description: this functions prints a column for a selected index within all the options
    
    */

    ui_header_element();

    unsigned int user_decision_col; 

    // Headers
    printf("\n\nDATABASE HEADER: ");
    headers_only_read();

    printf("\n\n(*) Select index of column:\n ");
    printf("==> ");
    scanf("%d", &user_decision_col);

    if (user_decision_col > db.num_columns - 1){
        system("clear");
        printf("ERROR: You have selected a column that does not exist. Please try again.\n\n");
        fflush(stdout);
        sleep(2);
        subscripts_column_read();
    }
    else{

    ui_header_element();

    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - -  \n");
    printf("\t   %s", db.column_names[user_decision_col]); 
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - -  \n");

    // Record 
    for (int i = 0; i < db.num_records; i++){
        printf("\n\t|%d| %s\n", i,db.records[i][user_decision_col]);
    }
    }

    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ");
    printf("\n\nTotal records: %d\n", db.num_records);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ");

    end_request(0);
}



#endif