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
 * @file      driver_syn6288.c
 * @brief     driver syn6288 source file
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

#include "driver_syn6288.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "YuToneWorld SYN6288"        /**< chip name */
#define MANUFACTURER_NAME         "YuToneWorld"                /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.4f                         /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.1f                         /**< chip max supply voltage */
#define MAX_CURRENT               280.0f                       /**< chip max current */
#define TEMPERATURE_MIN           -35.0f                       /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                        /**< chip max operating temperature */
#define DRIVER_VERSION            2000                         /**< driver version */

/**
 * @brief     initialize the chip
 * @param[in] *handle points to a syn6288 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 uart initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t syn6288_init(syn6288_handle_t *handle)
{
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->debug_print == NULL)                                   /* check debug_print */
    {
        return 3;                                                      /* return error */
    }
    if (handle->uart_init == NULL)                                     /* check uart_init */
    {
        handle->debug_print("syn6288: uart_init is null.\n");          /* uart_init is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->uart_deinit == NULL)                                   /* check uart_deinit */
    {
        handle->debug_print("syn6288: uart_deinit is null.\n");        /* uart_deinit is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->uart_read == NULL)                                     /* check uart_read */
    {
        handle->debug_print("syn6288: uart_read is null.\n");          /* uart_read is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->uart_write == NULL)                                    /* check uart_write */
    {
        handle->debug_print("syn6288: uart_write is null.\n");         /* uart_write is null */
        
        return 3;                                                      /* return error */
    } 
    if (handle->uart_flush == NULL)                                    /* check uart_flush */
    {
        handle->debug_print("syn6288: uart_flush is null.\n");         /* uart_flush is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->delay_ms == NULL)                                      /* check delay_ms */
    {
        handle->debug_print("syn6288: delay_ms is null.\n");           /* delay_ms is null */
        
        return 3;                                                      /* return error */
    }

    if (handle->uart_init() != 0)                                      /* uart init */
    {
        handle->debug_print("syn6288: uart init failed.\n");           /* uart init failed */
        
        return 1;                                                      /* return error */
    }
    handle->inited = 1;                                                /* flag finish initialization */
    
    return 0;                                                          /* success return 0 */
}

/**
 * @brief     close the chip
 * @param[in] *handle points to a syn6288 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 uart deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t syn6288_deinit(syn6288_handle_t *handle)
{
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (handle->uart_deinit() != 0)                                   /* uart deinit */
    {
        handle->debug_print("syn6288: uart deinit failed.\n");        /* uart deinit failed */
        
        return 1;                                                     /* return error */
    }         
    handle->inited = 0;                                               /* flag close */
    
    return 0;                                                         /* success return 0 */  
}

/**
 * @brief      get the current status
 * @param[in]  *handle points to a syn6288 handle structure
 * @param[out] *status points to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t syn6288_get_status(syn6288_handle_t *handle, syn6288_status_t *status)
{
    uint8_t res;
    uint8_t times = 3;
    uint16_t len;
    uint8_t temp[2];
    uint8_t cmd[5];
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    cmd[0] = 0xFD;                                                            /* frame header */
    cmd[1] = 0x00;                                                            /* length msb */
    cmd[2] = 0x02;                                                            /* length lsb */
    cmd[3] = 0x21;                                                            /* command */
    cmd[4] = 0xDE;                                                            /* xor */
    while (1)                                                                 /* loop */
    {
        res = handle->uart_flush();                                           /* uart flush */
        if (res != 0)                                                         /* check result */
        {
            handle->debug_print("syn6288: uart flush failed.\n");             /* uart flush failed */
            
            return 1;                                                         /* return error */
        }
        res = handle->uart_write((uint8_t *)cmd, 5);                          /* uart write */
        if (res != 0)                                                         /* check result */
        {
            handle->debug_print("syn6288: uart write failed.\n");             /* uart write failed */
            
            return 1;                                                         /* return error */
        }
        handle->delay_ms(100);                                                /* delay 100 ms */
        memset(temp, 0, sizeof(uint8_t) * 2);                                 /* clear the buffer */
        len = handle->uart_read((uint8_t *)temp, 2);                          /* uart read */
        if (len != 2)                                                         /* check result */
        {
            handle->debug_print("syn6288: uart read failed.\n");              /* uart read failed */
            
            return 1;                                                         /* return error */
        }
        if ((temp[0] == 0x41) && (temp[1] == 0x4F))                           /* check frame */
        {
            *status = (syn6288_status_t)(0);                                  /* set status */
            
            return 0;                                                         /* success return 0 */
        }
        else if ((temp[0] == 0x41) && (temp[1] == 0x4E))                      /* check frame */
        {
            *status = (syn6288_status_t)(1);                                  /* set status */
            
            return 0;                                                         /* success return 0 */
        }
        else
        {
            if (times != 0)                                                   /* check times */
            {
                times--;                                                      /* retry times-- */
                handle->delay_ms(100);                                        /* delay 100 ms */
                
                continue;                                                     /* continue */
            }
            handle->debug_print("syn6288: command receive failed.\n");        /* command receive failed */
            
            return 1;                                                         /* return error */
        }
    }
}

/**
 * @brief     stop the chip
 * @param[in] *handle points to a syn6288 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 stop failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t syn6288_stop(syn6288_handle_t *handle)
{
    uint8_t res;
    uint16_t len;
    uint8_t temp;
    uint8_t cmd[5];
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    cmd[0] = 0xFD;                                                         /* frame header */
    cmd[1] = 0x00;                                                         /* length msb */
    cmd[2] = 0x02;                                                         /* length lsb */
    cmd[3] = 0x02;                                                         /* command */
    cmd[4] = 0xFD;                                                         /* xor */
    res = handle->uart_flush();                                            /* uart flush */
    if (res != 0)                                                          /* check result */
    {
        handle->debug_print("syn6288: uart flush failed.\n");              /* uart flush failed */
        
        return 1;                                                          /* return error */
    }
    res = handle->uart_write((uint8_t *)cmd, 5);                           /* uart write */
    if (res != 0)                                                          /* check result */
    {
        handle->debug_print("syn6288: uart write failed.\n");              /* uart write failed */
        
        return 1;                                                          /* return error */
    }
    handle->delay_ms(100);                                                 /* delay 100 ms */
    len = handle->uart_read((uint8_t *)&temp, 1);                          /* uart read */
    if (len != 1)                                                          /* check result */
    {
        handle->debug_print("syn6288: uart read failed.\n");               /* uart read failed */
        
        return 1;                                                          /* return error */
    }
    if (temp == 0x41)                                                      /* check return */
    {
        return 0;                                                          /* success return 0 */
    }
    else
    {
        handle->debug_print("syn6288: command receive failed.\n");         /* command receive failed */
        
        return 1;                                                          /* return error */
    }
}

