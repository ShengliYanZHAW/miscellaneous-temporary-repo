/**
 * @file person.c
 * @brief Implementation of person-related functions
 */
 #include "person.h"
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <limits.h>
 
 int person_compare(const person_t *a, const person_t *b) {
     // Compare last names
     int result = strncmp(a->name, b->name, NAME_LEN);
     if (result != 0) {
         return result;
     }
     
     // If last names are equal, compare first names
     result = strncmp(a->first_name, b->first_name, NAME_LEN);
     if (result != 0) {
         return result;
     }
     
     // If both names are equal, compare ages
     return (int)(a->age - b->age);
 }
 
 int person_read(person_t *person) {
     char buffer[100]; // Buffer for reading input
     
     // Read last name
     printf("Enter last name: ");
     if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
         return -1;
     }
     
     // Remove newline character and check length
     size_t len = strlen(buffer);
     if (len > 0 && buffer[len-1] == '\n') {
         buffer[len-1] = '\0';
         len--;
     }
     
     if (len >= NAME_LEN) {
         printf("Error: Last name too long (max %d characters)\n", NAME_LEN - 1);
         return -1;
     }
     
     strncpy(person->name, buffer, NAME_LEN);
     person->name[NAME_LEN - 1] = '\0';
     
     // Read first name
     printf("Enter first name: ");
     if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
         return -1;
     }
     
     // Remove newline character and check length
     len = strlen(buffer);
     if (len > 0 && buffer[len-1] == '\n') {
         buffer[len-1] = '\0';
         len--;
     }
     
     if (len >= NAME_LEN) {
         printf("Error: First name too long (max %d characters)\n", NAME_LEN - 1);
         return -1;
     }
     
     strncpy(person->first_name, buffer, NAME_LEN);
     person->first_name[NAME_LEN - 1] = '\0';
     
     // Read age
     printf("Enter age: ");
     if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
         return -1;
     }
     
     char *endptr;
     long age = strtol(buffer, &endptr, 10);
     
     // Check for invalid age input
     if (endptr == buffer || *endptr != '\n') {
         printf("Error: Invalid age\n");
         return -1;
     }
     
     if (age < 0 || age > UINT_MAX) {
         printf("Error: Age out of range\n");
         return -1;
     }
     
     person->age = (unsigned int)age;
     
     return 0;
 }
 
 void person_print(const person_t *person) {
     printf("%-20s %-20s %u\n", person->name, person->first_name, person->age);
 }