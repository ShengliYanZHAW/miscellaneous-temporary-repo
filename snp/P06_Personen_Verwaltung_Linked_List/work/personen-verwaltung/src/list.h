/**
 * @file list.h
 * @brief Linked list implementation for person management
 */
 #ifndef LIST_H
 #define LIST_H
 
 #include "person.h"
 
 typedef struct node {
   person_t     content;        // Person stored in this node
   struct node *next;           // Pointer to the next node in the list
 } node_t;
 
 /**
  * @brief Initializes a linked list with an anchor node
  * @param anchor [OUT] Pointer to the anchor node
  */
 void list_init(node_t *anchor);
 
 /**
  * @brief Inserts a person into the linked list in sorted order
  * @param anchor [IN/OUT] Pointer to the anchor node of the list
  * @param person [IN] Pointer to the person to be inserted
  * @return 0 on success, -1 if a duplicate is found or memory allocation failed
  */
 int list_insert(node_t *anchor, const person_t *person);
 
 /**
  * @brief Removes a person from the linked list
  * @param anchor [IN/OUT] Pointer to the anchor node of the list
  * @param person [IN] Pointer to the person to be removed
  * @return 0 on success, -1 if person not found
  */
 int list_remove(node_t *anchor, const person_t *person);
 
 /**
  * @brief Clears the linked list, freeing all nodes except the anchor
  * @param anchor [IN/OUT] Pointer to the anchor node of the list
  */
 void list_clear(node_t *anchor);
 
 /**
  * @brief Prints all persons in the linked list
  * @param anchor [IN] Pointer to the anchor node of the list
  */
 void list_print(const node_t *anchor);
 
 /**
  * @brief Checks if the list is empty (only contains the anchor)
  * @param anchor [IN] Pointer to the anchor node of the list
  * @return 1 if empty, 0 otherwise
  */
 int list_is_empty(const node_t *anchor);
 
 #endif // LIST_H