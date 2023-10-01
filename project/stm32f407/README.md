### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

UART2 Pin: TX/RX PA2/PA3.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. SYN6288

#### 3.1 Command Instruction

1. Show syn6288 chip and driver information.

   ```shell
   syn6288 (-i | --information)
   ```

2. Show syn6288 help.

   ```shell
   syn6288 (-h | --help)
   ```

3. Show syn6288 pin connections of the current board.

   ```shell
   syn6288 (-p | --port)
   ```

4. Run syn6288 register test.

   ```shell
   syn6288 (-t reg | --test=reg)
   ```

5. Run syn6288 synthesis test.

   ```shell
   syn6288 (-t syn | --test=syn)
   ```

6. Run syn6288 synthesis text function, gb2312 format is gb2312.

   ```shell
   syn6288 (-e syn | --example=syn) --text=<gb2312>
   ```

7. Run syn6288 advance synthesis text function, gb2312 format is gb2312.

   ```shell
   syn6288 (-e advance-syn | --example=advance-syn) --text=<gb2312>
   ```

8. Run syn6288 advance synthesis sound function, type can be "A" - "Y".

   ```shell
   syn6288 (-e advance-sound | --example=advance-sound) --sound=<type>
   ```

9. Run syn6288 advance synthesis message function, type can be "A" - "H".

   ```shell
   syn6288 (-e advance-msg | --example=advance-msg) --msg=<type>
   ```

10. Run syn6288 advance synthesis ring function, type can be "A" - "O".

    ```shell
    syn6288 (-e advance-ring | --example=advance-ring) --ring=<type>
    ```

#### 3.2 Command Example

```shell
syn6288 -i

syn6288: chip is YuToneWorld SYN6288.
syn6288: manufacturer is YuToneWorld.
syn6288: interface is UART.
syn6288: driver version is 2.0.
syn6288: min supply voltage is 2.4V.
syn6288: max supply voltage is 5.1V.
syn6288: max current is 280.00mA.
syn6288: max temperature is 85.0C.
syn6288: min temperature is -35.0C.
```

```shell
syn6288 -p

syn6288: TX connected to GPIOA PIN3.
syn6288: RX connected to GPIOA PIN2.
```

```shell
syn6288 -t reg

syn6288: chip is YuToneWorld SYN6288.
syn6288: manufacturer is YuToneWorld.
syn6288: interface is IIC.
syn6288: driver version is 2.0.
syn6288: min supply voltage is 2.4V.
syn6288: max supply voltage is 5.1V.
syn6288: max current is 280.00mA.
syn6288: max temperature is 85.0C.
syn6288: min temperature is -35.0C.
syn6288: start register test.
syn6288: syn6288_set_baud_rate/syn6288_get_baud_rate test.
syn6288: set 9600 bps.
syn6288: check baud rate ok.
syn6288: syn6288_set_mode/syn6288_get_mode test.
syn6288: set background_15 mode.
syn6288: check mode ok.
syn6288: syn6288_set_text_type/syn6288_get_text_type test.
syn6288: set gb2312 text type.
syn6288: check text type ok.
syn6288: set gbk text type.
syn6288: check text type ok.
syn6288: set big5 text type.
syn6288: check text type ok.
syn6288: set unicode text type.
syn6288: check text type ok.
syn6288: syn6288_set_synthesis_volume/syn6288_get_synthesis_volume test.
syn6288: set synthesis volume 6.
syn6288: check synthesis volume ok.
syn6288: syn6288_set_background_volume/syn6288_get_background_volume test.
syn6288: set background volume 8.
syn6288: check background volume ok.
syn6288: syn6288_set_synthesis_speed/syn6288_get_synthesis_speed test.
syn6288: set synthesis speed 3.
syn6288: check synthesis speed ok.
syn6288: syn6288_set_command test.
syn6288: check command ok.
syn6288: finish register test.
```

```shell
syn6288 -t syn

syn6288: chip is YuToneWorld SYN6288.
syn6288: manufacturer is YuToneWorld.
syn6288: interface is IIC.
syn6288: driver version is 2.0.
syn6288: min supply voltage is 2.4V.
syn6288: max supply voltage is 5.1V.
syn6288: max current is 280.00mA.
syn6288: max temperature is 85.0C.
syn6288: min temperature is -35.0C.
syn6288: start synthesis test.
syn6288: synthesis text test.
syn6288: gb2312 synthesis text.
syn6288: gbk synthesis text.
syn6288: big5 synthesis text.
syn6288: unicode synthesis text.
syn6288: synthesis sound test.
syn6288: synthesis message test.
syn6288: synthesis ring test.
syn6288: synthesis control test.
syn6288: synthesis control pause.
syn6288: synthesis control resume.
syn6288: synthesis control stop.
syn6288: synthesis volume test.
syn6288: set synthesis volume 5.
syn6288: synthesis speed test.
syn6288: set synthesis speed 0.
syn6288: synthesis mode test.
syn6288: background mode on.
syn6288: command test.
syn6288: set command 0.
syn6288: set command 1.
syn6288: finish synthesis test.
```

```shell
syn6288 -e syn --text=你好

syn6288: synthesis 你好.
```

```shell
syn6288 -e advance-syn --text=你好

syn6288: synthesis 你好.
```

```shell
syn6288 -e advance-sound --sound=A

syn6288: synthesis sound a.
```

```shell
syn6288 -e advance-msg --msg=A

syn6288: synthesis message a.
```

```shell
syn6288 -e advance-ring --ring=A

syn6288: synthesis ring a.
```

```shell
syn6288 -h

Usage:
  syn6288 (-i | --information)
  syn6288 (-h | --help)
  syn6288 (-p | --port)
  syn6288 (-t reg | --test=reg)
  syn6288 (-t syn | --test=syn)
  syn6288 (-e syn | --example=syn) --text=<gb2312>
  syn6288 (-e advance-syn | --example=advance-syn) --text=<gb2312>
  syn6288 (-e advance-sound | --example=advance-sound) --sound=<type>
  syn6288 (-e advance-msg | --example=advance-msg) --msg=<type>
  syn6288 (-e advance-ring | --example=advance-ring) --ring=<type>

Options:
  -e <syn | advance-syn | advance-sound | advance-msg | advance-ring>, --example=<syn
     | advance-syn | advance-sound | advance-msg | advance-ring>
                          Run the driver example.
  -h, --help              Show the help.
  -i, --information       Show the chip information.
      --msg=<type>        Set the synthesis message and type can be "A" - "H".
  -p, --port              Display the pin connections of the current board.
      --ring=<type>       Set the synthesis ring and type can be "A" - "O".
      --sound=<type>      Set the synthesis sound and type can be "A" - "Y".
  -t <reg | syn>, --test=<reg | syn>
                          Run the driver test.
      --text=<gb2312>     Set the synthesis text and it's format is GB2312.
```

