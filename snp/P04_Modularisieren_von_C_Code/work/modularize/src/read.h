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
 * @brief Read module interface
 */

#ifndef READ_H_
#define READ_H_

/**
 * @brief Error codes for getInt function
 */
#define PARSE_ERROR -1
#define READ_ERROR  -2

/**
 * @brief Reads an unsigned integer from stdin
 * @param[in] maxResult Maximum allowed value for the result
 * @returns Returns the converted integer value, or PARSE_ERROR if not a number or too large, 
 *          or READ_ERROR if there was an error reading from stdin
 */
int getInt(int maxResult);

#endif /* READ_H_ */
