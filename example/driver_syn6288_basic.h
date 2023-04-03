/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_syn6288_basic.h
 * @brief     driver syn6288 basic header file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-03-17
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/17  <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/12/01  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_SYN6288_BASIC_H
#define DRIVER_SYN6288_BASIC_H

#include "driver_syn6288_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup syn6288_example_driver syn6288 example driver function
 * @brief    syn6288 example driver modules
 * @ingroup  syn6288_driver
 * @{
 */

/**
 * @brief syn6288 basic send command configure
 */
#ifndef SYN6288_BASIC_SEND_CONFIG
    #define SYN6288_BASIC_SEND_CONFIG 0        /**< don't send */
#endif

/**
 * @brief syn6288 basic example default definition
 */
#define SYN6288_BASIC_DEFAULT_BAUD_RATE           SYN6288_BAUD_RATE_9600_BPS        /**< 9600 bps */
#define SYN6288_BASIC_DEFAULT_MODE                SYN6288_MODE_COMMON               /**< common mode */
#define SYN6288_BASIC_DEFAULT_TEXT_TYPE           SYN6288_TYPE_GB2312               /**< gb2312 type */
#define SYN6288_BASIC_DEFAULT_SYNTHESIS_VOLUME    16                                /**< synthesis volume 16 */
#define SYN6288_BASIC_DEFAULT_BACKGROUND_VOLUME   0                                 /**< background volume 0 */
#define SYN6288_BASIC_DEFAULT_SYNTHESIS_SPEED     5                                 /**< synthesis speed 5 */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t syn6288_basic_init(void);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t syn6288_basic_deinit(void);

/**
 * @brief  basic example sync
 * @return status code
 *         - 0 success
 *         - 1 sync failed
 * @note   none
 */
uint8_t syn6288_basic_sync(void);

/**
 * @brief     basic example synthesis
 * @param[in] *text points to a text buffer
 * @return    status code
 *            - 0 success
 *            - 1 synthesis failed
 * @note      none
 */
uint8_t syn6288_basic_synthesis(char *text);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
