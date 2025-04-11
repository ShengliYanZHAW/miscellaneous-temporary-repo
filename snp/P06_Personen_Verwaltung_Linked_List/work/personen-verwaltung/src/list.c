/**
 * @file list.c
 * @brief Implementation of linked list functions for person management
 */
 #include "list.h"
 #include <stdlib.h>
 #include <stdio.h>
 
 void list_init(node_t *anchor) {
     anchor->next = anchor; // Point to itself (empty circular list)
 }
 
 int list_insert(node_t *anchor, const person_t *person) {
     // Find the insertion point
     node_t *prev = anchor;
     node_t *curr = anchor->next;
     
     // Traverse the list until we find the correct position
     while (curr != anchor) {
         // Check if this is a duplicate
         if (person_compare(&curr->content, person) == 0) {
             return -1; // Duplicate found
         }
         
         // Check if we've found the insertion point
         if (person_compare(&curr->content, person) > 0) {
             break; // curr is "greater" than person, insert before curr
         }
         
         prev = curr;
         curr = curr->next;
     }
     
     // Create a new node
     node_t *new_node = (node_t *)malloc(sizeof(node_t));
     if (new_node == NULL) {
         return -1; // Memory allocation failed
     }
     
     // Set the node's content and pointers
     new_node->content = *person;
     new_node->next = curr;
     prev->next = new_node;
     
     return 0;
 }
 
 int list_remove(node_t *anchor, const person_t *person) {
     node_t *prev = anchor;
     node_t *curr = anchor->next;
     
     // Traverse the list to find the person
     while (curr != anchor) {
         if (person_compare(&curr->content, person) == 0) {
             // Found the person, remove the node
             prev->next = curr->next;
             free(curr);
             return 0;
         }
         
         prev = curr;
         curr = curr->next;
     }
     
     return -1; // Person not found
 }
 
 void list_clear(node_t *anchor) {
     node_t *curr = anchor->next;
     
     // Set anchor to point to itself (empty list)
     anchor->next = anchor;
     
     // Free all nodes except the anchor
     while (curr != anchor) {
         node_t *temp = curr;
         curr = curr->next;
         free(temp);
     }
 }
 
 void list_print(const node_t *anchor) {
     const node_t *curr = anchor->next;
     
     if (curr == anchor) {
         printf("List is empty\n");
         return;
     }
     
     printf("%-20s %-20s %s\n", "Last Name", "First Name", "Age");
     printf("----------------------------------------\n");
     
     while (curr != anchor) {
         person_print(&curr->content);
         curr = curr->next;
     }
 }
 
 int list_is_empty(const node_t *anchor) {
     return anchor->next == anchor;
 }