/**
 * @brief     pause the chip
 * @param[in] *handle points to a syn6288 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 pause failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t syn6288_pause(syn6288_handle_t *handle)
{
    uint8_t res;
    uint16_t len;
    uint8_t temp;
    uint8_t cmd[5];
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    cmd[0] = 0xFD;                                                        /* frame header */
    cmd[1] = 0x00;                                                        /* length msb */
    cmd[2] = 0x02;                                                        /* length lsb */
    cmd[3] = 0x03;                                                        /* command */
    cmd[4] = 0xFC;                                                        /* xor */
    res = handle->uart_flush();                                           /* uart flush */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart flush failed.\n");             /* uart flush failed */
        
        return 1;                                                         /* return error */
    }
    res = handle->uart_write((uint8_t *)cmd, 5);                          /* uart write */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart write failed.\n");             /* uart write failed */
        
        return 1;                                                         /* return error */
    }
    handle->delay_ms(100);                                                /* delay 100 ms */
    len = handle->uart_read((uint8_t *)&temp, 1);                         /* uart read */
    if (len != 1)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart read failed.\n");              /* uart read failed */
        
        return 1;                                                         /* return error */
    }
    if (temp == 0x41)                                                     /* check return */
    {
        return 0;                                                         /* success return 0 */
    }
    else
    {
        handle->debug_print("syn6288: command receive failed.\n");        /* command receive failed */
        
        return 1;                                                         /* return error */
    }
}

