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
// begin students to add code for task 4.1
#ifndef READ_H
#define READ_H

// Return values for error conditions
#define PARSE_ERROR -1
#define READ_ERROR -2

/**
 * Reads an unsigned integer from stdin (via byte stream).
 * First reads a line and then converts it to an integer.
 * The read line may only contain one number (with optional spaces before/after).
 *
 * @param maxResult Maximum allowed value for the result
 * @return The converted number, or PARSE_ERROR if no number or too large,
 *         or READ_ERROR if there was an error reading
 */
int getInt(int maxResult);

#endif // READ_H
// end students to add code
