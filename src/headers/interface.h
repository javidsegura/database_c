// AVOID DEFINING HEADER TWICE
#ifndef INTERFACE_H
#define INTERFACE_H

// Importing standard libraries' headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Importing user-defined headers 
#include "funcs.h"

//Functions prototypes from other headers 
void partial_db_read(int mode);
void complete_db_read();
void record_prior_next_read(int user_record, int direction);

//Function prototype from local functions
void ui_header_element();



void end_request(int mode){

      /*
      
      Description: this function allows the user to decide what do do after he has reached the end of a feature 
      (instead of automatically being taken to the homepage as it would have had been with the infinite while loop)
      Parameters:
            - mode: different options at the end of a feature
                  - 0: end of page for read_columns and add_save
                  - 1: end of page for read_full_db
                  - 2: end of page for read_partial_db 

      */

      int user_decision;

      if (mode == 0){
      printf("\n\n\n\n ----------------------------------------\n");
      printf("(*) Return to homepage (0) or exit program (1): \n");
      printf("==> ");
      scanf("%d", &user_decision);

      switch (user_decision)
      {
      case 0:
            system("clear");
            break;
      case 1:
            system("clear");
            printf("\n\n Goodbye!");
            exit(0);
            break;
      default:
            ui_header_element();
            printf("Your option has not been registered. Please, try again.\n");
            fflush(stdout);  // Flush the output buffer to make sure the message appears before sleep
            end_request(0);
            break;
      }
      }

      else if (mode == 1){

            printf("\n\n\n\n --------------------------------------\n");
            printf("(*) Return to homepage (0), exit program (1) or show only partial details (2): \n");
            printf("==> ");
            scanf("%d", &user_decision);

            switch (user_decision)
            {
            case 0:
                  system("clear");
                  break;
            case 1:
                  system("clear");
                  printf("\n\n Goodbye!");
                  exit(0);
                  break;
            case 2:
                  ui_header_element();
                  partial_db_read(1);
                  break;
            default:
                  system("clear");
                  printf("Your option has not been registered. Please, try again.\n");
                  fflush(stdout);  
                  sleep(2);
                  complete_db_read();
                  break;
            }
      }
      else if (mode == 2){

            printf("\n\n\n\n ------------------------------------\n");
            printf("(*) Return to homepage (0), exit program (1) or show all details (2): \n");
            printf("==> ");
            scanf("%d", &user_decision);

            switch (user_decision)
            {
            case 0:
                  system("clear");
                  break;
            case 1:
                  system("clear");
                  printf("\n\n Goodbye!");
                  exit(0);
                  break;
            case 2:
                  complete_db_read();
                  break;
            default:
                  system("clear");
                  printf("Your option has not been registered. Please, try again.");
                  fflush(stdout);
                  sleep(2);
                  partial_db_read(1);
                  break;
            }
      }
}

void end_request_prior_record(int current_record_index){

      /*
      
      Description: follow-up functions from the prior one. It also presents a possibility for the user to be redirected after reaching the end of a features
      Parameters:
            - current_record_index: if reached from 'subscripts_record_read()' the value will be the subscripted record. If coming
            from 'record_prior_next_read()' it will be the one displayed after having chosen 'next record' or 'prior record'


      Note: this function's code has not be written as another case from 'end_request()' as for this one requiring to be passed an argument.
      
      */

      int user_decision;

      printf("\n\n\n\n ------------------------------------\n");
      printf("(*) Return to homepage (0), exit program (1), prior record (2) or next record (3): \n");
      printf("==> ");
      scanf("%d", &user_decision);

      switch (user_decision)
      {
      case 0:
            system("clear");
            break;
      case 1:
            system("clear");
            printf("\n\n Goodbye!");
            exit(0);
            break;
      case 2:
            record_prior_next_read(current_record_index, -1);
            break;
      case 3:
            record_prior_next_read(current_record_index, 1);
            break;
      default:
            system("clear");
            printf("Your option has not been registered. Please, try again.\n");
            fflush(stdout);
            sleep(2);
            end_request_prior_record(current_record_index);
            break;
      }
            


      
}

void ui_header_element(){

      /*
      
      Description: print a header at the top of the of the console with information about the program. 
      
      */
    system("clear");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\n\n");
    printf("\t\t\t\t\t\t\t\t\t\tDATABASE MANAGEMENT SYSTEM");
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t    Session info: %s", asctime (timeinfo)); 
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
}

#endif