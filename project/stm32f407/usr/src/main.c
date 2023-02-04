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
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-03-17
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/17  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_syn6288_basic.h"
#include "driver_syn6288_advance.h"
#include "driver_syn6288_register_test.h"
#include "driver_syn6288_synthesis_test.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <ctype.h>
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
volatile uint16_t g_len;   /**< uart buffer length */

/**
 * @brief     syn6288 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t syn6288(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"msg", required_argument, NULL, 1},
        {"ring", required_argument, NULL, 2},
        {"sound", required_argument, NULL, 3},
        {"text", required_argument, NULL, 4},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint8_t sound_flag = 0;
    uint8_t msg_flag = 0;
    uint8_t ring_flag = 0;
    uint8_t text_flag = 0;
    syn6288_sound_t sound = SYN6288_SOUND_A;
    syn6288_message_t msg = SYN6288_MESSAGE_A;
    syn6288_ring_t ring = SYN6288_RING_A;
    char text[129] = {0};
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* msg */
            case 1 :
            {
                /* set the msg */
                msg = (syn6288_message_t)(tolower(optarg[0]));
                msg_flag = 1;
                
                break;
            }
            
            /* ring */
            case 2 :
            {
                /* set the ring */
                ring = (syn6288_ring_t)(tolower(optarg[0]));
                ring_flag = 1;
                
                break;
            }
            
            /* sound */
            case 3 :
            {
                /* set the sound */
                sound = (syn6288_sound_t)(tolower(optarg[0]));
                sound_flag = 1;
                
                break;
            }
             
            /* text */
            case 4 :
            {
                /* set the test */
                memset(text, 0, sizeof(char) * 129);
                strncpy(text, optarg, 128);
                text_flag = 1;
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        /* run reg test */
        if (syn6288_register_test() != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("t_syn", type) == 0)
    {
        /* run syn test */
        if (syn6288_synthesis_test() != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_syn", type) == 0)
    {
        uint8_t res;
        
        /* check the flag */
        if (text_flag != 1)
        {
            return 5;
        }
        
        /* basic init */
        res = syn6288_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* delay 500ms */
        syn6288_interface_delay_ms(500);
        
        /* output */
        syn6288_interface_debug_print("syn6288: synthesis %s.\n", text);
        
        /* syn */
        res = syn6288_basic_synthesis(text);
        if (res != 0)
        {
            (void)syn6288_basic_deinit();
            
            return 1;
        }
        
        /* basic deinit */
        (void)syn6288_basic_sync();
        (void)syn6288_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_advance-syn", type) == 0)
    {
        uint8_t res;
        
        /* check the flag */
        if (text_flag != 1)
        {
            return 5;
        }

        /* advance init */
        res = syn6288_advance_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* delay 500ms */
        syn6288_interface_delay_ms(500);
        
        /* output */
        syn6288_interface_debug_print("syn6288: synthesis %s.\n", text);
        
        /* syn */
        res = syn6288_advance_synthesis(text);
        if (res != 0)
        {
            (void)syn6288_advance_deinit();
            
            return 1;
        }
        
        /* advance deinit */
        (void)syn6288_advance_sync();
        (void)syn6288_advance_deinit();
        
        return 0;
    }
    else if (strcmp("e_advance-sound", type) == 0)
    {
        uint8_t res;
        
        /* check the flag */
        if (sound_flag != 1)
        {
            return 5;
        }
        
        /* advance init */
        res = syn6288_advance_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* delay 500ms */
        syn6288_interface_delay_ms(500);
        
        /* output */
        syn6288_interface_debug_print("syn6288: synthesis sound %c.\n", sound);
        res = syn6288_advance_sound(sound);
        if (res != 0)
        {
            (void)syn6288_advance_deinit();
            
            return 1;
        }
        
        /* advance deinit */
        (void)syn6288_advance_sync();
        (void)syn6288_advance_deinit();
        
        return 0;
    }
    else if (strcmp("e_advance-msg", type) == 0)
    {
        uint8_t res;
        
        /* check the flag */
        if (msg_flag != 1)
        {
            return 5;
        }
        
        /* advance init */
        res = syn6288_advance_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* delay 500ms */
        syn6288_interface_delay_ms(500);
        
        /* output */
        syn6288_interface_debug_print("syn6288: synthesis message %c.\n", msg);
        
        /* msg */
        res = syn6288_advance_message(msg);
        if (res != 0)
        {
            (void)syn6288_advance_deinit();
            
            return 1;
        }
        
        /* advance deinit */
        (void)syn6288_advance_sync();
        (void)syn6288_advance_deinit();
        
        return 0;
    }
    else if (strcmp("e_advance-ring", type) == 0)
    {
        uint8_t res;
        
        /* check the flag */
        if (ring_flag != 1)
        {
            return 5;
        }
        
        /* advance init */
        res = syn6288_advance_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* delay 500ms */
        syn6288_interface_delay_ms(500);
        
        /* output */
        syn6288_interface_debug_print("syn6288: synthesis ring %c.\n", ring);
        
        /* ring */
        res = syn6288_advance_ring(ring);
        if (res != 0)
        {
            (void)syn6288_advance_deinit();
            
            return 1;
        }
        
        /* advance deinit */
        (void)syn6288_advance_sync();
        (void)syn6288_advance_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        syn6288_interface_debug_print("Usage:\n");
        syn6288_interface_debug_print("  syn6288 (-i | --information)\n");
        syn6288_interface_debug_print("  syn6288 (-h | --help)\n");
        syn6288_interface_debug_print("  syn6288 (-p | --port)\n");
        syn6288_interface_debug_print("  syn6288 (-t reg | --test=reg)\n");
        syn6288_interface_debug_print("  syn6288 (-t syn | --test=syn)\n");
        syn6288_interface_debug_print("  syn6288 (-e syn | --example=syn) --text=<gb2312>\n");
        syn6288_interface_debug_print("  syn6288 (-e advance-syn | --example=advance-syn) --text=<gb2312>\n");
        syn6288_interface_debug_print("  syn6288 (-e advance-sound | --example=advance-sound) --sound=<type>\n");
        syn6288_interface_debug_print("  syn6288 (-e advance-msg | --example=advance-msg) --msg=<type>\n");
        syn6288_interface_debug_print("  syn6288 (-e advance-ring | --example=advance-ring) --ring=<type>\n");
        syn6288_interface_debug_print("\n");
        syn6288_interface_debug_print("Options:\n");
        syn6288_interface_debug_print("  -e <syn | advance-syn | advance-sound | advance-msg | advance-ring>, --example=<syn\n");
        syn6288_interface_debug_print("     | advance-syn | advance-sound | advance-msg | advance-ring>\n");
        syn6288_interface_debug_print("                          Run the driver example.\n");
        syn6288_interface_debug_print("  -h, --help              Show the help.\n");
        syn6288_interface_debug_print("  -i, --information       Show the chip information.\n");
        syn6288_interface_debug_print("      --msg=<type>        Set the synthesis message and type can be \"A\" - \"H\".\n");
        syn6288_interface_debug_print("  -p, --port              Display the pin connections of the current board.\n");
        syn6288_interface_debug_print("      --ring=<type>       Set the synthesis ring and type can be \"A\" - \"O\".\n");
        syn6288_interface_debug_print("      --sound=<type>      Set the synthesis sound and type can be \"A\" - \"Y\".\n");
        syn6288_interface_debug_print("  -t <reg | syn>, --test=<reg | syn>\n");
        syn6288_interface_debug_print("                          Run the driver test.\n");
        syn6288_interface_debug_print("      --text=<gb2312>     Set the synthesis text and it's format is GB2312.\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        syn6288_info_t info;
        
        /* print syn6288 info */
        syn6288_info(&info);
        syn6288_interface_debug_print("syn6288: chip is %s.\n", info.chip_name);
        syn6288_interface_debug_print("syn6288: manufacturer is %s.\n", info.manufacturer_name);
        syn6288_interface_debug_print("syn6288: interface is %s.\n", info.interface);
        syn6288_interface_debug_print("syn6288: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        syn6288_interface_debug_print("syn6288: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        syn6288_interface_debug_print("syn6288: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        syn6288_interface_debug_print("syn6288: max current is %0.2fmA.\n", info.max_current_ma);
        syn6288_interface_debug_print("syn6288: max temperature is %0.1fC.\n", info.temperature_max);
        syn6288_interface_debug_print("syn6288: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        syn6288_interface_debug_print("syn6288: TX connected to GPIOA PIN3.\n");
        syn6288_interface_debug_print("syn6288: RX connected to GPIOA PIN2.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register syn6288 function */
    shell_init();
    shell_register("syn6288", syn6288);
    uart_print("syn6288: welcome to libdriver syn6288.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("syn6288: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("syn6288: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("syn6288: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("syn6288: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("syn6288: param is invalid.\n");
            }
            else
            {
                uart_print("syn6288: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