/**
 * @brief     resume the chip
 * @param[in] *handle points to a syn6288 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 resume failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t syn6288_resume(syn6288_handle_t *handle)
{
    uint8_t res;
    uint16_t len;
    uint8_t temp;
    uint8_t cmd[5];
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    cmd[0] = 0xFD;                                                        /* frame header */
    cmd[1] = 0x00;                                                        /* length msb */
    cmd[2] = 0x02;                                                        /* length lsb */
    cmd[3] = 0x04;                                                        /* command */
    cmd[4] = 0xFB;                                                        /* xor */
    res = handle->uart_flush();                                           /* uart flush */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart flush failed.\n");             /* uart flush failed */
        
        return 1;                                                         /* return error */
    }
    res = handle->uart_write((uint8_t *)cmd, 5);                          /* uart write */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart write failed.\n");             /* uart write failed */
        
        return 1;                                                         /* return error */
    }
    handle->delay_ms(100);                                                /* delay 100 ms */
    len = handle->uart_read((uint8_t *)&temp, 1);                         /* uart read */
    if (len != 1)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart read failed.\n");              /* uart read failed */
        
        return 1;                                                         /* return error */
    }
    if (temp == 0x41)                                                     /* check return */
    {
        return 0;                                                         /* success return 0 */
    }
    else
    {
        handle->debug_print("syn6288: command receive failed.\n");        /* command receive failed */
        
        return 1;                                                         /* return error */
    }
}

/**
 * @brief     power down the chip
 * @param[in] *handle points to a syn6288 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 power down failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t syn6288_power_down(syn6288_handle_t *handle)
{
    uint8_t res;
    uint16_t len;
    uint8_t temp;
    uint8_t cmd[5];
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    cmd[0] = 0xFD;                                                        /* frame header */
    cmd[1] = 0x00;                                                        /* length msb */
    cmd[2] = 0x02;                                                        /* length lsb */
    cmd[3] = 0x88;                                                        /* command */
    cmd[4] = 0x77;                                                        /* xor */
    res = handle->uart_flush();                                           /* uart flush */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart flush failed.\n");             /* uart flush failed */
        
        return 1;                                                         /* return error */
    }
    res = handle->uart_write((uint8_t *)cmd, 5);                          /* uart write */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart write failed.\n");             /* uart write failed */
        
        return 1;                                                         /* return error */
    }
    handle->delay_ms(100);                                                /* delay 100 ms */
    len = handle->uart_read((uint8_t *)&temp, 1);                         /* uart read */
    if (len != 1)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart read failed.\n");              /* uart read failed */
        
        return 1;                                                         /* return error */
    }
    if (temp == 0x41)                                                     /* check return */
    {
        return 0;                                                         /* success return 0 */
    }
    else
    {
        handle->debug_print("syn6288: command receive failed.\n");        /* command receive failed */
        
        return 1;                                                         /* return error */
    }
}

