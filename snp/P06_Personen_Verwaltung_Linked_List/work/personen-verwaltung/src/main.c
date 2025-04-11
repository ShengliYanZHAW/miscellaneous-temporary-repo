/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur             -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences)           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 */
/**
 * @file
 * @brief Lab implementation
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <ctype.h>
 #include "person.h"
 #include "list.h"
 
 /**
  * @brief Main entry point.
  * @param[in] argc  The size of the argv array.
  * @param[in] argv  The command line arguments...
  * @returns Returns EXIT_SUCCESS (=0) on success, EXIT_FAILURE (=1) there is an expression syntax error.
  */
 int main(int argc, char* argv[])
 {
	 // Initialize linked list
	 node_t anchor;
	 list_init(&anchor);
	 
	 char choice;
	 int result;
	 person_t person;
	 
	 while (1) {
		 printf("\nI(nsert), R(emove), S(how), C(lear), E(nd): ");
		 scanf(" %c", &choice);
		 while (getchar() != '\n'); // Clear input buffer
		 
		 choice = toupper(choice);
		 
		 switch (choice) {
			 case 'I': // Insert
				 printf("Enter person details to insert:\n");
				 if (person_read(&person) == 0) {
					 result = list_insert(&anchor, &person);
					 if (result == 0) {
						 printf("Person successfully inserted\n");
					 } else {
						 printf("Error: Person already exists or memory allocation failed\n");
					 }
				 } else {
					 printf("Error: Invalid input\n");
				 }
				 break;
				 
			 case 'R': // Remove
				 printf("Enter person details to remove:\n");
				 if (person_read(&person) == 0) {
					 result = list_remove(&anchor, &person);
					 if (result == 0) {
						 printf("Person successfully removed\n");
					 } else {
						 printf("Error: Person not found\n");
					 }
				 } else {
					 printf("Error: Invalid input\n");
				 }
				 break;
				 
			 case 'S': // Show
				 printf("\nCurrent list of persons:\n");
				 list_print(&anchor);
				 break;
				 
			 case 'C': // Clear
				 list_clear(&anchor);
				 printf("List cleared\n");
				 break;
				 
			 case 'E': // End
				 // Clean up before exit
				 list_clear(&anchor);
				 printf("Exiting program\n");
				 return EXIT_SUCCESS;
				 
			 default:
				 printf("Invalid choice\n");
		 }
	 }
	 
	 return EXIT_SUCCESS;
 }