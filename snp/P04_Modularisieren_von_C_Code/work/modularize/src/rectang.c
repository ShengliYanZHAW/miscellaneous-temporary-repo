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
 * @brief Rectangle module implementation
 */

#include "rectang.h"

/**
 * @brief Determines if a triangle is right-angled
 * @param[in] a First side of the triangle
 * @param[in] b Second side of the triangle
 * @param[in] c Third side of the triangle
 * @returns Returns 1 (true) if right-angled, 0 (false) if not
 */
int Rectangular(int a, int b, int c)
{
    int aS = a * a;
    int bS = b * b;
    int cS = c * c;
    
    int isRightAngled;
    if ((a == 0) && (b == 0) && (c == 0))
        isRightAngled = 0;
    else if ((aS + bS) == cS)
        isRightAngled = 1;
    else if ((aS + cS) == bS)
        isRightAngled = 1;
    else if ((bS + cS) == aS)
        isRightAngled = 1;
    else
        isRightAngled = 0;
    
    return isRightAngled;
}
