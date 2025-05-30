#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "person.h"

int person_compare(const person_t *a, const person_t *b)
{
	assert(a);
	assert(b);
	int res = strncmp(a->name, b->name, NAME_LEN);
	if (res == 0) res = strncmp(a->first_name, b->first_name, NAME_LEN);
	if (res == 0) res = a->age - b->age;
	return res;
}

int person_read(person_t *p)
{
	assert(p);
	assert(NAME_LEN == 20);
	memset(p, 0, sizeof(person_t));  
 
	return scanf("%19s %19s %d", p->name, p->first_name, &(p->age)) == 3;
}

//operations for persistency lab


static const int max_len = 128; //!!!könnte man schöner lösen, scia

int person_to_csv_string(person_t* person, char* s)
{
    // serialize person fields into CSV string
    return snprintf(s, max_len, "%s,%s,%u", person->name, person->first_name, person->age);
}

void person_from_csv_string(person_t* person, char* s)
{
    // parse CSV string with sscanf (fields separated by commas)
    unsigned int age = 0;
    // read up to NAME_LEN-1 chars for name and first_name, then age
    if (sscanf(s, "%19[^,],%19[^,],%u", person->name, person->first_name, &age) == 3) {
        person->name[NAME_LEN-1] = '\0';
        person->first_name[NAME_LEN-1] = '\0';
        person->age = age;
    } else {
        // if parsing fails, zero the person
        person->name[0] = '\0';
        person->first_name[0] = '\0';
        person->age = 0;
    }
}



