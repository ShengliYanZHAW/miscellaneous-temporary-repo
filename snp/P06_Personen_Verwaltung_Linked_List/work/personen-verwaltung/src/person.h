/**
 * @file person.h
 * @brief Person data structure and related functions
 */
 #ifndef PERSON_H
 #define PERSON_H
 
 #define NAME_LEN 20
 
 typedef struct {
   char         name[NAME_LEN];
   char         first_name[NAME_LEN];
   unsigned int age;
 } person_t;
 
 /**
  * @brief  Compares two persons in this sequence: 1st=name, 2nd=first_name, 3rd=age
  * @param  a [IN] const reference to 1st person in the comparison
  * @param  b [IN] const reference to 2nd person in the comparison
  * @return =0 if all record fields are the same
  *         >0 if all previous fields are the same, but for this field, a is greater
  *         <0 if all previous fields are the same, but for this field, b is greater
  * @remark strncmp() is used for producing the result of string field comparisons
  * @remark a->age - b->age is used for producing the result of age comparison
  */
 int person_compare(const person_t *a, const person_t *b);
 
 /**
  * @brief Reads a person's data from stdin
  * @param person [OUT] Pointer to the person structure to be filled
  * @return 0 on success, -1 on error (invalid input)
  */
 int person_read(person_t *person);
 
 /**
  * @brief Prints a person's data to stdout
  * @param person [IN] Pointer to the person structure to be printed
  */
 void person_print(const person_t *person);
 
 #endif // PERSON_H