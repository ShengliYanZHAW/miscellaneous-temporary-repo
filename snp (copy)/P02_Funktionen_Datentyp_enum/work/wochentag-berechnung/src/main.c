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
 * @brief Lab P02 weekday
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


// *** TASK1: typedef enum types for month_t (Jan=1,...Dec} ***
// BEGIN-STUDENTS-TO-ADD-CODE

typedef enum {
    Jan=1, Feb, Mar, Apr, Mai, Jun, Jul, Aug, Sep, Oct, Nov, Dec
} month_t;

// END-STUDENTS-TO-ADD-CODE


// *** TASK1: typedef struct for date_t ***
// BEGIN-STUDENTS-TO-ADD-CODE

typedef struct {
    int year; 
    int month; 
    int day; 
} date_t; 

// END-STUDENTS-TO-ADD-CODE



// *** TASK2: typedef enum weekday_t (Sun=0, Mon, ...Sat) ***
// BEGIN-STUDENTS-TO-ADD-CODE

typedef enum {
    Sun=0, Mon, Tue, Wed, Thu, Fri, Sat
} weekday_t; 

// END-STUDENTS-TO-ADD-CODE

/**
 * @brief   TASK1: Checks if the given date is a leap year.
 * @returns 0 = is not leap year, 1 = is leap year
 */
// BEGIN-STUDENTS-TO-ADD-CODE

int is_leap_year(date_t date) {
    if (date.year%4 == 0) {
        if (date.year%100 == 0) {
            if (date.year%400 == 0) {
                return 1; 
            } else {
                return 0; 
            }
        } else {
            return 1; 
        }
    } else {
        return 0; 
    }
}

// END-STUDENTS-TO-ADD-CODE


/**
 * @brief   TASK1: Calculates the length of the month given by the data parameter
 * @returns 28, 29, 30, 31 if a valid month, else 0
 */
// BEGIN-STUDENTS-TO-ADD-CODE

int get_month_length(date_t date) {

    if (is_leap_year(date) && (date.month==Feb)) {
        return 29; 
    } else {
        switch (date.month) {
            case Jan: 
            case Mar: 
            case Mai: 
            case Jul: 
            case Aug: 
            case Oct: 
            case Dec: 
                return 31; 
                break; 
            case Feb: 
                return 28; 
                break; 
            case Apr: 
            case Jun: 
            case Sep: 
            case Nov: 
                return 30; 
                break; 
            default: 
                return 0;
        }
    } 
}

// END-STUDENTS-TO-ADD-CODE

/**
 * @brief   TASK1: Checks if the given date is in the gregorian date range
 * @returns 0 = no, 1 = yes
 */
// BEGIN-STUDENTS-TO-ADD-CODE

int is_gregorian_date(date_t date) { 
    // Everything between 1583 and 9999 is always valid
    if (date.year > 1582 && date.year <= 9999) {
        return 1; 
    }

    // If it is the year 1582 we have to be careful -->
    if (date.year == 1582) {

        // Nov and Dec are always valid
        if (date.month > 10) {
            return 1; 
        }

        // Oct is only valid, if the day is greater than 14
        if (date.month == 10 && date.day > 14) {
            return 1; 
        }

        // Every month, that is earlier jan, feb, etc. is NOT valid. 
        return 0; 
    }

    // Ever year before 1582 or after 9999 is NOT valid
    return 0; 
}

// END-STUDENTS-TO-ADD-CODE


/**
 * @brief   TASK1: Checks if the given date is a valid date.
 * @returns 0 = is not valid date, 1 = is valid date
 */
// BEGIN-STUDENTS-TO-ADD-CODE
int is_valid_date(date_t date) {
    int isValidDate = 1; 

    // Checks if it is not a Gregorian date 
    if (!is_gregorian_date(date)) {
        isValidDate = 0; 
    } 

    // Checks if the day of the month is invalid
    if (!(date.day <= get_month_length(date))) {
        isValidDate = 0; 
    }

    // Checks if day is smaller than 0
    if(!(date.day > 0)) {
        isValidDate = 0; 
    }

    return isValidDate; 
}

// END-STUDENTS-TO-ADD-CODE


/**
 * @brief   TASK2: calculated from a valid date the weekday
 * @returns returns a weekday in the range Sun...Sat
 */
// BEGIN-STUDENTS-TO-ADD-CODE

weekday_t calculate_weekday(date_t date) {
    //assert(is_valid_date(date)); 
    int weekday;
    if (is_valid_date(date)){
    int m = 1 + (date.month + 9) % 12; 
    int a = date.month < Mar ? date.year-1 : date.year; 
    int y = a % 100; 
    int c = a / 100; 
    weekday = ((date.day + (13*m-1)/5 + y + y/4 + c/4 - 2*c) % 7 + 7) % 7; 
    }
    else 
    {
        exit(EXIT_FAILURE);

    }
    return weekday; 
}

// END-STUDENTS-TO-ADD-CODE



/**
 * @brief   TASK2: print weekday as 3-letter abreviated English day name
 */
// BEGIN-STUDENTS-TO-ADD-CODE

void print_weekday(weekday_t day) {
    switch (day) {
        case Sun: 
            printf("Sun"); 
            break; 
        case Mon: 
            printf("Mon"); 
            break; 
        case Tue: 
            printf("Tue"); 
            break; 
        case Wed: 
            printf("Wed"); 
            break; 
        case Thu: 
            printf("Thu"); 
            break; 
        case Fri: 
            printf("Fri"); 
            break; 
        case Sat: 
            printf("Sat"); 
            break; 
        default: 
             assert(!"day is out-of-range"); 
    }
}

// END-STUDENTS-TO-ADD-CODE

/**
 * @brief   main function
 * @param   argc [in] number of entries in argv
 * @param   argv [in] program name plus command line arguments
 * @returns returns success if valid date is given, failure otherwise
 */
int main(int argc, const char *argv[])
{
    // TASK1: parse the mandatory argument into a date_t variable and check if the date is valid
    // BEGIN-STUDENTS-TO-ADD-CODE

    if(argc != 2) {
        fprintf(stderr, "Error: Illegal amount of given arguments\n"); 
        return EXIT_FAILURE; 
    }

    const char *userInput = argv[1]; 
    date_t newDate = {0};
    
    int inputControl = sscanf(userInput, "%d-%d-%d", &newDate.year, &newDate.month, &newDate.day);         

    if (!is_valid_date(newDate)) { 
        fprintf(stderr, "Error: Date format is wrong\n"); 
        return EXIT_FAILURE; 
    }
    
    if (inputControl !=3) {
        fprintf(stderr, "Error: Date format could not be read\n");
        return EXIT_FAILURE; 
    }

    // END-STUDENTS-TO-ADD-CODE


    // TASK2: calculate the weekday and print it in this format: "%04d-%02d-%02d is a %s\n"
    // BEGIN-STUDENTS-TO-ADD-CODE

    printf("%04d-%02d-%02d is a ", newDate.year, newDate.month, newDate.day); 
    print_weekday(calculate_weekday(newDate)); 
    printf("\n"); 

    // END-STUDENTS-TO-ADD-CODE

    return EXIT_SUCCESS;
}


