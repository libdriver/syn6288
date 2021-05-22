/**
 * Copyright (C) LibDriver 2015-2021 All rights reserved
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
 * @file      main.c
 * @brief     main source file
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

#include "driver_syn6288_basic.h"
#include "driver_syn6288_advance.h"
#include "driver_syn6288_register_test.h"
#include "driver_syn6288_synthesis_test.h"
#include "uart.h"
#include <ctype.h>

/**
 * @brief     syn6288 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t syn6288(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            syn6288_info_t info;
            
            /* print syn6288 info */
            syn6288_info(&info);
            syn6288_interface_debug_print("syn6288: chip is %s.\n", info.chip_name);
            syn6288_interface_debug_print("syn6288: manufacturer is %s.\n", info.manufacturer_name);
            syn6288_interface_debug_print("syn6288: interface is %s.\n", info.interface);
            syn6288_interface_debug_print("syn6288: driver version is %d.%d.\n", info.driver_version/1000, (info.driver_version%1000)/100);
            syn6288_interface_debug_print("syn6288: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            syn6288_interface_debug_print("syn6288: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            syn6288_interface_debug_print("syn6288: max current is %0.2fmA.\n", info.max_current_ma);
            syn6288_interface_debug_print("syn6288: max temperature is %0.1fC.\n", info.temperature_max);
            syn6288_interface_debug_print("syn6288: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            syn6288_interface_debug_print("syn6288: TX connected to GPIO14(BCM).\n");
            syn6288_interface_debug_print("syn6288: RX connected to GPIO15(BCM).\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show syn6288 help */
            
            help:
            
            syn6288_interface_debug_print("syn6288 -i\n\tshow syn6288 chip and driver information.\n");
            syn6288_interface_debug_print("syn6288 -h\n\tshow syn6288 help.\n");
            syn6288_interface_debug_print("syn6288 -p\n\tshow syn6288 pin connections of the current board.\n");
            syn6288_interface_debug_print("syn6288 -t reg\n\trun syn6288 register test.\n");
            syn6288_interface_debug_print("syn6288 -t syn\n\trun syn6288 synthesis test.\n");
            syn6288_interface_debug_print("syn6288 -c syn <text>\n\trun syn6288 synthesis text function.text format is gb2312.\n");
            syn6288_interface_debug_print("syn6288 -c advance -syn <text>\n\trun syn6288 advance synthesis text function."
                                          "text format is gb2312.\n");
            syn6288_interface_debug_print("syn6288 -c advance -sound <soundtype>\n\trun syn6288 advance synthesis sound function."
                                          "soundtype can be \"A\" - \"Y\".\n");
            syn6288_interface_debug_print("syn6288 -c advance -message <messagetype>\n\trun syn6288 advance synthesis message function."
                                          "messagetype can be \"A\" - \"H\".\n");
            syn6288_interface_debug_print("syn6288 -c advance -ring <ringtype>\n\trun syn6288 advance synthesis ring function."
                                          "ringtype can be \"A\" - \"O\".\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 3)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* reg test */
            if (strcmp("reg", argv[2]) == 0)
            {
                /* run reg test */
                if (syn6288_register_test())
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
             /* reg test */
            if (strcmp("syn", argv[2]) == 0)
            {
                /* run syn test */
                if (syn6288_synthesis_test())
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 4)
    {
        /* run function */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* synthesis function */
            if (strcmp("syn", argv[2]) == 0)
            {
                volatile uint8_t res;
                
                res = syn6288_basic_init();
                if (res)
                {
                    return 1;
                }
                syn6288_interface_delay_ms(500);
                syn6288_interface_debug_print("syn6288: synthesis %s.\n", argv[3]);
                res = syn6288_basic_synthesis(argv[3]);
                if (res)
                {
                    syn6288_basic_deinit();
                    
                    return 1;
                }
                syn6288_basic_sync();
                syn6288_basic_deinit();
                
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 5)
    {
        /* run function */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* advance function */
            if (strcmp("advance", argv[2]) == 0)
            {
                if (strcmp("syn", argv[3]) == 0)
                {
                    volatile uint8_t res;
                    
                    res = syn6288_advance_init();
                    if (res)
                    {
                        return 1;
                    }
                    syn6288_interface_delay_ms(500);
                    syn6288_interface_debug_print("syn6288: synthesis %s.\n", argv[4]);
                    res = syn6288_advance_synthesis(argv[4]);
                    if (res)
                    {
                        syn6288_advance_deinit();
                        
                        return 1;
                    }
                    syn6288_advance_sync();
                    syn6288_advance_deinit();
                    
                    return 0;
                }
                else if (strcmp("sound", argv[3]) == 0)
                {
                    volatile uint8_t res;
                    
                    if ((argv[4][0]<'A') || (argv[4][0]>'Z'))
                    {
                        syn6288_interface_debug_print("syn6288: sound is invalid.\n");
                        
                        return 5;
                    }
                    res = syn6288_advance_init();
                    if (res)
                    {
                        return 1;
                    }
                    syn6288_interface_delay_ms(500);
                    syn6288_interface_debug_print("syn6288: synthesis sound %c.\n", toupper(argv[4][0]));
                    res = syn6288_advance_sound((syn6288_sound_t)(toupper(argv[4][0])));
                    if (res)
                    {
                        syn6288_advance_deinit();
                        
                        return 1;
                    }
                    syn6288_advance_sync();
                    syn6288_advance_deinit();
                    
                    return 0;
                }
                else if (strcmp("message", argv[3]) == 0)
                {
                    volatile uint8_t res;
                    
                    if ((argv[4][0]<'A') || (argv[4][0]>'H'))
                    {
                        syn6288_interface_debug_print("syn6288: message is invalid.\n");
                        
                        return 5;
                    }
                    res = syn6288_advance_init();
                    if (res)
                    {
                        return 1;
                    }
                    syn6288_interface_delay_ms(500);
                    syn6288_interface_debug_print("syn6288: synthesis message %c.\n", toupper(argv[4][0]));
                    res = syn6288_advance_message((syn6288_message_t)(toupper(argv[4][0])));
                    if (res)
                    {
                        syn6288_advance_deinit();
                        
                        return 1;
                    }
                    syn6288_advance_sync();
                    syn6288_advance_deinit();
                    
                    return 0;
                }
                else if (strcmp("ring", argv[3]) == 0)
                {
                    volatile uint8_t res;
                    
                    if ((argv[4][0]<'A') || (argv[4][0]>'O'))
                    {
                        syn6288_interface_debug_print("syn6288: ring is invalid.\n");
                        
                        return 5;
                    }
                    res = syn6288_advance_init();
                    if (res)
                    {
                        return 1;
                    }
                    syn6288_interface_delay_ms(500);
                    syn6288_interface_debug_print("syn6288: synthesis ring %c.\n", toupper(argv[4][0]));
                    res = syn6288_advance_ring((syn6288_ring_t)(toupper(argv[4][0])));
                    if (res)
                    {
                        syn6288_advance_deinit();
                        
                        return 1;
                    }
                    syn6288_advance_sync();
                    syn6288_advance_deinit();
                    
                    return 0;
                }
                /* param is invalid */
                else
                {
                    return 5;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = syn6288(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        syn6288_interface_debug_print("syn6288: run failed.\n");
    }
    else if (res == 5)
    {
        syn6288_interface_debug_print("syn6288: param is invalid.\n");
    }
    else
    {
        syn6288_interface_debug_print("syn6288: unknow status code.\n");
    }

    return 0;
}