/**
 * @brief     set the baud rate
 * @param[in] *handle points to a syn6288 handle structure
 * @param[in] rate is the baud rate
 * @return    status code
 *            - 0 success
 *            - 1 set baud rate failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t syn6288_set_baud_rate(syn6288_handle_t *handle, syn6288_baud_rate_t rate)
{
    uint8_t res;
    uint16_t len;
    uint8_t temp;
    uint8_t cmd[6];
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    cmd[0] = 0xFD;                                                        /* frame header */
    cmd[1] = 0x00;                                                        /* length msb */
    cmd[2] = 0x03;                                                        /* length lsb */
    cmd[3] = 0x31;                                                        /* command */
    switch (rate)                                                         /* check rate */
    {
        case SYN6288_BAUD_RATE_9600_BPS :                                 /* 9600 */
        {
            handle->rate = rate;                                          /* set rate */
            cmd[4] = 0x00;                                                /* baud rate */
            cmd[5] = 0xCF;                                                /* xor */
            
            break;                                                        /* break */
        }
        case SYN6288_BAUD_RATE_19200_BPS :                                /* 19200 */
        {
            handle->rate = rate;                                          /* set rate */
            cmd[4] = 0x01;                                                /* baud rate */
            cmd[5] = 0xCE;                                                /* xor */
            
            break;                                                        /* break */
        }
        case SYN6288_BAUD_RATE_38400_BPS :                                /* 38400 */
        {
            handle->rate = rate;                                          /* set rate */
            cmd[4] = 0x02;                                                /* baud rate */
            cmd[5] = 0xCD;                                                /* xor */
            
            break;                                                        /* break */
        }
        default :
        {
            handle->rate = rate;                                          /* set rate */
            cmd[4] = 0x00;                                                /* baud rate */
            cmd[5] = 0xCF;                                                /* xor */
            
            break;                                                        /* break */
        }
    }
    res = handle->uart_flush();                                           /* uart flush */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart flush failed.\n");             /* uart flush failed */
            
        return 1;                                                         /* return error */
    }
    res = handle->uart_write((uint8_t *)cmd, 6);                          /* uart write */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart write failed.\n");             /* uart write failed */
        
        return 1;                                                         /* return error */
    }
    handle->delay_ms(100);                                                /* delay 100 ms */
    len = handle->uart_read((uint8_t *)&temp, 1);                         /* uart read */
    if (len != 1)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart read failed.\n");              /* uart read failed */
        
        return 1;                                                         /* return error */
    }
    if (temp == 0x41)                                                     /* check return */
    {
        return 0;                                                         /* success return 0 */
    }
    else
    {
        handle->debug_print("syn6288: command receive failed.\n");        /* command receive failed */
        
        return 1;                                                         /* return error */
    }
}

/**
 * @brief      get the baud rate
 * @param[in]  *handle points to a syn6288 handle structure
 * @param[out] *rate points to a baud rate buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t syn6288_get_baud_rate(syn6288_handle_t *handle, syn6288_baud_rate_t *rate)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    }
    
    *rate = (syn6288_baud_rate_t)(handle->rate);        /* get baud rate */
    
    return 0;                                           /* success return 0 */
}

/**
 * @brief     set the chip mode
 * @param[in] *handle points to a syn6288 handle structure
 * @param[in] mode is the chip mode
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t syn6288_set_mode(syn6288_handle_t *handle, syn6288_mode_t mode)
{
    if (handle == NULL)             /* check handle */
    {
        return 2;                   /* return error */
    }
    if (handle->inited != 1)        /* check handle initialization */
    {
        return 3;                   /* return error */
    }
    
    handle->mode = (uint8_t)mode;   /* set mode */
    
    return 0;                       /* success return 0 */
}

/**
 * @brief      get the chip mode
 * @param[in]  *handle points to a syn6288 handle structure
 * @param[out] *mode points to a chip mode buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t syn6288_get_mode(syn6288_handle_t *handle, syn6288_mode_t *mode)
{
    if (handle == NULL)                            /* check handle */
    {
        return 2;                                  /* return error */
    }
    if (handle->inited != 1)                       /* check handle initialization */
    {
        return 3;                                  /* return error */
    }
    
    *mode = (syn6288_mode_t)(handle->mode);        /* get mode */
    
    return 0;                                      /* success return 0 */
}

/**
 * @brief     set the chip text type
 * @param[in] *handle points to a syn6288 handle structure
 * @param[in] type is the chip text type
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t syn6288_set_text_type(syn6288_handle_t *handle, syn6288_type_t type)
{
    if (handle == NULL)             /* check handle */
    {
        return 2;                   /* return error */
    }
    if (handle->inited != 1)        /* check handle initialization */
    {
        return 3;                   /* return error */
    }
    
    handle->type = (uint8_t)type;   /* set type */
    
    return 0;                       /* success return 0 */
}

/**
 * @brief      get the chip text type
 * @param[in]  *handle points to a syn6288 handle structure
 * @param[out] *type points to a chip text type
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t syn6288_get_text_type(syn6288_handle_t *handle, syn6288_type_t *type)
{
    if (handle == NULL)                            /* check handle */
    {
        return 2;                                  /* return error */
    }
    if (handle->inited != 1)                       /* check handle initialization */
    {
        return 3;                                  /* return error */
    }
    
    *type = (syn6288_type_t)(handle->type);        /* get type */
    
    return 0;                                      /* success return 0 */
}

