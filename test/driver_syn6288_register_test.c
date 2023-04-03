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
 * @file      driver_syn6288_register_test.c
 * @brief     driver syn6288 register test source file
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

#include "driver_syn6288_register_test.h"

static syn6288_handle_t gs_handle;        /**< syn6288 handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t syn6288_register_test(void)
{
    uint8_t res;
    uint8_t volume;
    uint8_t speed;
    char s[32];
    syn6288_baud_rate_t rate;
    syn6288_mode_t mode;
    syn6288_info_t info;
    syn6288_type_t type;
    
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
    
    /* start register test */
    syn6288_interface_debug_print("syn6288: start register test.\n");
    
    /* syn6288_set_baud_rate/syn6288_get_baud_rate test */
    syn6288_interface_debug_print("syn6288: syn6288_set_baud_rate/syn6288_get_baud_rate test.\n");
    res = syn6288_set_baud_rate(&gs_handle, SYN6288_BAUD_RATE_9600_BPS);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set baud rate failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set 9600 bps */
    syn6288_interface_debug_print("syn6288: set 9600 bps.\n");
    res = syn6288_get_baud_rate(&gs_handle, &rate);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: get baud rate failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: check baud rate %s.\n", rate==SYN6288_BAUD_RATE_9600_BPS?"ok":"error");
    
    /* syn6288_set_mode/syn6288_get_mode test */
    syn6288_interface_debug_print("syn6288: syn6288_set_mode/syn6288_get_mode test.\n");
    res = syn6288_set_mode(&gs_handle, SYN6288_MODE_BACKGROUND_15);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set mode failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: set background_15 mode.\n");
    res = syn6288_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: get mode failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: check mode %s.\n", mode==SYN6288_MODE_BACKGROUND_15?"ok":"error");
    
    /* syn6288_set_text_type/syn6288_get_text_type test */
    syn6288_interface_debug_print("syn6288: syn6288_set_text_type/syn6288_get_text_type test.\n");
    
    /* set GB2312 */
    res = syn6288_set_text_type(&gs_handle, SYN6288_TYPE_GB2312);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set text type failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: set gb2312 text type.\n");
    res = syn6288_get_text_type(&gs_handle, &type);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: get text type failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: check text type %s.\n", type==SYN6288_TYPE_GB2312?"ok":"error");
    
    /* set GBK */
    res = syn6288_set_text_type(&gs_handle, SYN6288_TYPE_GBK);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set text type failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: set gbk text type.\n");
    res = syn6288_get_text_type(&gs_handle, &type);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: get text type failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: check text type %s.\n", type==SYN6288_TYPE_GBK?"ok":"error");
    
    /* set BIG5 */
    res = syn6288_set_text_type(&gs_handle, SYN6288_TYPE_BIG5);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set text type failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: set big5 text type.\n");
    res = syn6288_get_text_type(&gs_handle, &type);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: get text type failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: check text type %s.\n", type==SYN6288_TYPE_BIG5?"ok":"error");
    
    /* set UNICODE */
    res = syn6288_set_text_type(&gs_handle, SYN6288_TYPE_UNICODE);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set text type failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: set unicode text type.\n");
    res = syn6288_get_text_type(&gs_handle, &type);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: get text type failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: check text type %s.\n", type==SYN6288_TYPE_UNICODE?"ok":"error");
    
    /* syn6288_set_synthesis_volume/syn6288_get_synthesis_volume test */
    syn6288_interface_debug_print("syn6288: syn6288_set_synthesis_volume/syn6288_get_synthesis_volume test.\n");
    res = syn6288_set_synthesis_volume(&gs_handle, 6);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set synthesis volume failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: set synthesis volume 6.\n");
    res = syn6288_get_synthesis_volume(&gs_handle, (uint8_t *)&volume);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: get synthesis volume failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: check synthesis volume %s.\n", volume==6?"ok":"error");
    
    /* syn6288_set_background_volume/syn6288_get_background_volume test */
    syn6288_interface_debug_print("syn6288: syn6288_set_background_volume/syn6288_get_background_volume test.\n");
    res = syn6288_set_background_volume(&gs_handle, 8);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set background volume failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: set background volume 8.\n");
    res = syn6288_get_background_volume(&gs_handle, (uint8_t *)&volume);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: get background volume failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: check background volume %s.\n", volume==8?"ok":"error");
    
    /* syn6288_set_synthesis_speed/syn6288_get_synthesis_speed test */
    syn6288_interface_debug_print("syn6288: syn6288_set_synthesis_speed/syn6288_get_synthesis_speed test.\n");
    res = syn6288_set_synthesis_speed(&gs_handle, 3);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set synthesis speed failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: set synthesis speed 3.\n");
    res = syn6288_get_synthesis_speed(&gs_handle, (uint8_t *)&speed);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: get synthesis speed failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: check synthesis speed %s.\n", speed==3?"ok":"error");
    
    /* syn6288_set_command test */
    syn6288_interface_debug_print("syn6288: syn6288_set_command test.\n");
    memset(s, 0, sizeof(char) * 32);
    strncpy(s, "[y1]", 32);
    res = syn6288_set_command(&gs_handle, s);
    if (res != 0)
    {
        syn6288_interface_debug_print("syn6288: set command failed.\n");
        (void)syn6288_deinit(&gs_handle);
        
        return 1;
    }
    syn6288_interface_debug_print("syn6288: check command %s.\n", res==0?"ok":"error");
    
    /* finish register test */
    syn6288_interface_debug_print("syn6288: finish register test.\n");
    (void)syn6288_deinit(&gs_handle);

    return 0;
}
