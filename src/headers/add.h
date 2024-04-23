// AVOID DEFINING HEADER TWICE
#ifndef ADD_H
#define ADD_H

// Importing standard libraries' headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Importing user-defined headers 
#include "funcs.h"
#include "interface.h"

// ~ 0. DATABASE STRUCTURE
typedef struct {

      char title[99];
      char author[99];
      char duration[99];
      char genre[99];
      int year;
      long int views;

} records;

//Functions prototypes from other headers 
void ui_header_element();

//Function prototype from local functions
void user_decision_add(records *new_record);
void save_csv_add(records *new_record);
void create_instance_add();
void confirm_update_add(records *new_record);


// Acccess to the path of the csv
extern char path[256];



// ~ 1. START ADDING MODE
void record_add(){

      /*
      
      Definition: this function creates a new record and adds it to the database. It only calls functions as it needs to rely on independet calls to properly aggreagate the data (to create a 'records' instance at every call)
      
      */

    create_instance_add();
}

// ~ 2. CREATE AN INSTANCE OF THE FIELDS' STRUCUTRE
void create_instance_add(){

      /*
      
      Description: this function needs to independently instantiate the structure so that it does not collide when several records are added.
      
      */

      records db;

      user_decision_add(&db);
}

// ~ 3. AGGREGATE DATA TO THE INSTANTIATED STRUCTURE
void user_decision_add(records *new_record){

      /*
      
      Definition: this function prompts the user to input the data for a new record.
      It then calls the function 'save_csv_add' to add the new record to the database.
      
      */

      ui_header_element();

      char buffer[256];

      printf("\n\n\nTitle {str}: ");
      scanf(" %[^\n]", buffer);  // Reads entire line until newline is encountered - (REGEX)
      strcpy(new_record->title, buffer);

      printf("Author {str}: ");
      scanf(" %[^\n]", buffer);
      strcpy(new_record->author, buffer);

      printf("Duration {str} (MM:SS): ");
      scanf(" %[^\n]", buffer);
      strcpy(new_record->duration, buffer);

      printf("Genre {str}: ");
      scanf(" %[^\n]", buffer);
      strcpy(new_record->genre, buffer);

      printf("Year {int}: ");
      scanf("%d", &new_record->year);

      printf("Views {long int}: ");
      scanf("%ld", &new_record->views);

      confirm_update_add(new_record);
}

// ~ 4. ASK THE USER FOR CONFIRMATION ON THE CHANGE
void confirm_update_add(records *new_record){

      /*
      
      Definition: this function confirms the user's input and asks for confirmation.
      
      */

      ui_header_element();

      char *ptr;
      ptr = (char *)malloc(1);

      printf("\n\n\nNEW RECORD: \n");
      printf("------------------\n\n");

      printf("Title: %s", new_record->title);
      printf("\nAuthor: %s", new_record->author);
      printf("\nDuration: %s", new_record->duration);
      printf("\nGenre: %s", new_record->genre);
      printf("\nYear: %d", new_record->year);
      printf("\nViews: %ld", new_record->views);

      printf("\n\n--------------\n\n");

      printf("\n(*) Do you want to save the following data (y/n)?");
      printf("\n==> ");
      scanf("%c", ptr);
      
      switch (*ptr)
      {
      case 'y':
            save_csv_add(new_record);
            free(ptr);
            break;
      case 'n':
            ui_header_element();
            printf("\n\nData has not been saved.\n\n");
            end_request(0);
            break;
      default:
            printf("\n\n ERROR: Your option has not been registered. Please, try again.\n\n");
            confirm_update_add(new_record);
            break;
      }
}

// ~ 5. UPLOAD CHANGES PERMANTENTLY 
void save_csv_add(records *new_record){

      /*
      
      Definition: aggreagate user input's data to the database.
      
      */

      FILE* file = fopen(path , "a");

      if (file == NULL) {
        printf("Error opening file. Please make sure the link is correct.\n");
        return;
      }
      else {

            printf("\nFiles has been opened succesfully.\n\n");

      }
      fprintf(file, "%s,", new_record->title);       
      fprintf(file, "%s,", new_record->author);
      fprintf(file, "%s,", new_record->duration);  
      fprintf(file, "%s,", new_record->genre);
      fprintf(file, "%d,", new_record->year);
      fprintf(file, "%ld", new_record->views); 

      fputc('\n', file);

      fclose(file);

      ui_header_element();
      printf("\n\nData has been saved succesfully.\n\n");
      end_request(0);
}

#endif