/**
 * @brief     synthesis the sound
 * @param[in] *handle points to a syn6288 handle structure
 * @param[in] sound is the sound type
 * @return    status code
 *            - 0 success
 *            - 1 synthesis sound failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t syn6288_synthesis_sound(syn6288_handle_t *handle, syn6288_sound_t sound)
{
    uint8_t res;
    uint16_t len;
    uint8_t temp;
    uint8_t i;
    uint8_t xor_cal = 0;
    char cmd[6];
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    cmd[0] = 's';                                                         /* set 's' */
    cmd[1] = 'o';                                                         /* set 'o' */
    cmd[2] = 'u';                                                         /* set 'u' */
    cmd[3] = 'n';                                                         /* set 'n' */
    cmd[4] = 'd';                                                         /* set 'd' */
    cmd[5] = sound;                                                       /* set sound number */
    handle->buf[0] = 0xFD;                                                /* frame header */
    handle->buf[1] = (6 + 3) / 256;                                       /* length msb */
    handle->buf[2] = (6 + 3) % 256;                                       /* length lsb */
    handle->buf[3] = 0x01;                                                /* command */
    handle->buf[4] = 0x00;                                                /* command param */
    strncpy((char *)&handle->buf[5],(char *)cmd, 6);                      /* copy text */
    for (i = 0; i < 6 + 5; i++)
    {
        xor_cal ^= handle->buf[i];                                        /* calculate xor */
    }
    handle->buf[6+5] = xor_cal;                                           /* set xor */
    res = handle->uart_flush();                                           /* uart flush */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart flush failed.\n");             /* uart flush failed */
        
        return 1;                                                         /* return error */
    }
    res = handle->uart_write((uint8_t *)handle->buf, 6+6);                /* uart write */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart write failed.\n");             /* uart write failed */
        
        return 1;                                                         /* return error */
    }
    handle->delay_ms(100);                                                /* delay 100 ms */
    len = handle->uart_read((uint8_t *)&temp, 1);                         /* uart read */
    if (len != 1)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart read failed.\n");              /* uart read failed */
        
        return 1;                                                         /* return error */
    }
    if (temp == 0x41)                                                     /* check return */
    {
        return 0;                                                         /* success return 0 */
    }
    else
    {
        handle->debug_print("syn6288: command receive failed.\n");        /* command receive failed */
       
        return 1;                                                         /* return error */
    }
}

/**
 * @brief     synthesis the message
 * @param[in] *handle points to a syn6288 handle structure
 * @param[in] message is the message type
 * @return    status code
 *            - 0 success
 *            - 1 synthesis message failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t syn6288_synthesis_message(syn6288_handle_t *handle, syn6288_message_t message)
{
    uint8_t res;
    uint16_t len;
    uint8_t temp;
    uint8_t i;
    uint8_t xor_cal = 0;
    char cmd[4];
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    cmd[0] = 'm';                                                         /* set 'm' */
    cmd[1] = 's';                                                         /* set 's' */
    cmd[2] = 'g';                                                         /* set 'g' */
    cmd[3] = message;                                                     /* set message number */
    handle->buf[0] = 0xFD;                                                /* frame header */
    handle->buf[1] = (4 + 3) / 256;                                       /* length msb */
    handle->buf[2] = (4 + 3) % 256;                                       /* length lsb */
    handle->buf[3] = 0x01;                                                /* command */
    handle->buf[4] = 0x00;                                                /* command param */
    strncpy((char *)&handle->buf[5], (char *)cmd, 4);                     /* copy text */
    for (i = 0; i < 4 + 5; i++)
    {
        xor_cal ^= handle->buf[i];                                        /* calculate xor */
    } 
    handle->buf[4+5] = xor_cal;                                           /* set xor */
    res = handle->uart_flush();                                           /* uart flush */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart flush failed.\n");             /* uart flush failed */
        
        return 1;                                                         /* return error */
    }
    res = handle->uart_write((uint8_t *)handle->buf, 6 + 4);              /* uart write */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart write failed.\n");             /* uart write failed */
        
        return 1;                                                         /* return error */
    }
    handle->delay_ms(100);                                                /* delay 100 ms */
    len = handle->uart_read((uint8_t *)&temp, 1);                         /* uart read  */
    if (len != 1)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart read failed.\n");              /* uart read failed */
        
        return 1;                                                         /* return error */
    }
    if (temp == 0x41)                                                     /* check return */
    {
        return 0;                                                         /* success return 0 */
    }
    else
    {
        handle->debug_print("syn6288: command receive failed.\n");        /* command receive failed */
        
        return 1;                                                         /* return error */
    }
}

