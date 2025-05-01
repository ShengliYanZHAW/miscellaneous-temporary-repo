/**
 * @file string_sorter.c
 * @brief Program to read, convert to uppercase, sort and output strings
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 10
#define MAX_LENGTH 21  // 20 chars + null terminator

/**
 * @brief Converts a string to uppercase
 * @param str The string to convert
 */
void convertToUppercase(char *str) {
    while (*str) {
        *str = toupper((unsigned char) *str);
        str++;
    }
}

/**
 * @brief Checks if a word already exists in the array
 * @param words Array of words
 * @param count Number of words in array
 * @param word Word to check
 * @return 1 if word exists, 0 otherwise
 */
int wordExists(char words[][MAX_LENGTH], int count, const char *word) {
    for (int i = 0; i < count; i++) {
        if (strcmp(words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Sorts an array of strings alphabetically
 * @param words Array of words to sort
 * @param count Number of words in array
 */
void sortWords(char words[][MAX_LENGTH], int count) {
    char temp[MAX_LENGTH];
    
    // Simple bubble sort algorithm
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(words[j], words[j+1]) > 0) {
                // Swap words
                strcpy(temp, words[j]);
                strcpy(words[j], words[j+1]);
                strcpy(words[j+1], temp);
            }
        }
    }
}

int main() {
    char words[MAX_WORDS][MAX_LENGTH];
    char input[MAX_LENGTH];
    int count = 0;
    
    printf("Enter up to %d words (max %d chars each).\n", MAX_WORDS, MAX_LENGTH-1);
    printf("Enter 'ZZZ' to finish.\n");
    
    while (count < MAX_WORDS) {
        printf("Word %d: ", count + 1);
        
        if (scanf("%20s", input) != 1) {
            printf("Error reading input.\n");
            return 1;
        }
        
        convertToUppercase(input);
        
        // Check for termination condition
        if (strcmp(input, "ZZZ") == 0) {
            break;
        }
        
        // Check if word already exists
        if (!wordExists(words, count, input)) {
            strcpy(words[count], input);
            count++;
        } else {
            printf("Word already exists, ignored.\n");
        }
    }
    
    if (count > 0) {
        // Sort words alphabetically
        sortWords(words, count);
        
        // Print sorted words
        printf("\nSorted words in uppercase:\n");
        for (int i = 0; i < count; i++) {
            printf("%d. %s\n", i + 1, words[i]);
        }
    } else {
        printf("\nNo words were entered.\n");
    }
    
    return 0;
}