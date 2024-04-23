// Importing standard libraries' headers
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

// Importing user-defined headers
#include "headers/funcs.h"

//Function prototype from local functions
void homepage();

//Functions prototypes from other headers 
void complete_db_read();
void record_add();
void ui_header_element();
 

int main(){

        while (1){
        homepage();
        }

        return 0;
}



void homepage(){

    /*
    
    Description: this function presents the user with a menu with all features of the program. Features are accessed by providing the corresponding number to that feature.
    
    */

    load_csv(path);
      
    system("clear");
    ui_header_element();

    printf("\n\n|-> READ MODE\n");
    printf("      |--> Read full database (1.1)\n");
    printf("      |--> Read by columns (1.2)\n");
    printf("      |--> Read by rows (1.3)\n");
    printf("                                       \n");
     printf("|-> WRITE/SAVE MODE \n");
    printf("      |--> Add a row to the db (2.1)\n");
    printf("      |--> Edit an existing row in the db (2.2)\n");

    char user_decision_homepage[99];   

    printf("\n\n\n(*) Select an option here: ");
    printf("\n==> ");
    scanf("%s", user_decision_homepage);

    if (strcmp(user_decision_homepage, "1.1") == 0){
            complete_db_read();
    }
    else if (strcmp(user_decision_homepage, "1.2") == 0){
            subscripts_column_read();
    }
    else if (strcmp(user_decision_homepage, "1.3") == 0){
            subscripts_record_read();
    }
    else if (strcmp(user_decision_homepage, "2.1") == 0){
            record_add();
  
    }
    else if (strcmp(user_decision_homepage, "2.2") == 0){
            printf("We are currently working on it. Please try again later.\n");
            fflush(stdout);
            sleep(2);
    }
    else{
            printf("ERROR: Invalid input. Please try again.\n");
            sleep(2);
            homepage();
    }
}