/**
 * @brief     synthesis the ring
 * @param[in] *handle points to a syn6288 handle structure
 * @param[in] ring is the ring type
 * @return    status code
 *            - 0 success
 *            - 1 synthesis ring failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t syn6288_synthesis_ring(syn6288_handle_t *handle, syn6288_ring_t ring)
{
    uint8_t res;
    uint16_t len;
    uint8_t temp;
    uint8_t i;
    uint8_t xor_cal = 0;
    char cmd[5];
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    cmd[0] = 'r';                                                         /* set 'r' */
    cmd[1] = 'i';                                                         /* set 'i' */
    cmd[2] = 'n';                                                         /* set 'n' */
    cmd[3] = 'g';                                                         /* set 'g' */
    cmd[4] = ring;                                                        /* set ring number */
    handle->buf[0] = 0xFD;                                                /* frame header */
    handle->buf[1] = (5 + 3) / 256;                                       /* length msb */
    handle->buf[2] = (5 + 3) % 256;                                       /* length lsb */
    handle->buf[3] = 0x01;                                                /* command */
    handle->buf[4] = 0x00;                                                /* command param */
    strncpy((char *)&handle->buf[5],(char *)cmd, 5);                      /* copy text */
    for (i = 0; i < 5 + 5; i++)
    {
        xor_cal ^= handle->buf[i];                                        /* calculate xor */
    }
    handle->buf[5+5] = xor_cal;                                           /* set xor */
    res = handle->uart_flush();                                           /* uart flush */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart flush failed.\n");             /* uart flush failed */
       
        return 1;                                                         /* return error */
    }
    res = handle->uart_write((uint8_t *)handle->buf, 6+5);                /* uart write */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart write failed.\n");             /* uart write failed */
        
        return 1;                                                         /* return error */
    }
    handle->delay_ms(100);                                                /* delay 100 ms */
    len = handle->uart_read((uint8_t *)&temp, 1);                         /* uart read */
    if (len != 1)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart read failed.\n");              /* uart read failed */
        
        return 1;                                                         /* return error */
    }
    if (temp == 0x41)                                                     /* check return */
    {
        return 0;                                                         /* success return 0 */
    }
    else
    {
        handle->debug_print("syn6288: command receive failed.\n");        /* command receive failed */
        
        return 1;                                                         /* return error */
    }
}

