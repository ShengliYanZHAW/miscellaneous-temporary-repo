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
 * @brief Rectangle module interface
 */

#ifndef RECTANG_H_
#define RECTANG_H_

/**
 * @brief Determines if a triangle is right-angled
 * @param[in] a First side of the triangle
 * @param[in] b Second side of the triangle
 * @param[in] c Third side of the triangle
 * @returns Returns 1 (true) if right-angled, 0 (false) if not
 */
int Rectangular(int a, int b, int c);

#endif /* RECTANG_H_ */
