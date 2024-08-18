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
 * @file      driver_syn6288_synthesis_test.c
 * @brief     driver syn6288 synthesis test source file
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

#include "driver_syn6288_synthesis_test.h"

static syn6288_handle_t gs_handle;        /**< syn6288 handle */

/**
 * @brief  synthesis test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t syn6288_synthesis_test(void)
{
    uint8_t res;
    syn6288_info_t info;
    syn6288_status_t status;
    char s[32];
    uint8_t gb2312_text[] = {0xD3, 0xEE, 0xD2, 0xF4, 0xCC, 0xEC, 0xCF, 0xC2, 0x00};
    uint8_t gbk_text[] = {0xD3, 0xEE, 0xD2, 0xF4, 0xCC, 0xEC, 0xCF, 0xC2, 0x00};
    uint8_t big5_text[] = {0xA6, 0x74, 0xAD, 0xB5, 0xA4, 0xD1, 0xA4, 0x55, 0x00};
    uint8_t unicode_text[] = {0x8B, 0xED, 0x97, 0xF3, 0x59, 0x29, 0x4E, 0x0B, 0x00};
    
    /* link interface function */
    DRIVER_SYN6288_LINK_INIT(&gs_handle, syn6288_handle_t);
    DRIVER_SYN6288_LINK_UART_INIT(&gs_handle, syn6288_interface_uart_init);
    DRIVER_SYN6288_LINK_UART_DEINIT(&gs_handle, syn6288_interface_uart_deinit);
    DRIVER_SYN6288_LINK_UART_READ(&gs_handle, syn6288_interface_uart_read);
    DRIVER_SYN6288_LINK_UART_WRITE(&gs_handle, syn6288_interface_uart_write);
    DRIVER_SYN6288_LINK_UART_FLUSH(&gs_handle, syn6288_interface_uart_flush);
    DRIVER_SYN6288_LINK_DELAY_MS(&gs_handle, syn6288_interface_delay_ms);
    DRIVER_SYN6288_LINK_DEBUG_PRINT(&gs_handle, syn6288_interface_debug_print);
    
    /* get syn6288 information */
    res = syn6288_info(&info);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        syn6288_interface_debug_print("syn6288: chip is %s.\n", info.chip_name);
        syn6288_interface_debug_print("syn6288: manufacturer is %s.\n", info.manufacturer_name);
        syn6288_interface_debug_print("syn6288: interface is %s.\n", info.interface);
        syn6288_interface_debug_print("syn6288: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        syn6288_interface_debug_print("syn6288: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        syn6288_interface_debug_print("syn6288: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        syn6288_interface_debug_print("syn6288: max current is %0.2fmA.\n", info.max_current_ma);
        syn6288_interface_debug_print("syn6288: max temperature is %0.1fC.\n", info.temperature_max);
        syn6288_interface_debug_print("syn6288: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* syn6288 init */
    res = syn6288_init(&gs_handle);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: init failed.\n");
       
        return 1;
    }
    
    /* set baud rate 9600 bps */
    res = syn6288_set_baud_rate(&gs_handle, SYN6288_BAUD_RATE_9600_BPS);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set baud rate failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set common mode */
    res = syn6288_set_mode(&gs_handle, SYN6288_MODE_COMMON);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set mode failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set synthesis volume 16 */
    res = syn6288_set_synthesis_volume(&gs_handle, 16);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set synthesis volume failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set background volume 16 */
    res = syn6288_set_background_volume(&gs_handle, 0);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set background volume failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set synthesis speed 5 */
    res = syn6288_set_synthesis_speed(&gs_handle, 5);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set synthesis speed failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: start synthesis test.\n");
    
    /* synthesis text test */
    syn6288_interface_debug_print("syn6288: synthesis text test.\n");
    
    /* gb2312 synthesis text */
    syn6288_interface_debug_print("syn6288: gb2312 synthesis text.\n");
    res = syn6288_set_text_type(&gs_handle, SYN6288_TYPE_GB2312);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set text type failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    
    /* synthesis text */
    res = syn6288_synthesis_text(&gs_handle, (char *)gb2312_text);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: synthesis text failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    status = SYN6288_STATUS_BUSY;
    while (status == SYN6288_STATUS_BUSY)
    {
        syn6288_interface_delay_ms(500);
        res = syn6288_get_status(&gs_handle, &status);
        if (res != 0)
        {
            syn6288_interface_debug_print("syn6288: get status failed.\n");
            (void)syn6288_deinit(&gs_handle);
            
            return 1;
        }
    }
    
    /* gbk synthesis text */
    syn6288_interface_debug_print("syn6288: gbk synthesis text.\n");
    res = syn6288_set_text_type(&gs_handle, SYN6288_TYPE_GBK);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set text type failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    
    /* synthesis text */
    res = syn6288_synthesis_text(&gs_handle, (char *)gbk_text);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: synthesis text failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    status = SYN6288_STATUS_BUSY;
    while (status == SYN6288_STATUS_BUSY)
    {
        syn6288_interface_delay_ms(500);
        res = syn6288_get_status(&gs_handle, &status);
        if (res != 0)
        {
            syn6288_interface_debug_print("syn6288: get status failed.\n");
            (void)syn6288_deinit(&gs_handle);
            
            return 1;
        }
    }
    
    /* big5 synthesis text */
    syn6288_interface_debug_print("syn6288: big5 synthesis text.\n");
    res = syn6288_set_text_type(&gs_handle, SYN6288_TYPE_BIG5);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set text type failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    
    /* synthesis text */
    res = syn6288_synthesis_text(&gs_handle, (char *)big5_text);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: synthesis text failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    status = SYN6288_STATUS_BUSY;
    while (status == SYN6288_STATUS_BUSY)
    {
        syn6288_interface_delay_ms(500);
        res = syn6288_get_status(&gs_handle, &status);
        if (res != 0)
        {
            syn6288_interface_debug_print("syn6288: get status failed.\n");
            (void)syn6288_deinit(&gs_handle);
            
            return 1;
        }
    }
    
    /* unicode synthesis text */
    syn6288_interface_debug_print("syn6288: unicode synthesis text.\n");
    res = syn6288_set_text_type(&gs_handle, SYN6288_TYPE_UNICODE);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set text type failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    
    /* synthesis text */
    res = syn6288_synthesis_text(&gs_handle, (char *)unicode_text);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: synthesis text failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    status = SYN6288_STATUS_BUSY;
    while (status == SYN6288_STATUS_BUSY)
    {
        syn6288_interface_delay_ms(500);
        res = syn6288_get_status(&gs_handle, &status);
        if (res != 0)
        {
            syn6288_interface_debug_print("syn6288: get status failed.\n");
            (void)syn6288_deinit(&gs_handle);
            
            return 1;
        }
    }
    
    /* set gb2312 synthesis text */
    res = syn6288_set_text_type(&gs_handle, SYN6288_TYPE_GB2312);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set text type failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    
    /* synthesis sound test */
    syn6288_interface_debug_print("syn6288: synthesis sound test.\n");
    res = syn6288_synthesis_sound(&gs_handle, SYN6288_SOUND_A);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: synthesis sound failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    status = SYN6288_STATUS_BUSY;
    while (status == SYN6288_STATUS_BUSY)
    {
        syn6288_interface_delay_ms(500);
        res = syn6288_get_status(&gs_handle, &status);
        if (res != 0)
        {
            syn6288_interface_debug_print("syn6288: get status failed.\n");
            (void)syn6288_deinit(&gs_handle);
            
            return 1;
        }
    }
    
    /* synthesis message test */
    syn6288_interface_debug_print("syn6288: synthesis message test.\n");
    res = syn6288_synthesis_message(&gs_handle, SYN6288_MESSAGE_A);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: synthesis message failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    status = SYN6288_STATUS_BUSY;
    while (status == SYN6288_STATUS_BUSY)
    {
        syn6288_interface_delay_ms(500);
        res = syn6288_get_status(&gs_handle, &status);
        if (res != 0)
        {
            syn6288_interface_debug_print("syn6288: get status failed.\n");
            (void)syn6288_deinit(&gs_handle);
            
            return 1;
        }
    }
    
    /* synthesis ring test */
    syn6288_interface_debug_print("syn6288: synthesis ring test.\n");
    res = syn6288_synthesis_ring(&gs_handle, SYN6288_RING_E);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: synthesis ring failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    status = SYN6288_STATUS_BUSY;
    while (status == SYN6288_STATUS_BUSY)
    {
        syn6288_interface_delay_ms(500);
        res = syn6288_get_status(&gs_handle, &status);
        if (res != 0)
        {
            syn6288_interface_debug_print("syn6288: get status failed.\n");
            (void)syn6288_deinit(&gs_handle);
            
            return 1;
        }
    }
    syn6288_interface_delay_ms(60000);
    
    /* synthesis control test */
    syn6288_interface_debug_print("syn6288: synthesis control test.\n");    
    res = syn6288_synthesis_text(&gs_handle, (char *)gb2312_text);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: synthesis text failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_delay_ms(500);
    res = syn6288_pause(&gs_handle);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: pause failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: synthesis control pause.\n");
    syn6288_interface_delay_ms(5000);
    res = syn6288_resume(&gs_handle);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: resume failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: synthesis control resume.\n");
    status = SYN6288_STATUS_BUSY;
    while (status == SYN6288_STATUS_BUSY)
    {
        syn6288_interface_delay_ms(500);
        res = syn6288_get_status(&gs_handle, &status);
        if (res != 0)
        {
            syn6288_interface_debug_print("syn6288: get status failed.\n");
            (void)syn6288_deinit(&gs_handle);
            
            return 1;
        }
    }
    res = syn6288_synthesis_text(&gs_handle, (char *)gb2312_text);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: synthesis text failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_delay_ms(500);
    res = syn6288_stop(&gs_handle);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: stop failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: synthesis control stop.\n");
    syn6288_interface_delay_ms(5000);
    
    /* synthesis volume test */
    syn6288_interface_debug_print("syn6288: synthesis volume test.\n");
    res = syn6288_set_synthesis_volume(&gs_handle, 5);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set synthesis volume failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: set synthesis volume 5.\n");
    res = syn6288_synthesis_text(&gs_handle, (char *)gb2312_text);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: synthesis text failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    status = SYN6288_STATUS_BUSY;
    while (status == SYN6288_STATUS_BUSY)
    {
        syn6288_interface_delay_ms(500);
        res = syn6288_get_status(&gs_handle, &status);
        if (res != 0)
        {
            syn6288_interface_debug_print("syn6288: get status failed.\n");
            (void)syn6288_deinit(&gs_handle);
            
            return 1;
        }
    }
    res = syn6288_set_synthesis_volume(&gs_handle, 16);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set synthesis volume failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    
    /* synthesis speed test */
    syn6288_interface_debug_print("syn6288: synthesis speed test.\n");
    res = syn6288_set_synthesis_speed(&gs_handle, 0);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set synthesis speed failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: set synthesis speed 0.\n");
    res = syn6288_synthesis_text(&gs_handle, (char *)gb2312_text);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: synthesis text failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    status = SYN6288_STATUS_BUSY;
    while (status == SYN6288_STATUS_BUSY)
    {
        syn6288_interface_delay_ms(500);
        res = syn6288_get_status(&gs_handle, &status);
        if (res != 0)
        {
            syn6288_interface_debug_print("syn6288: get status failed.\n");
            (void)syn6288_deinit(&gs_handle);
            
            return 1;
        }
    }
    res = syn6288_set_synthesis_speed(&gs_handle, 5);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set synthesis speed failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    
    /* synthesis mode test */
    syn6288_interface_debug_print("syn6288: synthesis mode test.\n");
    
    /* background mode on */
    syn6288_interface_debug_print("syn6288: background mode on.\n");
    res = syn6288_set_background_volume(&gs_handle, 15);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set background volume failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    res = syn6288_set_mode(&gs_handle, SYN6288_MODE_BACKGROUND_1);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set mode failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    res = syn6288_synthesis_text(&gs_handle, (char *)gb2312_text);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: synthesis text failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    status = SYN6288_STATUS_BUSY;
    while (status == SYN6288_STATUS_BUSY)
    {
        syn6288_interface_delay_ms(500);
        res = syn6288_get_status(&gs_handle, &status);
        if (res != 0)
        {
            syn6288_interface_debug_print("syn6288: get status failed.\n");
            (void)syn6288_deinit(&gs_handle);
            
            return 1;
        }
    }
    
    /* command test */
    syn6288_interface_debug_print("syn6288: command test.\n");
    syn6288_interface_debug_print("syn6288: set command 0.\n");
    memset(s, 0, sizeof(char) * 32);
    strncpy(s, "[b0]", 32);
    res = syn6288_set_command(&gs_handle, s);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set command failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    memset(s, 0, sizeof(char) * 32);
    strncpy(s, "110,120,130", 32);
    res = syn6288_synthesis_text(&gs_handle, s);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: synthesis text failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    status = SYN6288_STATUS_BUSY;
    while (status == SYN6288_STATUS_BUSY)
    {
        syn6288_interface_delay_ms(500);
        res = syn6288_get_status(&gs_handle, &status);
        if (res != 0)
        {
            syn6288_interface_debug_print("syn6288: get status failed.\n");
            (void)syn6288_deinit(&gs_handle);
            
            return 1;
        }
    }
    syn6288_interface_debug_print("syn6288: set command 1.\n");
    memset(s, 0, sizeof(char) * 32);
    strncpy(s, "[b1]", 32);
    res = syn6288_set_command(&gs_handle, s);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set command failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    memset(s, 0, sizeof(char) * 32);
    strncpy(s, "110,120,130", 32);
    res = syn6288_synthesis_text(&gs_handle, s);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: synthesis text failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    status = SYN6288_STATUS_BUSY;
    while (status == SYN6288_STATUS_BUSY)
    {
        syn6288_interface_delay_ms(500);
        res = syn6288_get_status(&gs_handle, &status);
        if (res != 0)
        {
            syn6288_interface_debug_print("syn6288: get status failed.\n");
            (void)syn6288_deinit(&gs_handle);
            
            return 1;
        }
    }
    
    /* finish synthesis test */
    syn6288_interface_debug_print("syn6288: finish synthesis test.\n");
    (void)syn6288_deinit(&gs_handle);
    
    return 0;
}