/**
 * @brief     synthesis the test
 * @param[in] *handle points to a syn6288 handle structure
 * @param[in] *text points to a test buffer
 * @return    status code
 *            - 0 success
 *            - 1 synthesis text failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t syn6288_synthesis_text(syn6288_handle_t *handle, char *text)
{
    uint8_t res;
    uint16_t l;
    uint8_t len, temp;
    uint8_t i;
    uint8_t xor_cal = 0;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    len = (uint8_t)strlen(text);                                          /* get length of text */
    if (len > 200)                                                        /* check length */
    {
        handle->debug_print("syn6288: text is too long.\n");              /* text is too long */
        
        return 1;                                                         /* return error */
    }
    handle->buf[0] = 0xFD;                                                /* frame header */
    handle->buf[1] = (uint8_t)((len + 3) / 256);                          /* length msb */
    handle->buf[2] = (len + 3) % 256;                                     /* length lsb */
    handle->buf[3] = 0x01;                                                /* command */
    handle->buf[4] = handle->mode|handle->type;                           /* command param */
    strncpy((char *)&handle->buf[5], text, len);                          /* copy text */
    for (i = 0; i < len + 5; i++)
    {
        xor_cal ^= handle->buf[i];                                        /* calculate xor */
    }
    handle->buf[len+5] = xor_cal;                                         /* set xor */
    res = handle->uart_flush();                                           /* uart flush */ 
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart flush failed.\n");             /* uart flush failed */
        
        return 1;                                                         /* return error */
    }
    res = handle->uart_write((uint8_t *)handle->buf, len+6);              /* uart write */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart write failed.\n");             /* uart write failed */
        
        return 1;                                                         /* return error */
    }
    handle->delay_ms(100);                                                /* delay 100 ms */
    l = handle->uart_read((uint8_t *)&temp, 1);                           /* uart read */
    if (l != 1)                                                           /* check result */
    {
        handle->debug_print("syn6288: uart read failed.\n");              /* uart read failed */
        
        return 1;                                                         /* return error */
    }
    if (temp == 0x41)                                                     /* check return */
    {
        return 0;                                                         /* success return 0 */
    }
    else
    {
        handle->debug_print("syn6288: command receive failed.\n");        /* command receive failed */
       
        return 1;                                                         /* return error */
    }
}

/**
 * @brief     set the chip synthesis volume
 * @param[in] *handle points to a syn6288 handle structure
 * @param[in] volume is the synthesis volume
 * @return    status code
 *            - 0 success
 *            - 1 set synthesis volume failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t syn6288_set_synthesis_volume(syn6288_handle_t *handle, uint8_t volume)
{
    char cmd[8];
    
    if (volume > 16)                                              /* check volume */
    {
        handle->debug_print("syn6288: volume invalid.\n");        /* volume invalid */
        
        return 1;                                                 /* return error */
    }
    
    memset((char *)cmd, 0, sizeof(char)*8);                       /* memory set 0 */
    (void)snprintf((char *)cmd, 8, "v[%d]", (int16_t)volume);     /* set command */
    handle->volume = volume;                                      /* save volume */
    
    return syn6288_set_command(handle, (char *)cmd);              /* write command */
}

/**
 * @brief      get the chip synthesis volume
 * @param[in]  *handle points to a syn6288 handle structure
 * @param[out] *volume points to a synthesis volume buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t syn6288_get_synthesis_volume(syn6288_handle_t *handle, uint8_t *volume)
{
    if (handle == NULL)              /* check handle */
    {
        return 2;                    /* return error */
    }
    if (handle->inited != 1)         /* check handle initialization */
    {
        return 3;                    /* return error */
    }
    
    *volume = handle->volume;        /* get volume */
    
    return 0;                        /* success return 0 */
}

/**
 * @brief     set the synthesis background volume
 * @param[in] *handle points to a syn6288 handle structure
 * @param[in] volume is the background volume
 * @return    status code
 *            - 0 success
 *            - 1 set background volume failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t syn6288_set_background_volume(syn6288_handle_t *handle, uint8_t volume)
{
    char cmd[8];
    
    if (volume > 16)                                              /* check volume */
    {
        handle->debug_print("syn6288: volume is invalid.\n");     /* volume is invalid */
       
        return 1;                                                 /* return error */
    }
    
    memset((char *)cmd, 0, sizeof(char)*8);                       /* memory set 0 */
    (void)snprintf((char *)cmd, 8, "m[%d]", (int16_t)volume);     /* set command */
    handle->background_volume = volume;                           /* save volume */

    return syn6288_set_command(handle, (char *)cmd);              /* write command */
}

/**
 * @brief      get the chip synthesis background volume
 * @param[in]  *handle points to a syn6288 handle structure
 * @param[out] *volume points to a synthesis background volume buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t syn6288_get_background_volume(syn6288_handle_t *handle, uint8_t *volume)
{
    if (handle == NULL)                         /* check handle */
    {
        return 2;                               /* return error */
    }
    if (handle->inited != 1)                    /* check handle initialization */
    {
        return 3;                               /* return error */
    }
    
    *volume = handle->background_volume;        /* get volume */
    
    return 0;                                   /* success return 0 */
}

