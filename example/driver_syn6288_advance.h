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
 * @file      driver_syn6288_advance.h
 * @brief     driver syn6288 advance header file
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

#ifndef DRIVER_SYN6288_ADVANCE_H
#define DRIVER_SYN6288_ADVANCE_H

#include "driver_syn6288_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup syn6288_example_driver
 * @{
 */

/**
 * @brief syn6288 advance send command configure
 */
#ifndef SYN6288_ADVANCE_SEND_CONFIG
    #define SYN6288_ADVANCE_SEND_CONFIG 0        /**< don't send */
#endif

/**
 * @brief syn6288 advance example default definition
 */
#define SYN6288_ADVANCE_DEFAULT_BAUD_RATE           SYN6288_BAUD_RATE_9600_BPS        /* 9600 bps */
#define SYN6288_ADVANCE_DEFAULT_MODE                SYN6288_MODE_COMMON               /* common mode */
#define SYN6288_ADVANCE_DEFAULT_TEXT_TYPE           SYN6288_TYPE_GB2312               /* gb2312 type */
#define SYN6288_ADVANCE_DEFAULT_SYNTHESIS_VOLUME    16                                /* synthesis volume 16 */
#define SYN6288_ADVANCE_DEFAULT_BACKGROUND_VOLUME   0                                 /* background volume 0 */
#define SYN6288_ADVANCE_DEFAULT_SYNTHESIS_SPEED     5                                 /* synthesis speed 5 */

/**
 * @brief  advance example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t syn6288_advance_init(void);

/**
 * @brief  advance example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t syn6288_advance_deinit(void);

/**
 * @brief     advance example synthesis
 * @param[in] *text points to a text buffer
 * @return    status code
 *            - 0 success
 *            - 1 synthesis failed
 * @note      none
 */
uint8_t syn6288_advance_synthesis(char *text);

/**
 * @brief     advance example play the sound
 * @param[in] sound is the sound type
 * @return    status code
 *            - 0 success
 *            - 1 play sound failed
 * @note      none
 */
uint8_t syn6288_advance_sound(syn6288_sound_t sound);

/**
 * @brief     advance example play the message
 * @param[in] message is the message type
 * @return    status code
 *            - 0 success
 *            - 1 play message failed
 * @note      none
 */
uint8_t syn6288_advance_message(syn6288_message_t message);

/**
 * @brief     advance example play the ring
 * @param[in] ring is the ring type
 * @return    status code
 *            - 0 success
 *            - 1 play ring failed
 * @note      none
 */
uint8_t syn6288_advance_ring(syn6288_ring_t ring);

/**
 * @brief  advance example sync
 * @return status code
 *         - 0 success
 *         - 1 sync failed
 * @note   none
 */
uint8_t syn6288_advance_sync(void);

/**
 * @brief  advance example power down
 * @return status code
 *         - 0 success
 *         - 1 power down failed
 * @note   none
 */
uint8_t syn6288_advance_power_down(void);

/**
 * @brief  advance example stop
 * @return status code
 *         - 0 success
 *         - 1 stop failed
 * @note   none
 */
uint8_t syn6288_advance_stop(void);

/**
 * @brief  advance example resume
 * @return status code
 *         - 0 success
 *         - 1 resume failed
 * @note   none
 */
uint8_t syn6288_advance_resume(void);

/**
 * @brief  advance example pause
 * @return status code
 *         - 0 success
 *         - 1 pause failed
 * @note   none
 */
uint8_t syn6288_advance_pause(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
