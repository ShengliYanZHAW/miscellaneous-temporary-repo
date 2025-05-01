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
 * @brief Read module implementation
 */

#include <stdio.h>
#include "read.h"

/**
 * @brief Reads an unsigned integer from stdin
 * @param[in] maxResult Maximum allowed value for the result
 * @returns Returns the converted integer value, or PARSE_ERROR if not a number or too large, 
 *          or READ_ERROR if there was an error reading from stdin
 */
int getInt(int maxResult)
{
    // end of input
    const int EOF_CHAR = -1; // end of file
    const int EOL_CHAR = 10; // end of line (newline)
    
    // ASCII Codes
    const int ASCII_SPACE   = 32; // ' '
    const int ASCII_DIGIT_0 = 48; // '0'
    const int ASCII_DIGIT_9 = 57; // '9'
    
    // conversion buffer
    const int NO_POS = -1;
    const int BUFFERSIZE = 10;
    char buffer[BUFFERSIZE];
    
    int result = 0;
    
    // read line: up to EOL or EOF (i.e. error while reading)
    int bytes = 0;
    int input = getchar();
    while ((input != EOL_CHAR) && (input != EOF_CHAR)) { // read whole line
        if (bytes < BUFFERSIZE) { // only buffer first n characters
            buffer[bytes] = (char)input;
            bytes++;
        } else {
            result = PARSE_ERROR; // exceed buffer size, continue read line
        }
        input = getchar();
    }
    if (input == EOF_CHAR) {
        result = READ_ERROR;
    }
    
    // check for numbers: skip leading and trailing spaces
    // (i.e. this includes all control chars below the space ASCII code)
    int pos = 0;
    while ((pos < bytes) && (buffer[pos] <= ASCII_SPACE)) pos++; // skip spaces
    int posOfFirstDigit = pos;
    int posOfLastDigit = NO_POS;
    while ((pos < bytes) 
           && (buffer[pos] >= ASCII_DIGIT_0) 
           && (buffer[pos] <= ASCII_DIGIT_9)) {
        posOfLastDigit = pos;
        pos++;
    }
    while ((pos < bytes) && (buffer[pos] <= ASCII_SPACE)) pos++; // skip spaces
    
    // produce return value
    if (result != 0) {
        // previously detected read or parse error given
    } else if ((pos != bytes) || (posOfLastDigit == NO_POS)) {
        result = PARSE_ERROR;
    } else { // convert number
        for (int i = posOfFirstDigit; i <= posOfLastDigit; i++) {
            result = result * 10 + (buffer[i] - ASCII_DIGIT_0);
            if (result > maxResult) {
                result = PARSE_ERROR;
                break;
            }
        }
    }
    return result;
}