/**
 * @brief     set the synthesis speed
 * @param[in] *handle points to a syn6288 handle structure
 * @param[in] speed is the synthesis speed
 * @return    status code
 *            - 0 success
 *            - 1 set synthesis speed failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t syn6288_set_synthesis_speed(syn6288_handle_t *handle, uint8_t speed)
{
    char cmd[8];
    
    if (speed > 5)                                                  /* check speed */
    {
        handle->debug_print("syn6288: speed is invalid.\n");        /* speed is invalid */
       
        return 1;                                                   /* return error */
    }
    
    memset((char *)cmd, 0, sizeof(char)*8);                         /* memory set 0 */
    (void)snprintf((char *)cmd, 8, "t[%d]", (int16_t)speed);        /* set command */
    handle->speed = speed;                                          /* save speed */

    return syn6288_set_command(handle, (char *)cmd);                /* write command */
}

/**
 * @brief      get the synthesis speed
 * @param[in]  *handle points to a syn6288 handle structure
 * @param[out] *speed points to a synthesis speed
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t syn6288_get_synthesis_speed(syn6288_handle_t *handle, uint8_t *speed)
{
    if (handle == NULL)             /* check handle */
    {
        return 2;                   /* return error */
    }
    if (handle->inited != 1)        /* check handle initialization */
    {
        return 3;                   /* return error  */
    }
    
    *speed = handle->speed;         /* get speed */
    
    return 0;                       /* success return 0 */
}

/**
 * @brief     send the command to the chip
 * @param[in] *handle points to a syn6288 handle structure
 * @param[in] *command points to a command buffer
 * @return    status code
 *            - 0 success
 *            - 1 set command failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t syn6288_set_command(syn6288_handle_t *handle, char *command)
{
    uint8_t res;
    uint16_t l;
    uint8_t len, temp;
    uint8_t i;
    uint8_t xor_cal = 0;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    len = (uint8_t)strlen(command);                                       /* get length of command */
    if (len > 200)                                                        /* check result */
    {
        handle->debug_print("syn6288: command is too long.\n");           /* command is too long */
       
        return 1;                                                         /* return error */
    }
    handle->buf[0] = 0xFD;                                                /* frame header */
    handle->buf[1] = (uint8_t)((len + 3) / 256);                          /* length msb */
    handle->buf[2] = (len + 3) % 256;                                     /* length lsb */
    handle->buf[3] = 0x01;                                                /* command */
    handle->buf[4] = 0x00;                                                /* command param */
    strncpy((char *)&handle->buf[5], command, len);                       /* copy command */
    for (i = 0; i < len + 5; i++)
    {
        xor_cal ^= handle->buf[i];                                        /* calculate xor */
    }
    handle->buf[len + 5] = xor_cal;                                       /* set xor */
    res = handle->uart_flush();                                           /* uart flush */ 
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart flush failed.\n");             /* uart flush failed */
       
        return 1;                                                         /* return error */
    }
    res = handle->uart_write((uint8_t *)handle->buf, len+6);              /* uart write */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("syn6288: uart write failed.\n");             /* uart write failed */
       
        return 1;                                                         /* return error */
    }
    handle->delay_ms(100);                                                /* delay 100 ms */
    l = handle->uart_read((uint8_t *)&temp, 1);                           /* uart read */
    if (l != 1)                                                           /* check result */
    {
        handle->debug_print("syn6288: uart read failed.\n");              /* uart read failed */
       
        return 1;                                                         /* return error */
    }
    if (temp == 0x41)                                                     /* check return */
    {
        return 0;                                                         /* success return 0 */
    }
    else
    {
        handle->debug_print("syn6288: command receive failed.\n");        /* command receive failed */
       
        return 1;                                                         /* return error */
    }
}

/**
 * @brief      get chip's information
 * @param[out] *info points to a syn6288 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t syn6288_info(syn6288_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(syn6288_info_t));                        /* initialize syn6288 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "UART", 8);                            /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
