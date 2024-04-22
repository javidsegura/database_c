// 0. SET UP
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


// Will have to redine the path here (with a different name)
char url[] = "/Users/javierdominguezsegura/Programming/No Python/C/Programming principles/Database Management System/data/MUSIC - DATASET - Sheet1 (1) (1).csv";


// 1. DATABASE STRUCTURE

typedef struct {

      char title[99];
      char author[99];
      char duration[99];
      char genre[99];
      int year;
      long int views;
      
} records;

void user_decision_add(records *sample_data);
void save_csv_add(records *sample_data);
void create_instance_add();
void confirm_update_add(records *sample_data);

void record_add(){

      /*
      
      Definition: this function creates a new record and adds it to the database. It only calls functions as it needs to rely on independet calls to properly aggreagate the data (to create a 'records' instance at every call)
      
      */

    create_instance_add();

}

void create_instance_add(){

      // Create a new instance of the records struct 
      records db;

      user_decision_add(&db);


}

void user_decision_add(records *sample_data){

      /*
      
      Definition: this function prompts the user to input the data for a new record.
      It then calls the function 'save_csv_add' to add the new record to the database.
      
      */

     system("clear");

     char user_decision_duration[99];


     printf("\nTitle {str}: ");
     scanf("%s", sample_data->title);

     printf("Author {str}: ");
     scanf("%s", sample_data->author);

     printf("Duration-(MM:SS) {int}: "); // Can be optimized to a single tokenized input
     scanf("%s", sample_data->duration);

     printf("Genre {str}: ");
     scanf("%s", sample_data->genre);

     printf("Year {int}: ");
     scanf("%d", &sample_data->year);

     printf("Views {long int}: ");
     scanf("%ld", &sample_data->views);

     confirm_update_add(sample_data);
}

void confirm_update_add(records *sample_data){

      /*
      
      Definition: this function confirms the user's input and asks for confirmation.
      
      */

      system("clear");

      char user_decision[30];

      printf("(*) Do you want to save the following data (y/n) ?\n\n");
      printf("---------------------------\n\n");

      printf("\n\nTitle: %s", sample_data->title);
      printf("\nAuthor: %s", sample_data->author);
      printf("\nDuration: %s", sample_data->duration);
      printf("\nGenre: %s", sample_data->genre);
      printf("\nYear: %d", sample_data->year);
      printf("\nViews: %ld", sample_data->views);

      printf("\n\n---------------------------\n\n");


      printf("\n==> ");
      scanf("%s", user_decision);
      

      if (strcmp(user_decision, "y") == 0) {
        save_csv_add(sample_data);
      }
      else {
        printf("\n\nData has not been saved.\n\n");
      }

}


void save_csv_add(records *sample_data){

      /*
      
      Definition: aggreagate user input's data to the database.
      
      */


      FILE* file = fopen(url, "a");

      if (file == NULL) {
        printf("Error opening file. Please make sure the link is correct.\n");
        return;
      }
      else {

            printf("\nFiles has been opened succesfully.\n\n");

      }



      fprintf(file, "%s,", sample_data->title);       
      fprintf(file, "%s,", sample_data->author);
      fprintf(file, "%s,", sample_data->duration);  
      fprintf(file, "%s,", sample_data->genre);
      fprintf(file, "%d,", sample_data->year);
      fprintf(file, "%ld", sample_data->views); 


      fputc('\n', file);

      fclose(file);

      system("clear");
      printf("\n\nData has been saved succesfully.\n\n");

}
